#include "menu.hpp"

MenuItem::MenuItem()
{
    selected = false;

    rect.x = SCREEN_WIDTH / 2;
    rect.y = SCREEN_HEIGHT / 2;
    rect.w = 100;
    rect.h = 40;

    label = "NOT SET";
}

MenuItem::MenuItem( Rect rect, std::string label )
{
    selected = false;
    this->rect = rect;
    this->label = label;
}

void MenuItem::draw()
{
    // Placeholder
    vita2d_draw_rectangle( rect.x, rect.y, rect.w, rect.h, RGBA8( 200, 200, 200, 255 ) );
    Gui::drawText_position( Gui::Position::centered, rect.x + (rect.w / 2), rect.y + (rect.h / 2), rect.h / 2, label.c_str() );
}

void MenuItem::drawSelected()
{
    // Placeholder
    vita2d_draw_rectangle( rect.x, rect.y, rect.w, rect.h, RGBA8( 255, 117, 117, 255 ) );
    Gui::drawText_position( Gui::Position::centered, rect.x + (rect.w / 2), rect.y + (rect.h / 2), rect.h / 2, label.c_str() );
}

Rect MenuItem::getRect()
{
    return rect;
}


Menu::Menu()
{
    cursor = 0;
}

void Menu::addItem( MenuItem * item )
{
    menuItems.push_back( item );
}

void Menu::update()
{
    handleInput();
}

void Menu::handleInput()
{
    if( Input::wasPressed( Input::Button::up ) || Input::wasPressed( Input::Button::lAnalogUp ) )
        selectUp();
    if( Input::wasPressed( Input::Button::down ) || Input::wasPressed( Input::Button::lAnalogDown ) )
        selectDown();
}

void Menu::draw()
{
    for( int i = 0; i < menuItems.size(); ++i )
    {
        if( cursor == i )
            menuItems[ i ]->drawSelected();
        else
            menuItems[ i ]->draw();
    }
}

int Menu::getCursor()
{
    return cursor;
}

bool Menu::selectPressed()
{
    return Input::wasPressed( Input::Button::cross );
}

void Menu::selectUp()
{
    if( cursor > 0 )
        cursor--;
    else
        cursor = menuItems.size() - 1;

    Sound::soloud.play( Sound::menuMove );
}

void Menu::selectDown()
{
    if( cursor < menuItems.size() - 1 )
        cursor++;
    else
        cursor = 0;

    Sound::soloud.play( Sound::menuMove );
}


MainMenu::MainMenu()
{
    cursor = 0;
    int buttonWidth = 260;

    MenuItem * startButton = new MenuItem( Rect( 150, 230, 320, 128 ), "Start" );
    addItem( startButton );

    MenuItem * levelButton = new MenuItem( Rect( 265, 360, 270, 110 ), "Level Select" );
    addItem( levelButton );

    MenuItem * exitButton = new MenuItem( Rect( 660, 390, 250, 120 ), "Exit" );
    addItem( exitButton );
}

void MainMenu::draw()
{
    Texture::drawTexture( Texture::Sprite::logo, Vec2( 0, 0 ) );

    if( cursor == 0 )
        Texture::drawTexture( Texture::Sprite::startSelected, Vec2( 0, 0 ) );
    else
        Texture::drawTexture( Texture::Sprite::startButton, Vec2( 0, 0 ) );

    if( cursor == 1 )
        Texture::drawTexture( Texture::Sprite::levelSelectSelected, Vec2( 0, 0 ) );
    else
        Texture::drawTexture( Texture::Sprite::levelSelectButton, Vec2( 0, 0 ) );

    if( cursor == 2 )
        Texture::drawTexture( Texture::Sprite::optionsSelected, Vec2( 0, 0 ) );
    else
        Texture::drawTexture( Texture::Sprite::optionsButton, Vec2( 0, 0 ) );
}

