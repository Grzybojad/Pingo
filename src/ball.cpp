#include "ball.hpp"

Ball::Ball()
{
    state = State::stationary;

    tilePosOffset.x = 0;
    tilePosOffset.y = 0;
    worldPos.x = 0;
    worldPos.y = 0;

    ballSpeed = 12.0f;

    tileSize = 30;
}

Ball::~Ball()
{

}
/*
void Ball::setTilePos( Vec2 spawnTile )
{
    tilePos = spawnTile;
}
*/
void Ball::setWorldPos( Vec2 worldPos )
{
    this->worldPos = worldPos;
}

Vec2 Ball::getWorldPos()
{
    return worldPos;
}

void Ball::handleInput()
{
    if( state == State::stationary )
    {
        if( Input::wasPressed (Input::Button::up ) )
            moveUp();
        if( Input::wasPressed (Input::Button::right ) )
            moveRight();
        if( Input::wasPressed (Input::Button::down ) )
            moveDown();
        if( Input::wasPressed (Input::Button::left ) )
            moveLeft();
    }
}

void Ball::move()
{
    switch( state )
    {
        case State::stationary:
            break;

        case State::movingUp:
            worldPos.y -= ballSpeed * timestep;
            tilePosOffset.y -= ballSpeed * timestep;
            break;

        case State::movingRight:
            worldPos.x += ballSpeed * timestep;
            tilePosOffset.x += ballSpeed * timestep;
            break;

        case State::movingDown:
            worldPos.y += ballSpeed * timestep;
            tilePosOffset.y += ballSpeed * timestep;
            break;

        case State::movingLeft:
            worldPos.x -= ballSpeed * timestep;
            tilePosOffset.x -= ballSpeed * timestep;
            break;
    }

    // Normalize position offset
    if( tilePosOffset.x >= (tileSize/2) ) tilePosOffset.x -= (tileSize/2);
    if( tilePosOffset.y >= (tileSize/2) ) tilePosOffset.y -= (tileSize/2);
    if( tilePosOffset.x <= -(tileSize/2) ) tilePosOffset.x += (tileSize/2);
    if( tilePosOffset.y <= -(tileSize/2) ) tilePosOffset.y += (tileSize/2);
}

void Ball::moveBack()
{
    switch( state )
    {
        case State::stationary:
            break;

        case State::movingUp:
            worldPos.y += ballSpeed * timestep;
            tilePosOffset.y += ballSpeed * timestep;
            break;

        case State::movingRight:
            worldPos.x -= ballSpeed * timestep;
            tilePosOffset.x -= ballSpeed * timestep;
            break;

        case State::movingDown:
            worldPos.y -= ballSpeed * timestep;
            tilePosOffset.y -= ballSpeed * timestep;
            break;

        case State::movingLeft:
            worldPos.x += ballSpeed * timestep;
            tilePosOffset.x += ballSpeed * timestep;
            break;
    }
}

void Ball::draw()
{
    vita2d_draw_rectangle( worldPos.x - (tileSize/2), worldPos.y - (tileSize/2), 30, 30, RGBA8( 255, 0, 0, 255 ) );
    vita2d_draw_fill_circle( worldPos.x, worldPos.y, 15, RGBA8( 0, 255, 0, 255 ) );

    // DEBUG
    Gui::drawTextf( 50, 340, 20, "worldPos.x = %.2f", worldPos.x );
    Gui::drawTextf( 50, 370, 20, "worldPos.y = %.2f", worldPos.y );
}

void Ball::stop()
{
    state = State::stationary;

    // Fix ball position
    worldPos.x -= tilePosOffset.x;
    worldPos.y -= tilePosOffset.y;

    tilePosOffset.x = 0;
    tilePosOffset.y = 0;
}

void Ball::moveUp()
{
    state = State::movingUp;
}
void Ball::moveRight()
{
    state = State::movingRight;
}
void Ball::moveDown()
{
    state = State::movingDown;
}
void Ball::moveLeft()
{
    state = State::movingLeft;
}

Rect Ball::getRect()
{
    return Rect(
        worldPos.x,
        worldPos.y,
        30,
        30
    );
}