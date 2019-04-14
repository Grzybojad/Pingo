#pragma once

#include <vector>
#include <string>

#include <vita2d.h>

#include "gui.hpp"
#include "input.hpp"
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

    protected:
        bool selected;
        Rect rect;
        std::string label;
};

class Menu
{
    public:
        Menu();

        void addItem( MenuItem item );

        void update();

        virtual void draw();

        // Returns cursor location
        int getCursor();

        // Returns select value
        bool selectPressed();

    protected:
        std::vector<MenuItem> menuItems;
        int cursor;

        // Is set to true if the select button was pressed
        bool select;

        // Handles all input from user
        void handleInput();

        // Move the cursor
        void selectUp();
        void selectDown();
};

class MainMenu : public Menu
{
    public:
        MainMenu();

        void draw() override;
};

class PauseMenu : public Menu
{
    public:
        PauseMenu();

        void draw() override;
};