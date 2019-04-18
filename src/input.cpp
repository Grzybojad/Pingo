#include "input.hpp"

namespace Input
{
    bool buttonIsHeld[ static_cast<int>( Button::count ) ];
    bool helperPressed[ static_cast<int>( Button::count ) ];
    bool buttonWasPressed[ static_cast<int>( Button::count ) ];
    SceCtrlData pad;
    SceTouchData touch_old[ SCE_TOUCH_PORT_MAX_NUM ];
    SceTouchData touch[ SCE_TOUCH_PORT_MAX_NUM ];

    void initInput()
    {
        sceCtrlSetSamplingMode( SCE_CTRL_MODE_ANALOG );
        memset( &pad, 0, sizeof( pad ) );

        sceTouchSetSamplingState( SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START );
        sceTouchSetSamplingState( SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START );
        sceTouchEnableTouchForce( SCE_TOUCH_PORT_FRONT );
        sceTouchEnableTouchForce( SCE_TOUCH_PORT_BACK );

        /* Button bools */
        for( int i = 0; i < static_cast<int>( Button::count ); ++i )
        {
            buttonIsHeld[ i ] = false;
            buttonWasPressed[ i ] = false;
        }
    }

    void handleInput()
    {
        sceCtrlPeekBufferPositive( 0, &pad, 1 );

        buttonIsHeld[ static_cast<int>( Button::select ) ] = ( pad.buttons & SCE_CTRL_SELECT );
        buttonIsHeld[ static_cast<int>( Button::start ) ] = ( pad.buttons & SCE_CTRL_START );

        buttonIsHeld[ static_cast<int>( Button::up ) ] = ( pad.buttons & SCE_CTRL_UP );
        buttonIsHeld[ static_cast<int>( Button::right ) ] = ( pad.buttons & SCE_CTRL_RIGHT );
        buttonIsHeld[ static_cast<int>( Button::down ) ] = ( pad.buttons & SCE_CTRL_DOWN );
        buttonIsHeld[ static_cast<int>( Button::left ) ] = ( pad.buttons & SCE_CTRL_LEFT );

        buttonIsHeld[ static_cast<int>( Button::lTrigger ) ] = ( pad.buttons & SCE_CTRL_LTRIGGER );
        buttonIsHeld[ static_cast<int>( Button::rTrigger ) ] = ( pad.buttons & SCE_CTRL_RTRIGGER );

        buttonIsHeld[ static_cast<int>( Button::triangle ) ] = ( pad.buttons & SCE_CTRL_TRIANGLE );
        buttonIsHeld[ static_cast<int>( Button::circle ) ] = ( pad.buttons & SCE_CTRL_CIRCLE );
        buttonIsHeld[ static_cast<int>( Button::cross ) ] = ( pad.buttons & SCE_CTRL_CROSS );
        buttonIsHeld[ static_cast<int>( Button::square ) ] = ( pad.buttons & SCE_CTRL_SQUARE );

        // Left analog stick
        float lAnalogX = (float)( ( pad.lx - 128.0f ) / 128.0f );
        float lAnalogY = (float)( ( pad.ly - 128.0f ) / 128.0f );
        buttonIsHeld[ static_cast<int>( Button::lAnalogUp ) ] = ( lAnalogY < -ANALOG_DEADZONE );
        buttonIsHeld[ static_cast<int>( Button::lAnalogRight ) ] = ( lAnalogX > ANALOG_DEADZONE );
        buttonIsHeld[ static_cast<int>( Button::lAnalogDown ) ] = ( lAnalogY > ANALOG_DEADZONE );
        buttonIsHeld[ static_cast<int>( Button::lAnalogLeft  ) ] = ( lAnalogX < -ANALOG_DEADZONE );

        // TODO Add touch checks

        for( int i = 0; i < static_cast<int>( Button::count ); ++i )
            buttonWasPressed[ i ] = checkPressed( i );
    }

    bool checkPressed( int i )
    {
        if( isHeld( static_cast<Button>( i ) ) && !helperPressed[ i ] )
        {
            helperPressed[ i ] = true;
            return true;
        }
        else if( !isHeld( static_cast<Button>( i ) ) )
        {
            helperPressed[ i ] = false;
        }

        return false;
    }

    bool isHeld( Button id )
    {
        return buttonIsHeld[ static_cast<int>( id ) ];
    }

    bool wasPressed( Button id )
    {
        return buttonWasPressed[ static_cast<int>( id ) ];
    }
}

