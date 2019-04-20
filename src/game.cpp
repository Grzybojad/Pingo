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
            gameState = GameState::paused;
        }
        else
        {
            level.update();
            draw();
        }
    }
    else
    {
        // Check to only save the data once
        if( !progressSaved )
        {
            levelList.saveProgress();
            progressSaved = true;
        }

        finishMenu.setStars( level.getStarRating() );

        finishMenu.update();

        if( !levelList.getCompletion( levelList.getCurrentLevel() ) )
            levelList.compleateCurrentLevel();

        if( finishMenu.clickedNextLevel() )
        {
            progressSaved = false;
            levelList.nextLevel();
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

        // TODO make this more elegant
        if( mainMenu.clickedStart() )
        {
            gameState = GameState::playing;
            initLevel();
        }
        else if( mainMenu.clickedLevelSelect() )
        {
            gameState = GameState::levelMenu;
        }
        else if( mainMenu.clickedExit() )
        {
            gameState = GameState::exiting;
        }

        draw();
    }
    else if( gameState == GameState::paused )
    {
        pauseMenu.update();

        if( pauseMenu.clickedResume() )
        {
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
    else if( gameState == GameState::levelMenu )
    {
        // TODO make this a little more elegant maybe
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

        draw();
    }

    calcFrameTime();
}

void Game::initLevel()
{
    level.init();
    level.loadFromFile( levelList.accessElement( levelList.getCurrentLevel() - 1 ) );
}

void Game::initLevel( int levelIndex )
{
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

    // Free textures

    Gui::freeFont();
}

void Game::draw()
{
    vita2d_start_drawing();
    vita2d_clear_screen();

    Texture::drawTexture_fillScreen( Texture::Sprite::background1 );

    switch( gameState )
    {
        case GameState::mainMenu:
            mainMenu.draw();
            break;

        case GameState::playing:
            level.draw();
            
            if( level.complete() )
                finishMenu.draw();

            break;

        case GameState::levelMenu:
            levelMenu.draw();
            break;

        case GameState::paused:
            level.draw();
            pauseMenu.draw();
            break;
    }

    vita2d_end_drawing();
    vita2d_swap_buffers();
}