#include "credits.hpp"

Credits::Credits()
{
    
}

void Credits::init()
{
    fadePoint = 0;
    scrollPoint = 0;

    fadeSpeed = 1.0f;
    scrollSpeed = 0.9f;

    faded = false;
    end = false;

    length = SCREEN_HEIGHT;

    addElement( new CreditsLogo( Texture::getTexture( Texture::Sprite::logo ) ) );
    addElement( new CreditsHeader( "Pingo development team" ) );
    addElement( new CreditsPerson( "Grzybojad", "Directing, Programming, Level Design, Gameplay Design" ) );
    addElement( new CreditsPerson( "Jumbocube", "Art" ) );
    addElement( new CreditsHeader( "Music" ) );
    addElement( new CreditsHeader( "Special thanks" ) );

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

void Credits::addElement( CreditsEntity* entity )
{
    elements.push_back( CreditsElement{ length, entity } );
    length += elements.back().entity->getHeight();
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
    return vita2d_texture_get_height( logo ) + paddingBottom;
}

void CreditsLogo::draw( int height )
{
    int width = vita2d_texture_get_width( logo );
    vita2d_draw_texture( logo, ( SCREEN_WIDTH - width )/2, height );
}


CreditsHeader::CreditsHeader( const char* text )
{
    this->text = text;
}

int CreditsHeader::getHeight()
{
    return Gui::getTextHeight( textSize, text ) + paddingBottom;
}

void CreditsHeader::draw( int height )
{
    Gui::drawText_color_position( Gui::Position::centeredTop, SCREEN_WIDTH/2, height, textSize, RGBA8( 255, 255, 255, 255 ), text );
}


CreditsPerson::CreditsPerson( const char* displayName, const char* role )
{
    this->displayName = displayName;
    this->role = role;
}

int CreditsPerson::getHeight()
{
    return Gui::getTextHeight( textSize, displayName ) + paddingBottom;
}

void CreditsPerson::draw( int height )
{
    Gui::drawText_color_position( Gui::Position::alignTopRight, SCREEN_WIDTH/2 - 50, height, textSize, RGBA8( 255, 255, 255, 255 ), displayName );
    Gui::drawText_color_position( Gui::Position::alignTop, SCREEN_WIDTH/2 + 50, height, textSize, RGBA8( 255, 255, 255, 255 ), role );
}