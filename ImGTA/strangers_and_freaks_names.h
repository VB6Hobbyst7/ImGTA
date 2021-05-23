#pragma once
// Functions taken GTA V decompiled scripts... For some reason the strangers and freaks data is not stored in Globals...

struct Char16Byte{
	char str[64];
};

struct Char24Byte {
	char str[64];
};

struct StrangersAndFreaksArray {
	Char16Byte f_0;
	Char16Byte f_1;
	int f_3;
	int f_4;
	int f_5;
	float f_6[3];
	int f_9;
	Char16Byte f_10;
	int f_14;
	int f_15;
	Char24Byte f_16;
	int f_22;
	int f_23;
	int f_24;
	int f_25;
	int f_26;
	int f_27;
	int f_28;
	int f_29;
	int f_30;
	int f_31;
};

void GetStrangersAndFreaksArray(int iParam0, StrangersAndFreaksArray & uParam1);
void func_12(StrangersAndFreaksArray & uParam0, const char* sParam1, Char16Byte Param2, int iParam4, int iParam5, int iParam6, float Param7_x, float Param7_y, float Param7_z, int iParam10, const char * sParam11, int iParam12, int iParam13, const char* sParam14, int iParam15, int iParam16, int iParam17, int iParam18, int iParam19, int iParam20, int iParam21, int uParam22, int iParam23, int iParam24);
int func_13(int iParam0);
Char16Byte func_14(int iParam0);
Char16Byte func_15(int iParam0);