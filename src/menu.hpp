#pragma once

#include <vector>
#include "common.hpp"

class MenuItem
{
    public:
        MenuItem();
        
        virtual void click();

        virtual void draw();

    protected:
        bool selected;
        Vec2 pos;
};

class Menu
{
    public:
        Menu();

        void draw();

    protected:
        std::vector<MenuItem> menuItems;

};