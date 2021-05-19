#pragma once
#include <Windows.h>
#include "types.h"
#include "enums.h"
#include "main.h"

struct handle_data
{
	unsigned long processID;
	HWND windowHandle;
};

HWND find_main_window(unsigned long processID);
void DrawTextToScreen(const char *text, float x, float y, float scale, eFont font, bool alignRight = false, int red = 255, int green = 255, int blue = 255);
void ClipInt(int & value, int min, int max);
void ClipFloat(float & value, float min, float max);
Vector3 InitVector3(float value);
bool IsVersionSupportedForGlobals(eGameVersion ver);