#include "game.hpp"

Game::Game()
{
    // Initialize vita2d
    vita2d_init_advanced_with_msaa( ( 1 * 1024 * 1024 ), SCE_GXM_MULTISAMPLE_4X );
    vita2d_set_clear_color( RGBA8( 0xFF, 0xFF, 0xFF, 0xFF ) );

    // Initialize input
    Input::initInput();

    // Initialize gui
    Gui::loadFont();

    // Initialize level list
    initLevelList();

    // TODO: change this
    gameState = GameState::initialized;
}

Game::~Game()
{
    vita2d_fini();
}

void Game::initLevelList()
{
    levelList.add( "level1.txt" );
    levelList.add( "level2.txt" );
    levelList.add( "level3.txt" );
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
        finishMenu.update();

        if( finishMenu.clickedNextLevel() )
        {
            levelList.nextLevel();
            destroyLevel();
            initLevel();
        }
        else if( finishMenu.clickedMainMenu() )
        {
            gameState = GameState::mainMenu;
            destroyLevel();
        }

        
        vita2d_start_drawing();
        vita2d_clear_screen();
        
        level.draw();
        finishMenu.draw();

        vita2d_end_drawing();
        vita2d_swap_buffers();
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
        else if( mainMenu.clickedExit() )
        {
            gameState = GameState::exiting;
        }

        vita2d_start_drawing();
        vita2d_clear_screen();

        mainMenu.draw();

        vita2d_end_drawing();
        vita2d_swap_buffers();
    }
    else if( gameState == GameState::paused )
    {
        pauseMenu.update();

        if( pauseMenu.clickedResume() )
        {
            gameState = GameState::playing;
        }
        else if( pauseMenu.clickedMainMenu() )
        {
            gameState = GameState::mainMenu;
            destroyLevel();
        }

        vita2d_start_drawing();
        vita2d_clear_screen();

        level.draw();
        pauseMenu.draw();

        vita2d_end_drawing();
        vita2d_swap_buffers();
    }

    calcFrameTime();
}

void Game::initLevel()
{
    level.init();
    level.loadFromFile( levelList.getLevelPath( levelList.getCurrentLevel() ) );
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

    // TODO move drawing here

    level.draw();

    vita2d_end_drawing();
    vita2d_swap_buffers();
}