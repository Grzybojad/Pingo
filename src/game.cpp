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
    initLevelList();

    // Initialize the level select menu
    levelMenu.initLevels( &levelList );

    // Initialize the sound effects
    Sound::initSoloud();
    Sound::loadSounds();

    // Read stats from file
    Stats::readStats();

    progressSaved = false;
    finishMessage = false;
    gameComplete = false;

    gameState = GameState::initialized;
}

Game::~Game()
{
    vita2d_fini();
}

void Game::initLevelList()
{
    int dfd;
    dfd = sceIoDopen( "app0:levels/" );
    if( dfd > 0 )
    {
        SceIoDirent file;
        while( sceIoDread( dfd, &file ) > 0 )
        {
            std::string fileName( file.d_name );
            levelList.add( fileName );
        }
    }
    else if( dfd < 0 )
    {
        // TODO handle error
    }
    sceIoDclose( dfd );

    levelList.loadProgress();
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
        if( !levelList.getCompletion( levelList.getCurrentLevel() ) )
            levelList.compleateCurrentLevel();

        // Check to only save the data and play sound once
        if( !progressSaved )
        {
            Sound::soloud.play( Sound::levelFinish );
            levelList.saveProgress();
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
            if( levelList.nextLevel() )
            {
                destroyLevel();
                initLevel();
            }
            else
            {
                gameState = GameState::mainMenu;
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
                initLevel( levelList.lastUnlockedLevel() );
            }
            else if( mainMenu.clickedLevelSelect() )
            {
                levelMenu.initStars();
                gameState = GameState::levelMenu;
            }
            else if( mainMenu.clickedExit() )
            {
                //gameState = GameState::exiting;
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
                levelList.saveProgress();
            }
        }
        else
        {
            if( Input::wasPressed( Input::Button::circle ) )
            {
                gameState = GameState::mainMenu;
            }
            if( levelMenu.selectPressed() )
            {
                gameState = GameState::playing;
                initLevel( levelMenu.getCursor() );
            }
            levelMenu.update();
        }

        draw();

        if( levelMenu.isGameComplete() )
            gameComplete = true;
    }
    // Options menu
    else if( gameState == GameState::optionsMenu )
    {
        if( Input::wasPressed( Input::Button::circle ) || Input::wasPressed( Input::Button::start ) )
        {
            gameState = GameState::mainMenu;
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
    level.loadFromFile( levelList.accessElement( levelList.getCurrentLevel() - 1 ) );
}

void Game::initLevel( int levelIndex )
{
    if( !gameTime.is_started() )
        gameTime.start();
    else if( gameTime.is_paused() )
        gameTime.unpause();

    level.init();
    // TODO don't allow loading unexisting levels
    levelList.setCurrentLevel( levelIndex );
    level.loadFromFile( levelList.accessElement( levelList.getCurrentLevel() - 1 ) );
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
}

void Game::draw()
{
    vita2d_start_drawing();
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
            levelMenu.draw();

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

    // DEBUG draw gametime
    Gui::drawTextf( 20, 100, 20, "Game time: %d", gameTime.get_ticks() / 1000000 );

    vita2d_end_drawing();
    vita2d_swap_buffers();
}