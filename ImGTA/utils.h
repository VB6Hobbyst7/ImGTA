#pragma once
#include <Windows.h>
#include "types.h"
#include "enums.h"
#include "main.h"
#include <cstdint>
#include <string>

struct handle_data
{
	unsigned long processID;
	HWND windowHandle;
};


struct ScrThread {
	uint64_t field_0; // 0
	int thread_id; // 8
	int scriptHash; // 12
	int field_3; // 16
	int field_4; // 20
	uint64_t frameSP; // 24
	uint64_t _padding[18]; // 32
	uint64_t * pStack = nullptr; // 176
	int _padding1; // 184
	int nParametersSize; // 188
	int nArgsOffset; // 192
	int _padding2; // 196
	uint64_t _padding3; // 200
	char scriptName[64]; // 208
	uint64_t _padding4[9]; // 272
}; // Size 344 Bytes


struct ThreadBasket {
	ScrThread ** srcThreads = nullptr; // 0
	unsigned short threadCount = 0; // 8
	unsigned short threadCapacity = 0; // 12
}; // 16 Bytes


HWND find_main_window(unsigned long processID);
void DrawTextToScreen(const char *text, float x, float y, float scale, eFont font, bool alignRight = false, int red = 255, int green = 255, int blue = 255);
void ClipInt(int & value, int min, int max);
void ClipFloat(float & value, float min, float max);
const char * BoolToStr(bool value);
Vector3 InitVector3(float value);
bool IsVersionSupportedForGlobals(eGameVersion ver);

// Thanks Parik (explanation on where and how to find addresses as well as thread structures...
//				 everything you see in these two functions)
// Thanks Gogsi123 (how to get the value from addresses in C++)
void InitThreadBasket();
uint64_t * GetThreadAddress(int localId, int scriptHash);