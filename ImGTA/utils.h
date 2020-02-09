#pragma once
#include <Windows.h>
#include "types.h"
#include "enums.h"

struct handle_data
{
    unsigned long process_id;
    HWND window_handle;
};

HWND find_main_window( unsigned long process_id );
void DrawTextToScreen( const char *text, float x, float y, float scale, eFont font );