void MainMenu::handleInput()
{
    if( Input::wasPressed( Input::Button::up ) || Input::wasPressed( Input::Button::lAnalogUp ) || Input::wasPressed( Input::Button::left ) || Input::wasPressed( Input::Button::lAnalogLeft ) )
        selectUp();
    if( Input::wasPressed( Input::Button::down ) || Input::wasPressed( Input::Button::lAnalogDown ) || Input::wasPressed( Input::Button::right ) || Input::wasPressed( Input::Button::lAnalogRight ) )
        selectDown();
}

bool MainMenu::clickedStart()
{
    if( selectPressed() && cursor == 0 )
        return true;

    if( Input::rectWasTouched( menuItems[ 0 ]->getRect() ) )
        return true;

    return false;
}

bool MainMenu::clickedLevelSelect()
{
    if( selectPressed() && cursor == 1 )
        return true;

    // Had to add more rects here, because the "buttons" are tilted
    if( Input::wasPressed( Input::Button::frontTouch ) )
        if( Input::rectIsTouched( menuItems[ 1 ]->getRect() ) ||
            Input::rectIsTouched( Rect( 520, 310, 215, 75 ) ) ||
            Input::rectIsTouched( Rect( 520, 387, 130, 35 ) ) )
            return true;

    return false;
}

bool MainMenu::clickedOptions()
{
    if( selectPressed() && cursor == 2 )
        return true;

    if( Input::wasPressed( Input::Button::frontTouch ) )
        if( Input::rectIsTouched( menuItems[ 2 ]->getRect() ) ||
            Input::rectIsTouched( Rect( 820, 320, 105, 75 ) ) ) // One more rect to cover the cog icon
            return true;

    return false;
}


OptionsMenu::OptionsMenu()
{
    Rect optionsPos = Rect( SCREEN_WIDTH / 2, 200, 100, 50 );

    addItem( new Slider( optionsPos, "SFX volume", 0.1f ) );
    optionsPos.y += 90;
    addItem( new Slider( optionsPos, "Music volume", 0.1f ) );
    optionsPos.y += 80;
    addItem( new Checkbox( optionsPos, "Enable touch", true ) );

    sfxVolume = 1.0f;
    musicVolume = 1.0f;
    ENABLE_TOUCH = true;
}

void OptionsMenu::draw()
{
    // Header
    Texture::drawTexture( Texture::Sprite::o_header, 320, 20 );

    switch( cursor )
    {
        case 0:
            Texture::drawTexture( Texture::Sprite::o_sfxOn, 20, menuItems[ 0 ]->getRect().y - 20 );
            break;
            
        case 1:
            Texture::drawTexture( Texture::Sprite::o_musicOn, 20, menuItems[ 1 ]->getRect().y - 10 );
            break;

        case 2:
            Texture::drawTexture( Texture::Sprite::o_touchOn, 20, menuItems[ 2 ]->getRect().y - 10 );
            break;  
        
        default:
            break;
    }

    Texture::drawTexture( Texture::Sprite::o_sfx, 20, menuItems[ 0 ]->getRect().y - 20 );
    Texture::drawTexture( Texture::Sprite::o_music, 20, menuItems[ 1 ]->getRect().y - 10 );
    Texture::drawTexture( Texture::Sprite::o_touch, 20, menuItems[ 2 ]->getRect().y - 10 );

    for( int i = 0; i < menuItems.size(); ++i )
    {
        menuItems[ i ]->draw();
    }

    // Credits
    //Gui::drawText( 20, 40, 30, "Credits:\n\nDirecting, programming, level design:\n  Grzybojad\n\nArt assets:\n  Jumbocube\n\nTesting:\n  Grzybojad\n  JumboCube\n  RobDevs\n  dragnu5" );

    // Stats
    Texture::drawTexture( Texture::Sprite::o_stats , Vec2( SCREEN_WIDTH - 280, 170 ) );
    Gui::drawTextf_position( Gui::Position::alignTopRight, SCREEN_WIDTH - 20, 200, 30, "Time: %s\nSteps: %d\nLevels finished: %d", timeToString( Stats::timePlayed ).c_str(), Stats::totalSteps, Stats::totalLevelFinished );

    // "Go back" text
    Gui::drawText_position( Gui::Position::alignRight, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, 30, "Press O to go back" );
}

