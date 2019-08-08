#include "credits.hpp"

Credits::Credits()
{
    
}

void Credits::init()
{
    fadePoint = 0;
    scrollPoint = 0;
    waitPoint = 0;

    fadeSpeed = 1.0f;
    scrollSpeed = 0.6f;

    faded = false;
    end = false;

    length = SCREEN_HEIGHT;
    waitTime = 1200.0f;

    addElement( new CreditsLogo( Texture::getTexture( Texture::Sprite::logo ) ) );

    addElement( new CreditsHeader( "Pingo development team" ) );
        addElement( new CreditsPerson( "Grzybojad", "Programming, Level Design" ) );
        addElement( new CreditsPerson( "Jumbocube", "Art" ) );

    addElement( new CreditsHeader( "Music" ) );
        addElement( new CreditsTextBlock( "All music comes from soundimage.org, composed by Eric Matyas." ) );

    addElement( new CreditsHeader( "Sound Effects" ) );
        addElement( new CreditsPerson( "wubitog", "Ball hit" ) );
        addElement( new CreditsPerson( "Kenney", "Menu click" ) );
        addElement( new CreditsPerson( "Brandon Morris", "Level finish" ) );
        addElement( new CreditsPerson( "soundimage.org", "Credits intro" ) );

    addElement( new CreditsHeader( "Special thanks" ) );
        addElement( new CreditsPerson( "Dragnu5", "Testing" ) );
        addElement( new CreditsPerson( "Xerpi", "LibVita2d" ) );
        addElement( new CreditsPerson( "VitaSDK team", "VitaSDK" ) );
        addElement( new CreditsTextBlock( "All the people on Discord who've helped me during development." ) );
        addElement( new CreditsTextBlock( "Extra Special thanks to RobDevs for creating pingo-edit. It was a massive help during development." ) );

    length += SCREEN_HEIGHT * 0.3;

    addElement( new CreditsHeader( "Disclaimer" ) );
        addElement( new CreditsTextBlock( "Pingo is a free, open source game distributed under the GPL-3.0 licence. If you paid for it, you've been scammed.") );

    addEmpty( SCREEN_HEIGHT * 0.5 );
    addElement( new CreditsTextBlock( "Thank you very much for playing Pingo! Beating the game is impressive enough, but can you get 3 stars on every level?" ) );
    addElement( new CreditsTextBlock( "If you got this far, feel free to contact me on Twitter (@_grzybojad) or on Discord (Grzybojad#7413). I'd love to know what you think about Pingo!" ) );
    addElement( new CreditsTextBlock( "TIP: try inputing the following button combination in the main menu: up, up, down, down, left, right, left, right, circle, cross.") );
    
    // This stops the scrolling 400 pixels earlier
    addEmpty( -400 );

    Sound::stopLevelMusic();
    Sound::soloud.play( Sound::airLock );
}

void Credits::update()
{
    handleInput();

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
    else if( waitPoint < waitTime )
    {
        waitPoint += timestep;
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

void Credits::addEmpty( int height )
{
    length += height;
}

void Credits::handleInput()
{
    if( Input::isHeld( Input::Button::cross ) )
        scrollSpeed = 3.0f;
    else
        scrollSpeed = 0.9f;
    
    if( Input::wasPressed( Input::Button::start ) )
        end = true;
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
    return vita2d_texture_get_height( logo ) + paddingBottom + paddingTop;
}

void CreditsLogo::draw( int height )
{
    int width = vita2d_texture_get_width( logo );
    vita2d_draw_texture( logo, ( SCREEN_WIDTH - width )/2, height + paddingTop );
}


CreditsHeader::CreditsHeader( const char* text )
{
    this->text = text;
}

int CreditsHeader::getHeight()
{
    return Gui::getTextHeight( textSize, text ) + paddingBottom + paddingTop;
}

void CreditsHeader::draw( int height )
{
    Gui::drawText_color_position( Gui::Position::centeredTop, SCREEN_WIDTH/2, height + paddingTop, textSize, RGBA8( 255, 255, 255, 255 ), text );
}


CreditsPerson::CreditsPerson( const char* displayName, const char* role )
{
    this->displayName = displayName;
    this->role = role;
}

CreditsPerson::CreditsPerson( const char* displayName )
{
    this->displayName = displayName;
    this->role = "";
}

int CreditsPerson::getHeight()
{
    return Gui::getTextHeight( textSize, displayName ) + paddingBottom;
}

void CreditsPerson::draw( int height )
{
    if( role == "" )
    {
        Gui::drawText_color_position( Gui::Position::centeredTop, SCREEN_WIDTH/2, height, textSize, RGBA8( 255, 255, 255, 255 ), displayName );
    }
    else
    {
        Gui::drawText_color_position( Gui::Position::alignTopRight, SCREEN_WIDTH/2 - spacing, height, textSize, RGBA8( 255, 255, 255, 255 ), role );
        Gui::drawText_color_position( Gui::Position::alignTop, SCREEN_WIDTH/2 + spacing, height, textSize, RGBA8( 255, 255, 255, 255 ), displayName );
    }
}


CreditsTextBlock::CreditsTextBlock( const char* text )
{
    this->text = text;
}

int CreditsTextBlock::getHeight()
{
    return Gui::getTextHeight( textSize, word_wrap( text, perLine ).c_str() ) + paddingBottom;
}

void CreditsTextBlock::draw( int height )
{
    Gui::drawText_color_position( Gui::Position::centeredTop, SCREEN_WIDTH/2, height - 30, textSize, RGBA8( 255, 255, 255, 255 ), word_wrap( text, perLine ).c_str() );
}