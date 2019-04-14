#include "ball.hpp"

Ball::Ball()
{
    state = State::stationary;

    worldPos.x = 0;
    worldPos.y = 0;

    ballSpeed = 12.0f;

    tileSize = 30;
}

Ball::~Ball()
{

}

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
        if( Input::wasPressed( Input::Button::up ) )
            moveUp();
        if( Input::wasPressed( Input::Button::right ) )
            moveRight();
        if( Input::wasPressed( Input::Button::down ) )
            moveDown();
        if( Input::wasPressed( Input::Button::left ) )
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
            break;

        case State::movingRight:
            worldPos.x += ballSpeed * timestep;
            break;

        case State::movingDown:
            worldPos.y += ballSpeed * timestep;
            break;

        case State::movingLeft:
            worldPos.x -= ballSpeed * timestep;
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
            worldPos.y += ballSpeed * timestep;
            break;

        case State::movingRight:
            worldPos.x -= ballSpeed * timestep;
            break;

        case State::movingDown:
            worldPos.y -= ballSpeed * timestep;
            break;

        case State::movingLeft:
            worldPos.x += ballSpeed * timestep;
            break;
    }
}

void Ball::draw()
{
    vita2d_draw_fill_circle( worldPos.x, worldPos.y, 15, RGBA8( 255, 0, 0, 255 ) );
}

void Ball::stop()
{
    state = State::stationary;
}

void Ball::reset()
{
    state = State::stationary;
    
    worldPos.x = 0;
    worldPos.y = 0;
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