void OptionsMenu::update()
{
    handleInput();

    menuItems[ cursor ]->handleInput();

    Slider* sfxVolOption = dynamic_cast<Slider *>( menuItems[ 0 ] );
    Slider* musicVolOption = dynamic_cast<Slider *>( menuItems[ 1 ] );
    Checkbox* enableTouchOption = dynamic_cast<Checkbox *>( menuItems[ 2 ] ); 

    if( sfxVolume != sfxVolOption->value )
    {
        sfxVolume = sfxVolOption->value;
        Sound::setSFXVolume( sfxVolume );
    }

    if( musicVolume != musicVolOption->value )
    {
        musicVolume = musicVolOption->value;
        Sound::setMusicVolume( musicVolume );
    }

    if( ENABLE_TOUCH != enableTouchOption->selected )
    {
        ENABLE_TOUCH = enableTouchOption->selected;
    }
}

void OptionsMenu::loadOptions()
{
    std::ifstream settings;
    settings.open( pathData + "settings.txt", std::ifstream::in );

    if( !settings.fail() )
    {
        settings >> sfxVolume;
        settings >> musicVolume;
        settings >> ENABLE_TOUCH;
    }
    else
    {
        sfxVolume = 1.0f;
        musicVolume = 1.0f;
        ENABLE_TOUCH = true;
    }

    settings.close();

    Slider* sfxVolOption = dynamic_cast<Slider *>( menuItems[ 0 ] );
    Slider* musicVolOption = dynamic_cast<Slider *>( menuItems[ 1 ] ); 
    Checkbox* enableTouchOption = dynamic_cast<Checkbox *>( menuItems[ 2 ] ); 

    sfxVolOption->value = sfxVolume;
    musicVolOption->value = musicVolume;
    enableTouchOption->selected = ENABLE_TOUCH;

    Sound::setSFXVolume( sfxVolume );
    Sound::setMusicVolume( musicVolume );
}

void OptionsMenu::saveOptions()
{
    std::ofstream settings;
    settings.open( pathData + "settings.txt" );

    settings << sfxVolume << "\n";
    settings << musicVolume << "\n";
    settings << ENABLE_TOUCH;

    settings.close();
}

Checkbox::Checkbox( Rect rect, std::string label, bool selected ) : MenuItem( rect, label )
{
    this->selected = selected;
}

void Checkbox::draw()
{
    if( selected )
        Texture::drawTexture( Texture::Sprite::o_checkboxOn, rect.x, rect.y );
    else
        Texture::drawTexture( Texture::Sprite::o_checkboxOff, rect.x, rect.y );
}

void Checkbox::drawSelected()
{
    int border = 4;
    vita2d_draw_rectangle( rect.x, rect.y, rect.w, border, RGBA8( 255, 0, 0, 255 ) );
    vita2d_draw_rectangle( rect.x + rect.w - border, rect.y, border, rect.h, RGBA8( 255, 0, 0, 255 ) );
    vita2d_draw_rectangle( rect.x, rect.y + rect.h - border, rect.w, border, RGBA8( 255, 0, 0, 255 ) );
    vita2d_draw_rectangle( rect.x, rect.y, border, rect.h, RGBA8( 255, 0, 0, 255 ) );

    draw();
}

void Checkbox::handleInput()
{
    if( Input::wasPressed( Input::Button::right ) || Input::wasPressed( Input::Button::lAnalogRight ) || 
        Input::wasPressed( Input::Button::left ) || Input::wasPressed( Input::Button::lAnalogLeft ) ||
        Input::wasPressed( Input::Button::cross ) )
        selected = !selected;
}

Slider::Slider( Rect rect, std::string label, float step ) : MenuItem( rect, label )
{
    this->step = step;

    value = 0.5f;
}

void Slider::draw()
{
    int cells = 10;
    int spacing = 30;
    int size = spacing * ( cells - 1 );
    for( int i = 0; i < cells; ++i )
    {
        if( i < (int)( round( value * cells ) ) )
            Texture::drawTexture( Texture::Sprite::o_sliderOn, rect.x + i * spacing - ( size / 2 ), rect.y );
        else
            Texture::drawTexture( Texture::Sprite::o_sliderOff, rect.x + i * spacing - ( size / 2 ), rect.y );
    }
}

