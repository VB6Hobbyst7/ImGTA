#include <bitset>

#include "utils.h"
#include "natives.h"
#include "enums.h"
#include "mod.h"

BOOL is_main_window( HWND handle )
{
    return GetWindow( handle, GW_OWNER ) == ( HWND )0 && IsWindowVisible( handle );
}

BOOL CALLBACK enum_windows_callback( HWND handle, LPARAM lParam )
{
    handle_data &data = *( handle_data * )lParam;
    unsigned long process_id = 0;
    GetWindowThreadProcessId( handle, &process_id );
    if ( data.process_id != process_id || !is_main_window( handle ) )
        return TRUE;
    data.window_handle = handle;
    return FALSE;
}

// https://stackoverflow.com/questions/1888863/how-to-get-main-window-handle-from-process-id
HWND find_main_window( unsigned long process_id )
{
    handle_data data;
    data.process_id = process_id;
    data.window_handle = 0;
    EnumWindows( enum_windows_callback, ( LPARAM )&data );
    return data.window_handle;
}

void DrawTextToScreen( const char *text, float x, float y, float scale, eFont font, bool alignRight, int red, int green, int blue)
{
    HUD::SET_TEXT_FONT( ( int )font );
    HUD::SET_TEXT_SCALE( scale, scale );
    HUD::SET_TEXT_COLOUR( red, green, blue, 255 );
    HUD::SET_TEXT_WRAP( 0.0, 1.0 );
    HUD::SET_TEXT_CENTRE( false );
	HUD::SET_TEXT_RIGHT_JUSTIFY(alignRight);
    HUD::SET_TEXT_DROPSHADOW( 2, 2, 0, 0, 0 );
    HUD::SET_TEXT_EDGE( 1, 0, 0, 0, 205 );
    HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT( ( char * )"STRING" );
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME( ( char * )text );
    HUD::END_TEXT_COMMAND_DISPLAY_TEXT( x, y, 0 );
}

void ClipInt(int & value, int min, int max)
{
	if (value < min)
		value = min;
	else if (value > max) {
		if (max > min)
			value = max;
		else
			value = min;
	}
}

void ClipFloat(float & value, float min, float max)
{
	if (value < min)
		value = min;
	else if (value > max) {
		if (max > min)
			value = max;
		else
			value = min;
	}
}

const char * BoolToStr(bool value)
{
	return value ? "True" : "False";
}

Vector3 InitVector3(float value)
{
	Vector3 vec;
	vec.x = value;
	vec.y = value;
	vec.z = value;

	return vec;
}