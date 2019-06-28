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
    Rect optionsPos = Rect( 50, 100, 250, 50 );
    int verticalSpacing = 80;

    addItem( new Slider( optionsPos, "SFX volume", 0.1f ) );
    optionsPos.y += verticalSpacing;
    addItem( new Slider( optionsPos, "Music volume", 0.1f ) );
    optionsPos.y += verticalSpacing;
    addItem( new Checkbox( optionsPos, "Enable touch", true ) );

    sfxVolume = 0.5f;
    musicVolume = 0.5f;
    enableTouchInMenu = true;
    enableTouchInGame = true;
}

void OptionsMenu::draw()
{
    for( int i = 0; i < menuItems.size(); ++i )
    {
        if( i == cursor )
            menuItems[ i ]->drawSelected();
        else 
            menuItems[ i ]->draw();
    }

    // Credits
    //Gui::drawText( 20, 40, 30, "Credits:\n\nDirecting, programming, level design:\n  Grzybojad\n\nArt assets:\n  Jumbocube\n\nTesting:\n  Grzybojad\n  JumboCube\n  RobDevs\n  dragnu5" );

    // Stats
    Gui::drawTextf_position( Gui::Position::alignTopRight, SCREEN_WIDTH - 20, 40, 30, "Stats:\n\nTime spend playing: %s\nTotal steps: %d\nTotal levels finished: %d", timeToString( Stats::timePlayed ).c_str(), Stats::totalSteps, Stats::totalLevelFinished );

    // "Go back" text
    Gui::drawText_position( Gui::Position::alignRight, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, 30, "Press O to go back" );
}

void OptionsMenu::update()
{
    handleInput();

    menuItems[ cursor ]->handleInput();

    Slider* sfxVolOption = dynamic_cast<Slider *>( menuItems[ 0 ] );
    Slider* musicVolOption = dynamic_cast<Slider *>( menuItems[ 1 ] ); 

    if( sfxVolume != sfxVolOption->getValue() )
    {
        sfxVolume = sfxVolOption->getValue();
        Sound::setSFXVolume( sfxVolume );
    }

    if( musicVolume != musicVolOption->getValue() )
    {
        musicVolume = musicVolOption->getValue();
        Sound::setMusicVolume( musicVolume );
    }
}

Checkbox::Checkbox( Rect rect, std::string label, bool selected ) : MenuItem( rect, label )
{
    this->selected = selected;
}

void Checkbox::draw()
{
    Gui::drawText_color_position( Gui::Position::alignTop, rect.x + 5, rect.y, 40, RGBA8( 0, 0, 0, 255 ), label.c_str() );

    if( selected )
        vita2d_draw_rectangle( rect.x + rect.w + 100, rect.y, 30, 30, RGBA8( 0, 255, 0, 255 ) );
    else
        vita2d_draw_rectangle( rect.x + rect.w + 100, rect.y, 30, 30, RGBA8( 255, 0, 0, 255 ) );
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

Selectable::Selectable( Rect rect, std::string label, std::vector<std::string> Selectable ) : MenuItem( rect, label )
{
    this->items = items;
}

void Selectable::draw()
{
    Gui::drawText_color_position( Gui::Position::alignTop, rect.x + 5, rect.y, 40, RGBA8( 0, 0, 0, 255 ), label.c_str() );

    // TODO
}

void Selectable::drawSelected()
{
    int border = 4;
    vita2d_draw_rectangle( rect.x, rect.y, rect.w, border, RGBA8( 255, 0, 0, 255 ) );
    vita2d_draw_rectangle( rect.x + rect.w - border, rect.y, border, rect.h, RGBA8( 255, 0, 0, 255 ) );
    vita2d_draw_rectangle( rect.x, rect.y + rect.h - border, rect.w, border, RGBA8( 255, 0, 0, 255 ) );
    vita2d_draw_rectangle( rect.x, rect.y, border, rect.h, RGBA8( 255, 0, 0, 255 ) );

    draw();
}

void Selectable::handleInput()
{
    // TODO
}

Slider::Slider( Rect rect, std::string label, float step ) : MenuItem( rect, label )
{
    this->step = step;

    // TODO load from file
    value = 0.5f;
}

void Slider::draw()
{
    Gui::drawText_color_position( Gui::Position::alignTop, rect.x + 5, rect.y, 40, RGBA8( 0, 0, 0, 255 ), label.c_str() );

    Gui::drawText_color_position( Gui::Position::alignTop, rect.x + rect.w + 100, rect.y, 40, RGBA8( 0, 0, 0, 255 ), ( std::to_string( (int)( round( value * 100 ) ) ) + "%" ).c_str() );

    // TODO
}

void Slider::drawSelected()
{
    int border = 4;
    vita2d_draw_rectangle( rect.x, rect.y, rect.w, border, RGBA8( 255, 0, 0, 255 ) );
    vita2d_draw_rectangle( rect.x + rect.w - border, rect.y, border, rect.h, RGBA8( 255, 0, 0, 255 ) );
    vita2d_draw_rectangle( rect.x, rect.y + rect.h - border, rect.w, border, RGBA8( 255, 0, 0, 255 ) );
    vita2d_draw_rectangle( rect.x, rect.y, border, rect.h, RGBA8( 255, 0, 0, 255 ) );

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

float Slider::getValue()
{
    return value;
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
    Gui::drawText_position( Gui::Position::centered, SCREEN_WIDTH / 2, 50, 60, name );

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
                    cursor = i + 1;
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
