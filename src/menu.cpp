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
    vita2d_draw_rectangle( rect.x, rect.y, rect.w, rect.h, RGBA8( 255, 255, 255, 255 ) );
    Gui::drawText_position( Gui::Position::centered, rect.x + (rect.w / 2), rect.y + (rect.h / 2), rect.h / 2, label.c_str() );
}

void MenuItem::drawSelected()
{
    // Placeholder
    vita2d_draw_rectangle( rect.x, rect.y, rect.w, rect.h, RGBA8( 255, 0, 0, 255 ) );
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
    if( cursor < menuItems.size() - 1 )
        cursor++;
    else
        cursor = 0;
}

void Menu::selectDown()
{
    if( cursor > 0 )
        cursor--;
    else
        cursor = menuItems.size() - 1;
}


MainMenu::MainMenu()
{
    cursor = 0;

    MenuItem startButton = MenuItem( Rect( SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT*0.6, 200, 70 ), "Start" );
    addItem( startButton );

    MenuItem exitButton = MenuItem( Rect( SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT*0.8, 200, 70 ), "Exit" );
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

bool MainMenu::clickedExit()
{
    return selectPressed() && cursor == 1;
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

    MenuItem nextButton = MenuItem( Rect( SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT*0.6, 200, 70 ), "Next Level" );
    addItem( nextButton );

    MenuItem menuButton = MenuItem( Rect( SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT*0.8, 200, 70 ), "Main menu" );
    addItem( menuButton );
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


LevelSelect::LevelSelect()
{
    cursor.x = 0;
    cursor.y = 0;
}

void LevelSelect::initLevels( LevelList levelList )
{
    int paddingSide = 40;
    int paddingTop = 80;
    int itemWidth = 30;
    int itemHeight = 60;

    int columns = 8;

    int spacing = ( SCREEN_WIDTH - paddingSide * 2 - itemWidth * columns ) / ( columns - 1 );


    for( int i = 0; i < levelList.getNrOfLevels(); ++i )
    {
        LevelSelectItem newItem = LevelSelectItem( 
            Rect(
                paddingSide + ( i * columns ) + ( i * spacing ),
                paddingTop,
                itemWidth,
                itemHeight
            ),
            std::to_string( i )
        );
        menuItems.push_back( newItem );
    }
}

void LevelSelect::update()
{
    
}

void LevelSelect::draw()
{

}

void LevelSelect::selectUp()
{

}

void LevelSelect::selectRight()
{

}

void LevelSelect::selectDown()
{

}

void LevelSelect::selectLeft()
{

}


LevelSelectItem::LevelSelectItem()
{

}

LevelSelectItem::LevelSelectItem( Rect rect, std::string label )
{

}

void LevelSelectItem::draw()
{
    
}

void LevelSelectItem::drawSelected()
{

}