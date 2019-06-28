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
    selectedLevelList = 1;  // TODO Have to change this if adding new World
    level.firstInit();
    initCustomLevelList();
    initLevelList();

    // Initialize the level select menu
    LevelSelect customLevels = LevelSelect();
    levelMenus.push_back( customLevels );
    LevelSelect world1Levels = LevelSelect();
    levelMenus.push_back( world1Levels );

    levelMenus[ 0 ].initLevels( &levelListList[ 0 ], "Custom" );
    levelMenus[ 1 ].initLevels( &levelListList[ 1 ], "World 1" );

    // Initialize the sound effects
    Sound::initSoloud();
    Sound::loadSounds();

    // Read stats from file
    Stats::readStats();

    // Load settings from file
    optionsMenu.loadOptions();

    progressSaved = false;
    finishMessage = false;
    gameComplete = false;

    gameState = GameState::initialized;

    //Sound::soloud.play( Sound::menuMusic );
}

Game::~Game()
{
    vita2d_fini();
}

void Game::initLevelList()
{
    int dfd;
    LevelList newLevelList = LevelList();
    dfd = sceIoDopen( pathLevels.c_str() );
    if( dfd > 0 )
    {
        SceIoDirent file;
        while( sceIoDread( dfd, &file ) > 0 )
        {
            std::string fileName( file.d_name );
            newLevelList.add( pathLevels + fileName );
        }
    }
    else if( dfd < 0 )
    {
        // TODO handle error
    }
    sceIoDclose( dfd );

    // TODO This needs to be changes for more levelLists
    newLevelList.loadProgress( 1 );

    levelListList.push_back( newLevelList );
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
            case GameState::levelMenu:
            case GameState::paused:
            case GameState::optionsMenu:
                inMenu();
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
        if( Input::wasPressed( Input::Button::start ) )
        {
            gameTime.pause();
            gameState = GameState::paused;
        }
        else
        {
            if( Input::wasPressed( Input::Button::triangle ) )
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
            }
            else
            {
                gameState = GameState::mainMenu;
                Sound::levelMusic.stop();
                Sound::soloud.play( Sound::menuMusic );
                destroyLevel();
                finishMessage = true;
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
            Sound::levelMusic.stop();
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

        // Handle game finish message box
        if( finishMessage )
        {
            if( Input::wasPressed( Input::Button::cross ) || Input::wasPressed( Input::Button::circle ) || Input::wasPressed( Input::Button::start ) )
            {
                finishMessage = false;
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

                Sound::menuMusic.stop();
                Sound::soloud.play( Sound::levelMusic );
                
                // TODO this kinda sucks right now
                initLevel( levelListList[ selectedLevelList ].lastUnlockedLevel() );
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
            Sound::levelMusic.stop();
            Sound::soloud.play( Sound::menuMusic );
            destroyLevel();
        }

        draw();
    }
    // Level select menu
    else if( gameState == GameState::levelMenu )
    {
        if( gameComplete && !alreadyShowedCompleteMessage )
        {
            if( Input::wasPressed( Input::Button::cross ) || Input::wasPressed( Input::Button::circle ) || Input::wasPressed( Input::Button::start ) )
            {
                alreadyShowedCompleteMessage = true;
                levelListList[ selectedLevelList ].saveProgress( selectedLevelList );
            }
        }
        else
        {
            if( Input::wasPressed( Input::Button::circle ) )
            {
                gameState = GameState::mainMenu;
            }
            // Handle switching between level select screens
            // TODO move this to menu.hpp/.cpp if possible
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

            if( levelMenus[ selectedLevelList ].selectPressed() )
            {
                gameState = GameState::playing;
                Sound::menuMusic.stop();
                Sound::soloud.play( Sound::levelMusic );
                initLevel( levelMenus[ selectedLevelList ].getCursor() );
            }
            levelMenus[ selectedLevelList ].update();
        }

        draw();

        if( levelMenus[ selectedLevelList ].isGameComplete() )
            gameComplete = true;
    }
    // Options menu
    else if( gameState == GameState::optionsMenu )
    {
        optionsMenu.update();

        if( Input::wasPressed( Input::Button::circle ) || Input::wasPressed( Input::Button::start ) )
        {
            gameState = GameState::mainMenu;
            optionsMenu.saveOptions();
        }
        draw();
    }

    calcFrameTime();
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

            if( finishMessage && !gameComplete )
                Gui::drawMessageBox( "Congratualations!", "You've completed all the\nlevels currently available to\nplay in Pingo!\nFor your next challange, try\ngetting 3 stars in every level!" );
            else if( finishMessage && gameComplete )
                Gui::drawMessageBox( "Congratualations!", "You've completed all the\nlevels currently available to\nplay in Pingo!\nSince you've already collected all the\nstars, you'll have to wait for more\ncontent. Follow me @_grzybojad if you\ndon't want to miss any updates!" );

            break;

        case GameState::playing:
            level.draw();
            
            if( level.complete() )
                finishMenu.draw();

            break;

        case GameState::levelMenu:
            levelMenus[ selectedLevelList ].draw();

            if( gameComplete && !alreadyShowedCompleteMessage )
                Gui::drawMessageBox( "Amazing!", "You got 3 stars on every single\nlevel! I'm impressed by your skills\nand your determination to master\nthis game. Thank you so much for\nplaying Pingo!\n- Grzybojad" );

            break;

        case GameState::paused:
            level.draw();
            pauseMenu.draw();
            break;

        case GameState::optionsMenu:
            optionsMenu.draw();
            break;
    }

    Gui::drawDebugText();

    vita2d_end_drawing();
    vita2d_swap_buffers();
}