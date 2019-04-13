#pragma once

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 544;

struct Rect
{
    int x;
    int y;
    int w;
    int h;

    Rect() { }
    Rect( int x, int y, int w, int h )
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }
};

struct Vec2
{
    int x;
    int y;

    Vec2() { }
    Vec2( int x, int y )
    {
        this->x = x;
        this->y = y;
    }

    Rect toRect( int w, int h )
    {
        return Rect(
            x,
            y,
            w,
            h
        );
    }
};