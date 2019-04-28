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


Menu::Menu()
{
    cursor = 0;
}

void Menu::addItem( MenuItem item )
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
            menuItems[ i ].drawSelected();
        else
            menuItems[ i ].draw();
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

    MenuItem startButton = MenuItem( Rect( SCREEN_WIDTH / 2 - ( buttonWidth / 2 ), SCREEN_HEIGHT*0.4, buttonWidth, 70 ), "Start" );
    addItem( startButton );

    MenuItem levelButton = MenuItem( Rect( SCREEN_WIDTH / 2 - ( buttonWidth / 2 ), SCREEN_HEIGHT*0.6, buttonWidth, 70 ), "Level Select" );
    addItem( levelButton );

    MenuItem exitButton = MenuItem( Rect( SCREEN_WIDTH / 2 - ( buttonWidth / 2 ), SCREEN_HEIGHT*0.8, buttonWidth, 70 ), "Exit" );
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
    return selectPressed() && cursor == 0;
}

bool MainMenu::clickedLevelSelect()
{
    return selectPressed() && cursor == 1;
}

bool MainMenu::clickedExit()
{
    return selectPressed() && cursor == 2;
}


PauseMenu::PauseMenu()
{
    cursor = 0;

    MenuItem startButton = MenuItem( Rect( SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT * 0.55, 200, 70 ), "Resume" );
    addItem( startButton );

    MenuItem restartButton = MenuItem( Rect( SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT * 0.7, 200, 70 ), "Restart" );
    addItem( restartButton );

    MenuItem menuButton = MenuItem( Rect( SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT * 0.85, 200, 70 ), "Main menu" );
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
    return selectPressed() && cursor == 0;
}

bool PauseMenu::clickedRestart()
{
    return selectPressed() && cursor == 1;
}

bool PauseMenu::clickedMainMenu()
{
    return selectPressed() && cursor == 2;
}


LevelFinish::LevelFinish()
{
    cursor = 0;
    stars = 0;

    int buttonWidth = 260;

    MenuItem nextButton = MenuItem( Rect( SCREEN_WIDTH / 2 - ( buttonWidth / 2 ), SCREEN_HEIGHT*0.5, buttonWidth, 70 ), "Next Level" );
    addItem( nextButton );

    MenuItem restartButton = MenuItem( Rect( SCREEN_WIDTH / 2 - ( buttonWidth / 2 ), SCREEN_HEIGHT*0.65, buttonWidth, 70 ), "Try again" );
    addItem( restartButton );

    MenuItem levelSelect = MenuItem( Rect( SCREEN_WIDTH / 2 - ( buttonWidth / 2 ), SCREEN_HEIGHT*0.8, buttonWidth, 70 ), "Main menu" );
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
    return selectPressed() && cursor == 0;
}

bool LevelFinish::clickedRestart()
{
    return selectPressed() && cursor == 1;
}

bool LevelFinish::clickedMainMenu()
{
    return selectPressed() && cursor == 2;
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
}

void LevelSelect::initLevels( LevelList *levelList )
{
    this->levelList = levelList;

    // Unlock the first level
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
    Gui::drawText_position( Gui::Position::centered, SCREEN_WIDTH / 2, 50, 60, "Level select" );

    int itemWidth = 70;
    int itemHeight = 90;
    int spacing = ( SCREEN_WIDTH - paddingSide * 2 - itemWidth * columns ) / ( columns - 1 );

    for( int i = 0; i < levelList->getNrOfLevels(); ++i )
    {
        int posX = paddingSide + ( ( i % columns ) * itemWidth ) + ( ( i % columns ) * spacing );
        int posY = paddingTop + ( ( i / columns ) * ( itemHeight + 40 ) );
        bool selected;
        if( ( i + 1 ) == cursor ) selected = true;
        else selected = false;

        levelList->accessElement( i )->drawLevelMenuElement( Vec2( posX, posY ), selected );
    }

    // Draw total star count
    Gui::drawTextf_position( Gui::Position::alignTopRight, SCREEN_WIDTH - 40, 10, 30, "%d/%d", collectedStars, totalStars );
    Texture::drawTexture_scale( Texture::Sprite::star, Vec2( SCREEN_WIDTH - 40, 15 ), 0.30 );
}

int LevelSelect::getCursor()
{
    return cursor;
}

void LevelSelect::handleInput()
{
    if( Input::wasPressed( Input::Button::up ) || Input::wasPressed( Input::Button::lAnalogUp ) )
        selectUp();
    if( Input::wasPressed( Input::Button::right ) || Input::wasPressed( Input::Button::lAnalogRight ) )
        selectRight();
    if( Input::wasPressed( Input::Button::down ) || Input::wasPressed( Input::Button::lAnalogDown ) )
        selectDown();
    if( Input::wasPressed( Input::Button::left ) || Input::wasPressed( Input::Button::lAnalogLeft ) )
        selectLeft();
}

bool LevelSelect::selectPressed()
{
    // Only allow loading unlocked levels
    if( levelList->accessElement( cursor - 1 )->unlocked )
    {
        return Input::wasPressed( Input::Button::cross );
    }
    else
    {
        return false;
    }
}

bool LevelSelect::isGameComplete()
{
    return ( collectedStars == totalStars );
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
        cursor %= columns;

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