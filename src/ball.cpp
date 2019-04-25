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

bool Ball::handleInput()
{
    bool wasPressed = false;

    if( state == State::stationary )
    {
        wasPressed = true;

        if( Input::wasPressed( Input::Button::up ) || Input::wasPressed( Input::Button::lAnalogUp ) )
            moveUp();
        else if( Input::wasPressed( Input::Button::right ) || Input::wasPressed( Input::Button::lAnalogRight ) )
            moveRight();
        else if( Input::wasPressed( Input::Button::down ) || Input::wasPressed( Input::Button::lAnalogDown ) )
            moveDown();
        else if( Input::wasPressed( Input::Button::left ) || Input::wasPressed( Input::Button::lAnalogLeft ) )
            moveLeft();
        else
            wasPressed = false;
    }

    return wasPressed;
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
    Texture::drawTexture( Texture::Sprite::ball, Vec2( worldPos.x - 15, worldPos.y - 15 ) );
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