/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <bitset>

#include "utils.h"
#include "natives.h"
#include "mod.h"

ThreadBasket threadBasket;

BOOL IsMainWindow(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	handle_data &data = *(handle_data *)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data.processID != process_id || !IsMainWindow(handle))
		return TRUE;
	data.windowHandle = handle;
	return FALSE;
}

// https://stackoverflow.com/questions/1888863/how-to-get-main-window-handle-from-process-id
HWND FindMainWindow(unsigned long process_id)
{
	handle_data data;
	data.processID = process_id;
	data.windowHandle = 0;
	EnumWindows(EnumWindowsCallback, (LPARAM)&data);
	return data.windowHandle;
}

void DrawTextToScreen(const char *text, float x, float y, float scale, eFont font, bool alignRight, int red, int green, int blue)
{
	// WARNING: Only the first 100 calls to this function are displayed!
	HUD::SET_TEXT_FONT((int)font);
	HUD::SET_TEXT_SCALE(scale, scale);
	HUD::SET_TEXT_COLOUR(red, green, blue, 255);
	HUD::SET_TEXT_WRAP(0.0, 1.0);
	HUD::SET_TEXT_CENTRE(false);
	HUD::SET_TEXT_RIGHT_JUSTIFY(alignRight);
	HUD::SET_TEXT_DROPSHADOW(2, 2, 0, 0, 0);
	HUD::SET_TEXT_EDGE(1, 0, 0, 0, 205);
	HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char *)"STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_KEYBOARD_DISPLAY((char *)text);
	HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
}

void ClipInt(int & value, int min, int max)
{
	if (value < min)
		value = min;
	else if (value > max)
	{
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
	else if (value > max)
	{
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

bool IsVersionSupportedForGlobals(eGameVersion ver)
{
	// Note: Assumed globals are the same in steam and nonsteam
	return ver == eGameVersion::VER_1_0_372_2_STEAM || ver == eGameVersion::VER_1_0_372_2_NOSTEAM;
}

bool InitThreadBasket()
{
	// 0x9B5BCD: offset to get to the mov instruction that contains the offset to the threads structure
	// 0x2A07D38: Offset to get the pointer to the ThreadBasket structure

	// (*(srcThreads))[0] -> Address to first thread script
	// (*srcThreads)[1] -> Address to second thread script

	// (*(*srcThreads)[0]) -> First script thread

	// (*(*srcThreads)[0]).pStack -> First script stack start address
	// *(*(*srcThreads)[0]).pStack + index) -> iLocal_index
	if (IsVersionSupportedForGlobals(getGameVersion()))
	{
		PVOID baseAddress = GetModuleHandleA("GTA5.exe");
		PVOID offsetAddress = (PVOID)((char*)baseAddress + 0x2A07D38);

		DWORD d, ds;
		VirtualProtect(offsetAddress, sizeof(ThreadBasket), PAGE_EXECUTE_READ, &d);
		memcpy(&threadBasket, offsetAddress, sizeof(ThreadBasket));
		VirtualProtect(offsetAddress, sizeof(ThreadBasket), d, &ds);
		return true;
	}
	else
		return false;
}

uint64_t * GetThreadAddress(int localId, int scriptHash)
{
	bool threadBasketLoaded = false;
	if (threadBasket.srcThreads == nullptr)
		threadBasketLoaded = InitThreadBasket();
	else
		threadBasketLoaded = true;

	uint64_t * localAddress = nullptr;
	if (threadBasketLoaded)
	{
		for (unsigned short i = 0; i < threadBasket.threadCount; i++)
		{
			ScrThread * scrThread = threadBasket.srcThreads[i];
			if (scrThread != nullptr && scrThread->pStack != nullptr)
			{
				if (scrThread->scriptHash == scriptHash)
				{
					localAddress = scrThread->pStack + localId;
					break;
				}
			}
		}
	}

	return localAddress;
}