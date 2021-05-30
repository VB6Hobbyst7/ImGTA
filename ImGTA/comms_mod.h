/*
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "mod.h"
#include "types.h"
#include "utils.h"

struct CommsSettings;

struct MessageArray
{
	// Global_127127 -> Global_97353.f_29774
	int field_0; // Hash example 'ig_devin' -> Look in standard_global_reg for correspondance
	DWORD _padding0;
	int field_1;
	DWORD _padding1;
	int field_2;
	DWORD _padding2;
	char field_3[32];
	char field_7[32];
	int field_11; // 11
	DWORD _padding11;
	int field_12_size; // 12 // size 4?
	DWORD _padding12;
	PaddedInt field_12[4];
	int field_17; // 17
	DWORD _padding17;
	int field_18; // 18
	DWORD _padding18;
	int field_20_size = 4; // 19
	DWORD _padding20;
	PaddedInt field_20[4]; // 20
	int field_25_size; // 25 // size 4?
	DWORD _padding25;
	PaddedInt field_25[4];
}; // Size 29 * 8 bytes

struct MessageArray2 {
	// Global_97
	char f_0[32]; // 0
	char f_4[32]; // 3
	int f_8; // 8
	DWORD _padding8;
	int f_9; // 9
	DWORD _padding9;
}; // Size 10 * 8 bytes

struct MessageArray3 {
	// Global_2270
	char f_0[32];
	int f_4;
	DWORD _padding4;
	char scriptName[32];
	int scriptHash; // 9
	DWORD _padding9;
	int f_10;
	DWORD _padding10;
	int f_11;
	DWORD _padding11;
	int f_12;
	DWORD _padding12;
	int f_13;
	DWORD _padding13;
	int f_14;
	DWORD _padding14;
}; // Size 15 * 8 bytes

struct MessageArray4 {
	// Global_97353.f_23635
};

struct MessageArray5 {
	// Global_2873
	char f_0[32];
	int f_5;
	DWORD _padding5;
}; // Size 6 * 8 bytes

struct MessageArray6 {
	// Global_1683749
};

struct MessageArray7 {
	// Global_97353.f_12395
};

class CommsMod : public Mod
{
public:
	CommsMod(DLLObject & dllObject, bool supportGlobals);

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawMenuBar();
	void UpdateLocationData();

	CommsSettings m_settings;
	GlobalArray<MessageArray> m_gMessage1;
	GlobalArray<MessageArray2> m_gMessage2;
	GlobalArray<MessageArray3> m_gMessage3;

	std::string m_unk15750 = "";
	std::string m_unk15756 = "";

	// ImGui inputs / internals
	bool m_wantsUpdate = false;
	bool m_constantUpdate = true;
	char m_animDictInput[256] = "";
	char m_animNameInput[256] = "";
	unsigned int m_animFlags = 0;
	bool m_animLoop = false;
};
