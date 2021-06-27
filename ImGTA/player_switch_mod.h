/*
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "mod.h"
#include "utils.h"
#include "mission_mod.h"
#include "user_settings.h"

#include "types.h"

enum class SwitchType
{
	SWITCH_TYPE_AUTO = 0,
	SWITCH_TYPE_LONG = 1,
	SWITCH_TYPE_MEDIUM = 2,
	SWITCH_TYPE_SHORT = 3
};

struct SwitchArray {
	// Global_85405
	Vector3 field_0 = { 0 }; // 0
	Vector3 field_3 = { 0 }; // 3
	float field_6 = 0; // 6
	DWORD _padding6;
	int field_7 = 0; // 7
	DWORD _padding7;
	int field_8 = 0; // 8
	DWORD _padding8;
	int characterId = 0; // 9
	DWORD _padding9;
}; // Size 10 * 8 bytes

struct SwitchArray2 {
	// Global_85570
	Vector3 f_0;
	Vector3 f_3; // potential coords
	float f_6;
	DWORD _padding6;
	int f_7; // Looks like local_115.f_3 or f_2
	DWORD _padding7;
	int hospitalIndex; // 8
	DWORD _padding8;
}; // Size 9 * 8 bytes

struct SwitchArray3 {
	// Global_88210
	int f_2;
	int f_3;
	Vector3 f_4; // potential coords
	float f_7;
	//... UNFINISHED
}; // Size 109 * 8 bytes

struct SwitchArray4 {
	// Global_101149 -> Global_97353.f_1729.f_539.f_1528
	Vector3 f_0; // potential coords
}; // Size 3 * 8 bytes

struct SwitchArray5 {
	// Global_88538
	Vector3 f_0; // potential coords
}; // Size 3 * 8 bytes

struct SwitchArray6 {
	// Global_87845
	PaddedInt f_0[4]; // Entity ID
	CharacterID f_7;
	QWORD _padding[37];
	int f_44; // 55
	int f_45;
	int f_46;
}; // Not fininshed

struct SwitchLocationIdHistory {
	int size = 5;
	DWORD _padding;
	PaddedInt history[5];
}; // Size 6 * 8 bytes

struct SwitchArray7Bis {
	int size = 4;
	DWORD _padding0;
	PaddedInt field_0[4]; // Boolean values
};

struct SwitchArray7 {
	// Global_114140 -> Global_97353.f_16787
	int switchLocationId_size = 3; // 0
	DWORD _padding0;
	PaddedInt switchLocationId[3]; // 1
	int switchIdHistory_size = 3; // 4
	DWORD _padding4;
	SwitchLocationIdHistory switchIdHistory[3]; // 5
	std::bitset<64> field_23;
	int switchArray7BisSize = 3; // 24
	DWORD _padding24;
	SwitchArray7Bis switchArray7[3]; // 25
	int field_40; // boolean values 40
	DWORD _padding40;
}; // One element only: Size 1 * 8 bytes

struct SwitchArray8 {
	// Global_101145 -> Global_97353.f_1729.f_539.f_1524
	int randVal;
	DWORD _padding;
}; // Size 1 * 8 bytes

// Global_97353.f_16787
// local_115.f_3 // Global_87845.f_45
// Global_97353.f_1729.f_539.f_3213

std::string SwitchTypeStr(SwitchType type);

class PlayerSwitchMod : public Mod
{
public:
	PlayerSwitchMod(DLLObject & dllObject, bool supportGlobals);

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawMenuBar();
	void UpdateLocationData();
	CommonSettings & GetCommonSettings() override { return m_settings.common; }

	PlayerSwitchSettings m_settings;
	bool m_switchInProgress = false;
	int m_switchType = 0;
	int m_switchState = 0;
	int m_shortSwitchState = 0;
	int m_switchJumpCutIndex = 0;
	bool m_switchReadyForDescent = false;
	bool m_switchSkippingDescent = false;
	bool m_unkSwitch = false;
	bool m_unkSwitch2 = false;
	int m_switchInterpOutDuration = 0;
	int m_switchInterpOutCurrentTime = 0;


	int m_currentCharacterID = 0;
	int m_previousCharacterID = 0;

	GlobalArray<SwitchArray> m_gSwitch1;
	GlobalArray<SwitchArray2> m_gSwitch2;
	GlobalArray<SwitchArray4> m_gSwitch4;
	GlobalArray<SwitchArray5> m_gSwitch5;
	GlobalArray<SwitchArray8> m_gSwitch8;
	SwitchArray7 m_switch7;

	std::string m_dictName;
	std::string m_dictUseless1;
	std::string m_dictUseless2;
	
	// ImGui inputs / internals
	bool m_wantsUpdate = false;
	int m_locationID = 0;
	bool m_constantUpdate = true;
	char m_animDictInput[256] = "";
	char m_animNameInput[256] = "";
	unsigned int m_animFlags = 0;
	bool m_animLoop = false;
};
