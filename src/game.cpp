#include "game.hpp"

Game::Game()
{
    // Initialize vita2d
    vita2d_init();
    vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));

    // Initialize input
    Input::initInput();

    // Initialize gui
    Gui::loadFont();

    // Load levels
    level1.loadFromFile( "app0:levels/level1.txt" );

    gameState = GameState::initialized;
}

Game::~Game()
{
    vita2d_fini();
}

void Game::start()
{
    if( gameState == GameState::initialized )
        loop();
}

void Game::loop()
{
    while( gameState != GameState::exiting )
    {
        Input::handleInput();

        level1.update();

        draw();
    }
}

void Game::draw()
{
    vita2d_start_drawing();
    vita2d_clear_screen();

    level1.draw();

    Gui::drawTextf_color_position( Gui::Position::alignTop, 0, 0, 20, RGBA8( 255, 255, 0, 255 ), "Text drawing test" );

    // DEBUG
    if( Input::wasPressed( Input::Button::cross ) )
        Gui::drawTextf_color_position( Gui::Position::alignTop, 100, 100, 50, RGBA8( 255, 0, 0, 255 ), "X pressed!" );
    else if( Input::isHeld( Input::Button::cross ) )
        Gui::drawTextf_color_position( Gui::Position::alignTop, 100, 100, 50, RGBA8( 255, 0, 0, 255 ), "X!" );

    vita2d_end_drawing();
    vita2d_swap_buffers();
}