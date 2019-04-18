#pragma once

#include <string.h> // for memset

#include <psp2/kernel/processmgr.h>
#include <psp2/touch.h>
#include <psp2/ctrl.h>

namespace Input
{
    enum class Button
    {
        select = 0,
        start = 1,

        up = 2,
        right = 3,
        down = 4,
        left = 5,
        
        lTrigger = 6,
        rTrigger = 7,

        triangle = 8,
        circle = 9,
        cross = 10,
        square = 11,

        lAnalogUp = 12,
        lAnalogRight = 13,
        lAnalogDown = 14,
        lAnalogLeft = 15,

        frontTouch = 16,
        backTouch = 17,

        count = 18
    };
    // Array with a bool for each button to store key presses
    extern bool buttonIsHeld[ static_cast<int>( Button::count ) ];
    extern bool helperPressed[ static_cast<int>( Button::count ) ];
    extern bool buttonWasPressed[ static_cast<int>( Button::count ) ];

    extern SceCtrlData pad;
    extern SceTouchData touch_old[ SCE_TOUCH_PORT_MAX_NUM ];
    extern SceTouchData touch[ SCE_TOUCH_PORT_MAX_NUM ];

    // Analog stick deadzone
    const float ANALOG_DEADZONE = 0.6f;

    // Initialize pad settings and variables
    void initInput();

    // Run in loop to handle all player input
    void handleInput();

    // Is the button held at this frame?
    bool isHeld( Button id );

    // Was the button pressed at this frame?
    bool wasPressed( Button id );

    // Helper function to find pressed buttons
    bool checkPressed( int i );
}