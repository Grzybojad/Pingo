#include "credits.hpp"

Credits::Credits()
{
    
}

void Credits::init()
{
    fadePoint = 0;
    scrollPoint = 0;

    fadeSpeed = 1.0f;
    scrollSpeed = 0.8f;

    faded = false;
    end = false;

    length = SCREEN_HEIGHT;
    elements.push_back( 
        CreditsElement{ 
            length, 
            new CreditsLogo( 
                Texture::getTexture( Texture::Sprite::logo ) 
            ) 
        } 
    );
    length += elements[ 0 ].entity->getHeight();

    Sound::stopLevelMusic();
    Sound::soloud.play( Sound::airLock );
}

void Credits::update()
{
    if( fadePoint < 255 )
    {
        fadePoint += fadeSpeed * timestep;
        if( fadePoint > 255 )
        {
            fadePoint = 255;
            faded = true;
            Sound::soloud.play( Sound::creditsMusic );
        }
    }
    else if( scrollPoint < length )
    {
        scrollPoint += scrollSpeed * timestep;
    }
    else
    {
        end = true;
    }
}

void Credits::draw()
{
    vita2d_draw_rectangle( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGBA8( 0, 0, 0, (int)fadePoint ) );

    for( int i = 0; i < elements.size(); ++i )
    {
        if( elements[ i ].position > scrollPoint - elements[ i ].entity->getHeight() &&
            elements[ i ].position < scrollPoint + SCREEN_HEIGHT )
        {
            elements[ i ].entity->draw( elements[ i ].position - scrollPoint );
        }
    }
}

bool Credits::levelHasFaded()
{
    return faded;
}

bool Credits::haveEnded()
{
    return end;
}


int CreditsEntity::getHeight()
{
    return 0;
}

void CreditsEntity::draw( int height )
{

}


CreditsLogo::CreditsLogo( vita2d_texture* texture )
{
    logo = texture;
}

int CreditsLogo::getHeight()
{
    return vita2d_texture_get_height( logo );
}

void CreditsLogo::draw( int height )
{
    int width = vita2d_texture_get_width( logo );
    vita2d_draw_texture( logo, ( SCREEN_WIDTH - width )/2, height );
}