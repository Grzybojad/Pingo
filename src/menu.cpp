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
    if( Input::wasPressed( Input::Button::up ) )
        selectUp();
    if( Input::wasPressed( Input::Button::down ) )
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
}

void Menu::selectDown()
{
    if( cursor < menuItems.size() - 1 )
        cursor++;
    else
        cursor = 0;
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
    Gui::drawText_color_position( Gui::Position::centered, SCREEN_WIDTH / 2, 100, 60, RGBA8( 0, 0, 0, 255 ), gameTitle );

    for( int i = 0; i < menuItems.size(); ++i )
    {
        if( cursor == i )
            menuItems[ i ].drawSelected();
        else
            menuItems[ i ].draw();
    }
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

    MenuItem startButton = MenuItem( Rect( SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT*0.6, 200, 70 ), "Resume" );
    addItem( startButton );

    MenuItem menuButton = MenuItem( Rect( SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT*0.8, 200, 70 ), "Main menu" );
    addItem( menuButton );
}

void PauseMenu::draw()
{
    // Dim the screen
    vita2d_draw_rectangle( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGBA8( 0, 0, 0, 100 ) );

    Gui::drawText_color_position( Gui::Position::centered, SCREEN_WIDTH / 2, 100, 60, RGBA8( 0, 0, 0, 255 ), "Paused" );

    for( int i = 0; i < menuItems.size(); ++i )
    {
        if( cursor == i )
            menuItems[ i ].drawSelected();
        else
            menuItems[ i ].draw();
    }
}

bool PauseMenu::clickedResume()
{
    return selectPressed() && cursor == 0;
}

bool PauseMenu::clickedMainMenu()
{
    return selectPressed() && cursor == 1;
}


LevelFinish::LevelFinish()
{
    cursor = 0;
    int buttonWidth = 260;

    MenuItem nextButton = MenuItem( Rect( SCREEN_WIDTH / 2 - ( buttonWidth / 2 ), SCREEN_HEIGHT*0.6, buttonWidth, 70 ), "Next Level" );
    addItem( nextButton );

    MenuItem levelSelect = MenuItem( Rect( SCREEN_WIDTH / 2 - ( buttonWidth / 2 ), SCREEN_HEIGHT*0.8, buttonWidth, 70 ), "Main menu" );
    addItem( levelSelect );
}

void LevelFinish::draw()
{
    Gui::drawText_color_position( Gui::Position::centered, SCREEN_WIDTH / 2, 100, 60, RGBA8( 0, 0, 0, 255 ), "Level complete!" );

    for( int i = 0; i < menuItems.size(); ++i )
    {
        if( cursor == i )
            menuItems[ i ].drawSelected();
        else
            menuItems[ i ].draw();
    }
}

bool LevelFinish::clickedNextLevel()
{
    return selectPressed() && cursor == 0;
}

bool LevelFinish::clickedMainMenu()
{
    return selectPressed() && cursor == 1;
}


LevelSelectItem::LevelSelectItem()
{
    rect = Rect(
        0,
        0,
        40,
        50
    );
}

LevelSelectItem::LevelSelectItem( Vec2 pos )
{
    rect = Rect(
        pos.x,
        pos.y,
        40,
        50
    );
}

LevelSelectItem::LevelSelectItem( Rect rect )
{
    this->rect = rect;
}

void LevelSelectItem::draw()
{
    
}

void LevelSelectItem::drawSelected()
{

}


LevelSelect::LevelSelect()
{
    cursor = 1;

    paddingSide = 40;
    paddingTop = 140;
    columns = 10;

    // TODO remove temp
    tempSize = 8;
}

void LevelSelect::initLevels( LevelList levelList )
{
    /*
    int spacing = ( SCREEN_WIDTH - paddingSide * 2 - itemWidth * columns ) / ( columns - 1 );

    rows = levelList.getNrOfLevels() / columns;
    if( levelList.getNrOfLevels() % columns != 0 )
        rows += 1;

    for( int i = 0; i < levelList.getNrOfLevels(); ++i )
    {
        LevelSelectItem newItem = LevelSelectItem( 
            Vec2(
                paddingSide + ( i * columns ) + ( i * spacing ),
                paddingTop,
            ),
        );
        menuItems.push_back( newItem );
    }

    rows = menuItems.size
    */
}

void LevelSelect::update()
{
    handleInput();
}

void LevelSelect::draw()
{
    Gui::drawTextf_position( Gui::Position::centered, SCREEN_WIDTH / 2, 50, 60, "Level select" );

    // TODO change
    int itemWidth = 70;
    int itemHeight = 90;

    int spacing = ( SCREEN_WIDTH - paddingSide * 2 - itemWidth * columns ) / ( columns - 1 );

    for( int i = 1; i <= tempSize; ++i )
    {
        int posX = paddingSide + ( ( ( i - 1 ) % columns ) * itemWidth ) + ( ( ( i - 1 ) % columns ) * spacing );
        int posY = paddingTop + ( ( ( i - 1 ) / columns ) * ( itemHeight + 40 ) );

        if( i == cursor)
            vita2d_draw_rectangle( posX, posY, itemWidth, itemHeight, RGBA8( 128, 0, 0, 255 ) );
        else
            vita2d_draw_rectangle( posX, posY, itemWidth, itemHeight, RGBA8( 0, 0, 0, 255 ) );

        Gui::drawTextf_color_position( Gui::Position::centeredX, posX + (itemWidth/2), posY + 45, 30, RGBA8( 255, 255, 255, 255 ), "%i", i );
    }
}

int LevelSelect::getCursor()
{
    return cursor;
}

void LevelSelect::handleInput()
{
    if( Input::wasPressed( Input::Button::up ) )
        selectUp();
    if( Input::wasPressed( Input::Button::right ) )
        selectRight();
    if( Input::wasPressed( Input::Button::down ) )
        selectDown();
    if( Input::wasPressed( Input::Button::left ) )
        selectLeft();
}

bool LevelSelect::selectPressed()
{
    return Input::wasPressed( Input::Button::cross );
}

void LevelSelect::selectUp()
{
    if( tempSize > columns )
    {
        if( cursor > columns )
            cursor -= columns;
        else
        {
            if( tempSize % columns >= cursor )
                cursor = tempSize - ( ( tempSize % columns ) - cursor );
            else
                cursor += ( ( tempSize + 1 ) / columns - 1 ) * columns;
        }
    }
}

void LevelSelect::selectRight()
{
    if( cursor < tempSize )//menuItems.size() )
        cursor++;
    else
        cursor = 1;
}

void LevelSelect::selectDown()
{
    if( cursor <= /*menuItems.size()*/ tempSize - columns )
        cursor += columns;
    else
        cursor %= columns;
}

void LevelSelect::selectLeft()
{
    if( cursor > 1 )
        cursor--;
    else
        cursor = /*menuItems.size()*/tempSize;
}