void Slider::drawSelected()
{
    draw();
}

void Slider::handleInput()
{
    if( Input::wasPressed( Input::Button::right ) || Input::wasPressed( Input::Button::lAnalogRight ) )
    {
        if( value < 1 ) value += step;
        if( value > 1 ) value = 1;
        Sound::soloud.play( Sound::menuMove );
    }
    if( Input::wasPressed( Input::Button::left ) || Input::wasPressed( Input::Button::lAnalogLeft ) )
    {
        if( value > 0 ) value -= step;
        if( value < step ) value = 0;
        Sound::soloud.play( Sound::menuMove );
    }
}


PauseMenu::PauseMenu()
{
    cursor = 0;

    MenuItem * startButton = new MenuItem( Rect( 316, 250, 300, 100 ), "Resume" );
    addItem( startButton );

    MenuItem * restartButton = new MenuItem( Rect( 316, 350, 300, 78 ), "Restart" );
    addItem( restartButton );

    MenuItem * menuButton = new MenuItem( Rect( 316, 435, 300, 75 ), "Main menu" );
    addItem( menuButton );
}

void PauseMenu::draw()
{
    // Dim the screen
    vita2d_draw_rectangle( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGBA8( 0, 0, 0, 100 ) );

    Gui::drawText_color_position( Gui::Position::centered, SCREEN_WIDTH / 2, 100, 60, RGBA8( 0, 0, 0, 255 ), "Paused" );

    Texture::drawTexture( Texture::Sprite::p_pausedText, Vec2( 0, 0 ) );

    if( cursor == 0 )
        Texture::drawTexture( Texture::Sprite::p_returnSelected, Vec2( 0, 0 ) );
    else
        Texture::drawTexture( Texture::Sprite::p_return, Vec2( 0, 0 ) );
    if( cursor == 1 )
        Texture::drawTexture( Texture::Sprite::p_restartSelected, Vec2( 0, 0 ) );
    else
        Texture::drawTexture( Texture::Sprite::p_restart, Vec2( 0, 0 ) );   
    if( cursor == 2 )
        Texture::drawTexture( Texture::Sprite::p_menuSelected, Vec2( 0, 0 ) );
    else
        Texture::drawTexture( Texture::Sprite::p_menu, Vec2( 0, 0 ) );
}

bool PauseMenu::clickedResume()
{
    if( Input::wasPressed( Input::Button::circle ) || Input::wasPressed( Input::Button::start ) )
        return true;

    if( selectPressed() && cursor == 0 )
        return true;

    if( Input::rectWasTouched( menuItems[ 0 ]->getRect() ) )
        return true;

    return false;
}

bool PauseMenu::clickedRestart()
{
    if( selectPressed() && cursor == 1 )
        return true;

    if( Input::rectWasTouched( menuItems[ 1 ]->getRect() ) )
        return true;

    return false;
}

bool PauseMenu::clickedMainMenu()
{
    if( selectPressed() && cursor == 2 )
        return true;

    if( Input::rectWasTouched( menuItems[ 2 ]->getRect() ) )
        return true;

    return false;
}


LevelFinish::LevelFinish()
{
    cursor = 0;
    stars = 0;

    int buttonWidth = 260;

    MenuItem * nextButton = new MenuItem( Rect( 300, 255, 345, 110 ), "Next Level" );
    addItem( nextButton );

    MenuItem * restartButton = new MenuItem( Rect( 300, 365, 345, 78 ), "Try again" );
    addItem( restartButton );

    MenuItem * levelSelect = new MenuItem(Rect( 300, 443, 345, 75 ), "Main menu" );
    addItem( levelSelect );
}

