#include "game.hpp"

Game::Game()
{
    // Initialize vita2d
    vita2d_init_advanced_with_msaa( ( 1 * 1024 * 1024 ), SCE_GXM_MULTISAMPLE_4X );
    vita2d_set_clear_color( RGBA8( 0xFF, 0xFF, 0xFF, 0xFF ) );

    // Initialize input
    Input::initInput();

    // Load textures
    Texture::loadTextures();

    // Initialize gui
    Gui::loadFont();

    // Initialize level list
    selectedLevelList = 1;
    level.firstInit();
    initCustomLevelList();
    initLevelList();

    // Initialize the level select menu
    LevelSelect customLevels = LevelSelect();
    levelMenus.push_back( customLevels );
    LevelSelect world1Levels = LevelSelect();
    levelMenus.push_back( world1Levels );
    LevelSelect world2Levels = LevelSelect();
    levelMenus.push_back( world2Levels );

    levelMenus[ 0 ].initLevels( &levelListList[ 0 ], "Custom" );
    levelMenus[ 1 ].initLevels( &levelListList[ 1 ], "World 1" );
    levelMenus[ 2 ].initLevels( &levelListList[ 2 ], "World 2" );

    // Initialize the sound effects
    Sound::initSoloud();
    Sound::loadSounds();

    // Read stats from file
    Stats::readStats();

    // Load settings from file
    optionsMenu.loadOptions();

    progressSaved = false;

    gameState = GameState::initialized;
}

Game::~Game()
{
    vita2d_fini();
}

void Game::initLevelList()
{
    int dfd;

    for( int i = 1; i <= nrOfWorlds; ++i )
    {
        LevelList newLevelList = LevelList();
        dfd = sceIoDopen( ( pathLevels + "World" + std::to_string( i ) + "/" ).c_str() );
        if( dfd > 0 )
        {
            SceIoDirent file;
            while( sceIoDread( dfd, &file ) > 0 )
            {
                std::string fileName( file.d_name );
                newLevelList.add( pathLevels + "World" + std::to_string( i ) + "/" + fileName );
            }
        }
        else if( dfd < 0 )
        {
            // TODO handle error
        }
        sceIoDclose( dfd );

        newLevelList.loadProgress( i );

        levelListList.push_back( newLevelList );
    }
}

void Game::initCustomLevelList()
{
    int dfd;
    LevelList newLevelList = LevelList();
    sceIoMkdir( pathCustomLevels.c_str(), 0777 );
    dfd = sceIoDopen( pathCustomLevels.c_str() );
    if( dfd > 0 )
    {
        SceIoDirent file;
        while( sceIoDread( dfd, &file ) > 0 )
        {
            std::string fileName( file.d_name );
            newLevelList.add( pathCustomLevels + fileName );
        }
    }
    else if( dfd < 0 )
    {
        // TODO handle error
    }
    sceIoDclose( dfd );

    newLevelList.loadProgress( 0 );

    levelListList.push_back( newLevelList );
}

void Game::mainLoop()
{
    if( gameState != GameState::initialized )
        return;

    while( gameState != GameState::exiting )
    {
        Input::handleInput();

        switch( gameState )
        {
            case GameState::initialized:
                gameState = GameState::mainMenu;
                break;

            case GameState::playing:
                inGame();
                break;

            case GameState::mainMenu:
                WALLCOLOR = RGBA8( 144, 145, 194, 255 );
                BGCOLOR = RGBA8( 97, 90, 160, 255 );
                inMenu();
                break;

            case GameState::levelMenu:
            case GameState::paused:
            case GameState::optionsMenu:
                inMenu();
                break;

            case GameState::credits:
                inCredits();
                break;
        }
    }

    exit();

    return;
}

