#include "ball.hpp"

Ball::Ball()
{
    state = State::stationary;

    tilePos.x = 0;
    tilePos.y = 0;
    worldPos.x = 0;
    worldPos.y = 0;

    ballSpeed = 5.0f;
}

Ball::~Ball()
{

}

void Ball::setTilePos( Vec2 spawnTile )
{
    tilePos = spawnTile;
}

void Ball::setWorldPos( Vec2 worldPos )
{
    this->worldPos = worldPos;
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
            worldPos.y -= ballSpeed;
            break;

        case State::movingRight:
            worldPos.x += ballSpeed;
            break;

        case State::movingDown:
            worldPos.y += ballSpeed;
            break;

        case State::movingLeft:
            worldPos.x -= ballSpeed;
            break;
    }
}

void Ball::moveBack()
{
    switch( state )
    {
        case State::stationary:
            break;

        case State::movingUp:
            worldPos.y += ballSpeed;
            break;

        case State::movingRight:
            worldPos.x -= ballSpeed;
            break;

        case State::movingDown:
            worldPos.y -= ballSpeed;
            break;

        case State::movingLeft:
            worldPos.x += ballSpeed;
            break;
    }
}

void Ball::draw()
{
    vita2d_draw_fill_circle( worldPos.x, worldPos.y, 10, RGBA8( 0, 255, 0, 255 ) );
}

void Ball::stop()
{
    state = State::stationary;
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