void LevelFinish::draw()
{
    Texture::drawTexture( Texture::Sprite::lf_levelComplete, Vec2( 0, 0 ) );

    if( cursor == 0 )
        Texture::drawTexture( Texture::Sprite::lf_nextLevelSelected, Vec2( 0, 0 ) );
    else
        Texture::drawTexture( Texture::Sprite::lf_nextLevel, Vec2( 0, 0 ) );
    if( cursor == 1 )
        Texture::drawTexture( Texture::Sprite::lf_restartSelected, Vec2( 0, 0 ) );
    else
        Texture::drawTexture( Texture::Sprite::lf_restart, Vec2( 0, 0 ) );   
    if( cursor == 2 )
        Texture::drawTexture( Texture::Sprite::lf_menuSelected, Vec2( 0, 0 ) );
    else
        Texture::drawTexture( Texture::Sprite::lf_menu, Vec2( 0, 0 ) );

    int starHeight = 140;
    Texture::drawTexture( Texture::Sprite::star, Vec2( SCREEN_WIDTH / 2 - 125, starHeight ) );
    if( stars > 1 )
        Texture::drawTexture( Texture::Sprite::star, Vec2( SCREEN_WIDTH / 2 - 50, starHeight ) );
    if( stars > 2 )
        Texture::drawTexture( Texture::Sprite::star, Vec2( SCREEN_WIDTH / 2 + 25, starHeight ) );
}

bool LevelFinish::clickedNextLevel()
{
    if( selectPressed() && cursor == 0 )
        return true;

    if( Input::rectWasTouched( menuItems[ 0 ]->getRect() ) )
        return true;

    return false;
}

bool LevelFinish::clickedRestart()
{
    if( selectPressed() && cursor == 1 )
        return true;

    if( Input::rectWasTouched( menuItems[ 1 ]->getRect() ) )
        return true;

    return false;
}

bool LevelFinish::clickedMainMenu()
{
    if( selectPressed() && cursor == 2 )
        return true;

    if( Input::rectWasTouched( menuItems[ 2 ]->getRect() ) )
        return true;

    return false;
}

void LevelFinish::setStars( int stars )
{
    this->stars = stars;
}


LevelSelect::LevelSelect()
{
    cursor = 1;

    paddingSide = 40;
    paddingTop = 140;
    columns = 10;

    itemWidth = vita2d_texture_get_width( Texture::getTexture( Texture::Sprite::doorClosed ) );
    itemHeight = vita2d_texture_get_height( Texture::getTexture( Texture::Sprite::doorClosed ) );
    spacing = ( SCREEN_WIDTH - paddingSide * 2 - itemWidth * columns ) / ( columns - 1 );
}

void LevelSelect::initLevels( LevelList * levelList, const char * name )
{
    this->levelList = levelList;
    this->name = name;

    // Unlock the first level if it exitst
    if( levelList->getNrOfLevels() > 0 )
        if( !levelList->accessElement( 0 )->unlocked )
            levelList->accessElement( 0 )->unlocked = true;
}

void LevelSelect::initStars()
{
    collectedStars = 0;
    totalStars = 0;

    for( int i = 0; i < levelList->getNrOfLevels(); ++i )
    {
        collectedStars += levelList->accessElement( i )->stars;
        totalStars += 3;
    }
}

void LevelSelect::update()
{
    handleInput();
}

void LevelSelect::draw()
{
    if( strcmp( name, "World 1" ) == 0 )
    {
        Texture::drawTexture( Texture::Sprite::headerWorld, SCREEN_WIDTH / 2 - 140, 30 );
        Texture::drawTexture( Texture::Sprite::header1, SCREEN_WIDTH / 2 + 110, 20 );
    }
    else if( strcmp( name, "World 2" ) == 0 )
    {
        Texture::drawTexture( Texture::Sprite::headerWorld, SCREEN_WIDTH / 2 - 140, 30 );
        Texture::drawTexture( Texture::Sprite::header2, SCREEN_WIDTH / 2 + 110, 20 );
    }
    else
    {
        Gui::drawText_position( Gui::Position::centered, SCREEN_WIDTH / 2, 50, 60, name );
    }
        
    if( levelList->getNrOfLevels() > 0 )
    {
        for( int i = 0; i < levelList->getNrOfLevels(); ++i )
        {
            bool selected;
            if( ( i + 1 ) == cursor ) selected = true;
            else selected = false;

            levelList->accessElement( i )->drawLevelMenuElement( Vec2( getItemRect( i ) ), selected );
        }

        // Draw total star count
        Gui::drawTextf_position( Gui::Position::alignTopRight, SCREEN_WIDTH - 40, 10, 30, "%d/%d", collectedStars, totalStars );
        Texture::drawTexture_scale( Texture::Sprite::star, Vec2( SCREEN_WIDTH - 40, 15 ), 0.30 );
    }
    else
    {
        Gui::drawText_position( Gui::Position::centered, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 30, "No levels found" );
    }
}