void Game::inGame()
{
    if( !level.complete() )
    {
        if( Input::wasPressed( Input::Button::start ) || Input::rectWasTouched( Rect( SCREEN_WIDTH - 190, SCREEN_HEIGHT - 80, 200, 85 ) ) )
        {
            gameTime.pause();
            gameState = GameState::paused;
        }
        else
        {
            if( Input::wasPressed( Input::Button::triangle ) || Input::rectWasTouched( Rect( SCREEN_WIDTH - 190, SCREEN_HEIGHT - 150, 200, 75 ) ) )
            {
                destroyLevel();
                initLevel();
            }
            level.update();
            draw();
        }
    }
    else
    {
        // Set the completion state of the level and unlock the next level
        if( !levelListList[ selectedLevelList ].getCompletion( levelListList[ selectedLevelList ].getCurrentLevel() ) )
            levelListList[ selectedLevelList ].compleateCurrentLevel();

        // Check to only save the data and play sound once
        if( !progressSaved )
        {
            Sound::soloud.play( Sound::levelFinish );
            levelListList[ selectedLevelList ].saveProgress( selectedLevelList );
            Stats::totalLevelFinished++;
            Stats::timePlayed += ( gameTime.get_ticks() / 1000000 );
            gameTime.start();
            gameTime.pause();
            Stats::saveStats();
            progressSaved = true;
        }

        finishMenu.setStars( level.getStarRating() );

        finishMenu.update();

        if( finishMenu.clickedNextLevel() )
        {
            progressSaved = false;

            if( levelListList[ selectedLevelList ].nextLevel() )
            {
                destroyLevel();
                initLevel();

                if( selectedLevelList == 2 )
                {
                    int level = levelListList[ selectedLevelList ].getCurrentLevel();
                    if( level == 11 || level == 21 )
                    {
                        Sound::stopLevelMusic();
                        playLevelMusic();
                    }
                }
            }
            else
            {
                // If there's no next level, play the credits
                credits.init();
                gameState = GameState::credits;
            }
            
        }
        else if( finishMenu.clickedRestart() )
        {
            progressSaved = false;
            destroyLevel();
            initLevel();
        }
        else if( finishMenu.clickedMainMenu() )
        {
            progressSaved = false;
            gameState = GameState::mainMenu;
            Sound::stopLevelMusic();
            Sound::soloud.play( Sound::menuMusic );
            destroyLevel();
        }

        draw();
    }

    calcFrameTime();
}

