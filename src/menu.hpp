#pragma once

#include <vector>
#include <string>

#include <vita2d.h>

#include "level.hpp"
#include "gui.hpp"
#include "input.hpp"
#include "sound.hpp"
#include "common.hpp"

class MenuItem
{
    public:
        MenuItem();
        MenuItem( Rect rect, std::string label );

        // Draw the menu item
        virtual void draw();

        // Draw the menu item the cursor is currently at
        virtual void drawSelected();

        virtual void handleInput() {}

        Rect getRect();

    protected:
        bool selected;
        Rect rect;
        std::string label;
};

class Menu
{
    public:
        Menu();

        void addItem( MenuItem * item );

        virtual void update();

        virtual void draw();

        // Returns cursor location
        int getCursor();

    protected:
        std::vector<MenuItem *> menuItems;
        int cursor;

        // Handles all input from user
        virtual void handleInput();

        // Returns true if the select button was pressed
        bool selectPressed();

        // Move the cursor
        void selectUp();
        void selectDown();
};


class MainMenu : public Menu
{
    public:
        MainMenu();

        void draw() override;

        // Returns true if the button was clicked
        bool clickedStart();
        bool clickedLevelSelect();
        bool clickedOptions();

    protected:
        void handleInput() override;
};


class OptionsMenu : public Menu
{
    public:
        OptionsMenu();

        void draw() override;
        void update() override;

        void loadOptions();
        void saveOptions();
        
    protected:
        float sfxVolume;
        float musicVolume;
};

class Checkbox : public MenuItem
{
    public:
        Checkbox( Rect rect, std::string label, bool selected );

        void draw() override;
        void drawSelected() override;

        bool selected;

    protected:
        void handleInput() override;
};

class Selectable : public MenuItem
{
    public:
        Selectable( Rect rect, std::string label, std::vector<std::string> items );

        void draw() override;
        void drawSelected() override;

    protected:
        void handleInput() override;

        std::vector<std::string> items;
};

class Slider : public MenuItem
{
    public:
        Slider( Rect rect, std::string label, float step );

        void draw() override;
        void drawSelected() override;

        float value;
    
    protected:
        void handleInput() override;

        
        float step;
};


class PauseMenu : public Menu
{
    public:
        PauseMenu();

        void draw() override;

        // Returns true if the button was clicked
        bool clickedResume();
        bool clickedRestart();
        bool clickedMainMenu();
};


class LevelFinish : public Menu
{
    public:
        LevelFinish();

        void draw() override;

        // Returns true if the button was clicked
        bool clickedNextLevel();
        bool clickedRestart();
        bool clickedMainMenu();

        void setStars( int stars );
        int stars;
};


class LevelSelect
{
    public:
        LevelSelect();

        void initLevels( LevelList * levelList, const char * name );
        void initStars();

        void update();
        void draw();

        // Returns cursor location (should be pointed at the level of the same number)
        int getCursor();

        // Returns true if the select button was pressed
        bool selectPressed();

        // Return true if the player has collected all the stars
        bool isGameComplete();

    protected:
        LevelList *levelList;
        int cursor;

        const char * name;

        // Handles all input from user
        void handleInput();

        // Move the cursor
        void selectUp();
        void selectRight();
        void selectDown();
        void selectLeft();

        Rect getItemRect( int i );

        // Screen spacing
        int paddingSide;
        int paddingTop;
        int columns;
        int itemWidth;
        int itemHeight;
        int spacing;

        // Stars stats
        int totalStars;
        int collectedStars;
};