int LevelSelect::getCursor()
{
    return cursor;
}

void LevelSelect::handleInput()
{
    if( levelList->getNrOfLevels() > 0 )
    {
        if( Input::wasPressed( Input::Button::up ) || Input::wasPressed( Input::Button::lAnalogUp ) )
            selectUp();
        if( Input::wasPressed( Input::Button::right ) || Input::wasPressed( Input::Button::lAnalogRight ) )
            selectRight();
        if( Input::wasPressed( Input::Button::down ) || Input::wasPressed( Input::Button::lAnalogDown ) )
            selectDown();
        if( Input::wasPressed( Input::Button::left ) || Input::wasPressed( Input::Button::lAnalogLeft ) )
            selectLeft();

        if( Input::isHeld( Input::Button::frontTouch ) )
        {
            for( int i = 0; i < levelList->getNrOfLevels(); ++i )
            {
                bool selected;
                if( ( i + 1 ) == cursor ) selected = true;
                else selected = false;

                if( !selected && Input::rectIsTouched( getItemRect( i ) ) )
                {
                    cursor = i + 1;
                    Sound::soloud.play( Sound::menuMove );
                }
            }
        }
    }
}

bool LevelSelect::selectPressed()
{
    if( levelList->getNrOfLevels() > 0 )
    {
        // Only allow loading unlocked levels
        if( levelList->accessElement( cursor - 1 )->unlocked )
        {
            if( Input::wasPressed( Input::Button::cross ) )
                return true;
            if( Input::rectWasTouched( getItemRect( cursor - 1 ) ) )
                return true;

            return false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool LevelSelect::isGameComplete()
{
    if( levelList->getNrOfLevels() > 0 )
        return ( collectedStars == totalStars );
    else
        return false;    
}

void LevelSelect::selectUp()
{
    if( levelList->getNrOfLevels() > columns )
    {
        if( cursor > columns )
            cursor -= columns;
        else
        {
            if( ( levelList->getNrOfLevels() ) % columns >= cursor )
                cursor = ( levelList->getNrOfLevels() ) - ( ( ( levelList->getNrOfLevels() ) % columns ) - cursor );
            else
                cursor += ( ( levelList->getNrOfLevels() ) / columns - 1 ) * columns;
        }
    }

    Sound::soloud.play( Sound::menuMove );
}

void LevelSelect::selectRight()
{
    if( cursor < levelList->getNrOfLevels() )
        cursor++;
    else
        cursor = 1;

    Sound::soloud.play( Sound::menuMove );
}

void LevelSelect::selectDown()
{
    if( cursor <= levelList->getNrOfLevels() - columns )
        cursor += columns;
    else
    {
        cursor %= columns;
        if( cursor < 1 ) cursor += columns;
    }
        
    Sound::soloud.play( Sound::menuMove );
}

void LevelSelect::selectLeft()
{
    if( cursor > 1 )
        cursor--;
    else
        cursor = levelList->getNrOfLevels();

    Sound::soloud.play( Sound::menuMove );
}

Rect LevelSelect::getItemRect( int i )
{
    int posX = paddingSide + ( ( i % columns ) * itemWidth ) + ( ( i % columns ) * spacing );
    int posY = paddingTop + ( ( i / columns ) * ( itemHeight + 20 ) );

    return Rect( posX, posY, itemWidth, itemHeight );
}