void Game::inMenu()
{
    // Main menu
    if( gameState == GameState::mainMenu )
    {
        mainMenu.update();
        curtain.update();

        // This is a mess, but whatever
        if( levelListList[ 1 ].areAllLevelsFinished() && !levelListList[ 1 ].seenFinishCongratulations )
        {
            if( Input::wasPressed( Input::Button::cross ) || Input::wasPressed( Input::Button::circle ) || Input::wasPressed( Input::Button::start ) )
            {
                levelListList[ 1 ].seenFinishCongratulations = true;
                levelListList[ 1 ].saveProgress( 1 );
            }
        }
        else if( levelListList[ 1 ].areAllLevelsFinished() && !levelListList[ 1 ].seenCompleteCongratulations )
        {
            if( Input::wasPressed( Input::Button::cross ) || Input::wasPressed( Input::Button::circle ) || Input::wasPressed( Input::Button::start ) )
            {
                levelListList[ 1 ].seenCompleteCongratulations = true;
                levelListList[ 1 ].saveProgress( 1 );
            }
        }
        else if( levelListList[ 2 ].areAllLevelsFinished() && !levelListList[ 2 ].seenFinishCongratulations )
        {
            if( Input::wasPressed( Input::Button::cross ) || Input::wasPressed( Input::Button::circle ) || Input::wasPressed( Input::Button::start ) )
            {
                levelListList[ 2 ].seenFinishCongratulations = true;
                levelListList[ 2 ].saveProgress( 2 );
            }
        }
        else if( levelListList[ 2 ].areAllLevelsFinished() && !levelListList[ 2 ].seenCompleteCongratulations )
        {
            if( Input::wasPressed( Input::Button::cross ) || Input::wasPressed( Input::Button::circle ) || Input::wasPressed( Input::Button::start ) )
            {
                levelListList[ 2 ].seenCompleteCongratulations = true;
                levelListList[ 2 ].saveProgress( 2 );
            }
        }

        else
        {
            if( mainMenu.clickedStart() )
            {
                if( gameTime.is_started() )
                    gameTime.unpause();
                else
                    gameTime.start();

                gameState = GameState::playing;
                
                if( levelListList[ 1 ].areAllLevelsFinished() && levelListList[ 2 ].areAllLevelsFinished() )
                {
                    // If all levels are finished, play 1-1
                    selectedLevelList = 1;
                    initLevel( 1 );
                }
                else if( levelListList[ 1 ].areAllLevelsFinished() )
                {
                    // If all World 1 levels are finished, play last unlocked level of World 2
                    selectedLevelList = 2;
                    initLevel( levelListList[ selectedLevelList ].lastUnlockedLevel() );
                }
                else if( levelListList[ 2 ].areAllLevelsFinished() )
                {
                    // In all other cases, play last unlocked level of World 1
                    selectedLevelList = 1;
                    initLevel( levelListList[ selectedLevelList ].lastUnlockedLevel() );
                }

                Sound::menuMusic.stop();
                playLevelMusic();
            }
            else if( mainMenu.clickedLevelSelect() )
            {
                // Init all star counters
                for( int i = 0; i < levelMenus.size(); ++i )
                {
                    levelMenus[ i ].initStars();
                }

                gameState = GameState::levelMenu;
            }
            else if( mainMenu.clickedOptions() )
            {
                gameState = GameState::optionsMenu;
            }
        }

        draw();
    }
    // Pause menu
    else if( gameState == GameState::paused )
    {
        pauseMenu.update();

        if( pauseMenu.clickedResume() )
        {
            gameTime.unpause();
            gameState = GameState::playing;
        }
        if( pauseMenu.clickedRestart() )
        {
            gameState = GameState::playing;
            destroyLevel();
            initLevel();
        }
        else if( pauseMenu.clickedMainMenu() )
        {
            gameState = GameState::mainMenu;
            Sound::stopLevelMusic();
            Sound::soloud.play( Sound::menuMusic );
            destroyLevel();
        }

        draw();
    }
    // Level select menu
    else if( gameState == GameState::levelMenu )
    {
        if( Input::wasPressed( Input::Button::circle ) )
        {
            gameState = GameState::mainMenu;
        }
        // Handle switching between level select screens
        if( Input::wasPressed( Input::Button::lTrigger ) )
        {
            if( selectedLevelList > 0 )
                selectedLevelList--;
            else
            {
                selectedLevelList = levelListList.size() - 1;
            }
            Sound::soloud.play( Sound::menuMove );
        }
        else if( Input::wasPressed( Input::Button::rTrigger ) )
        {
            if( selectedLevelList < levelListList.size() - 1 )
                selectedLevelList++;
            else
            {
                selectedLevelList = 0;
            }
            Sound::soloud.play( Sound::menuMove );
        }
        
        switch( selectedLevelList )
        {
            case 0:
            case 1:
                WALLCOLOR = RGBA8( 144, 145, 194, 255 );
                BGCOLOR = RGBA8( 97, 90, 160, 255 );
                break;
            case 2:
                WALLCOLOR = RGBA8( 110, 142, 110, 255 );
                BGCOLOR = RGBA8( 47, 98, 52, 255 );
                break;
            default:
                WALLCOLOR = RGBA8( 144, 145, 194, 255 );
                BGCOLOR = RGBA8( 97, 90, 160, 255 );
                break;
        }

        if( levelMenus[ selectedLevelList ].selectPressed() )
        {
            gameState = GameState::playing;
            initLevel( levelMenus[ selectedLevelList ].getCursor() );

            Sound::menuMusic.stop();
            playLevelMusic();
        }
        levelMenus[ selectedLevelList ].update();

        draw();
    }
    // Options menu
    else if( gameState == GameState::optionsMenu )
    {
        optionsMenu.update();

        if( Input::wasPressed( Input::Button::circle ) || Input::wasPressed( Input::Button::start ) || Input::rectWasTouched( Rect( SCREEN_WIDTH - 150, SCREEN_HEIGHT - 85, 145, 80 ) ) )
        {
            gameState = GameState::mainMenu;
            optionsMenu.saveOptions();
        }
        draw();
    }

    calcFrameTime();
}

void Game::inCredits()
{
    credits.update();

    if( credits.haveEnded() )
    {
        Sound::stopLevelMusic();
        Sound::soloud.play( Sound::menuMusic );
        gameState = GameState::mainMenu;
    }

    draw();
}

void Game::initLevel()
{
    if( !gameTime.is_started() )
        gameTime.start();
    else if( gameTime.is_paused() )
        gameTime.unpause();

    level.init();
    level.loadFromFile( levelListList[ selectedLevelList ].accessElement( levelListList[ selectedLevelList ].getCurrentLevel() - 1 ) );
}

void Game::initLevel( int levelIndex )
{
    if( !gameTime.is_started() )
        gameTime.start();
    else if( gameTime.is_paused() )
        gameTime.unpause();

    level.init();
    // TODO don't allow loading unexisting levels
    levelListList[ selectedLevelList ].setCurrentLevel( levelIndex );
    level.loadFromFile( levelListList[ selectedLevelList ].accessElement( levelListList[ selectedLevelList ].getCurrentLevel() - 1 ) );
}

void Game::destroyLevel()
{
    level.unload();
}

void Game::exit()
{
    vita2d_fini();

    Texture::freeTextures();

    Gui::freeFont();

    Sound::soloud.deinit();
}

void Game::draw()
{
    vita2d_pool_reset();
    vita2d_start_drawing_advanced( NULL, SCE_GXM_SCENE_VERTEX_WAIT_FOR_DEPENDENCY );
    vita2d_clear_screen();

    background.update();
    background.draw();

    switch( gameState )
    {
        case GameState::mainMenu:
            mainMenu.draw();
            curtain.draw();

            if( levelListList[ 1 ].areAllLevelsFinished() && !levelListList[ 1 ].seenFinishCongratulations )
                Gui::drawMessageBox( "Congratualations!", "You've completed all the\nlevels of World 1!\nTry getting 3 stars in every\nlevel or try World 2!" );
            else if( levelListList[ 1 ].areAllLevelsFinished() && !levelListList[ 1 ].seenCompleteCongratulations )
                Gui::drawMessageBox( "You're amazing!", "You managed to get 3 stars\non all World 1 levels!\nThis is no small feat, I'm\nproud of you. If you didn't\ncheat that is." );
            else if( levelListList[ 2 ].areAllLevelsFinished() && !levelListList[ 2 ].seenFinishCongratulations )
                Gui::drawMessageBox( "Congratualations!", "You've completed all the\nlevels of World 2!\nTry getting 3 stars in every\nlevel!" );
            else if( levelListList[ 2 ].areAllLevelsFinished() && !levelListList[ 2 ].seenCompleteCongratulations )
                Gui::drawMessageBox( "You're amazing!", "You managed to get 3 stars\non all World 2 levels!\nI hope you had a lot of fun\nplaying them!" );
            break;

        case GameState::playing:
            level.draw();
            
            if( level.complete() )
                finishMenu.draw();

            break;

        case GameState::levelMenu:
            levelMenus[ selectedLevelList ].draw();

            break;

        case GameState::paused:
            level.draw();
            pauseMenu.draw();
            break;

        case GameState::optionsMenu:
            optionsMenu.draw();
            break;

        case GameState::credits:
            level.draw();
            credits.draw();
            break;
    }

    Gui::drawDebugText();

    vita2d_end_drawing();
    vita2d_swap_buffers();
}

void Game::playLevelMusic()
{
    if( selectedLevelList != 2 )
        Sound::playLevelMusic( 1 );
    else if( levelListList[ 2 ].getCurrentLevel() > 20 )
        Sound::playLevelMusic( 4 );
    else if( levelListList[ 2 ].getCurrentLevel() > 10 )
        Sound::playLevelMusic( 3 );
    else
        Sound::playLevelMusic( 2 );
}