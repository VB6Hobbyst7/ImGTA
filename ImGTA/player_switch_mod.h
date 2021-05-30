/*
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "mod.h"
#include "types.h"
#include "utils.h"

struct PlayerSwitchSettings;

enum class SwitchType
{
	SWITCH_TYPE_AUTO = 0,
	SWITCH_TYPE_LONG = 1,
	SWITCH_TYPE_MEDIUM = 2,
	SWITCH_TYPE_SHORT = 3
};

struct SwitchArray
{
	// Global_85405
	Vector3 field_0 = { 0 }; // 0
	Vector3 field_3 = { 0 }; // 3
	float field_6 = 0; // 6
	DWORD _padding6;
	int field_7 = 0; // 7
	DWORD _padding7;
	int field_8 = 0; // 8
	DWORD _padding8;
	int field_9 = 0; // 9
	DWORD _padding9;
}; // Size 10 * 8 bytes

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

	PlayerSwitchSettings m_settings;
	bool m_switchInProgress = false;
	int m_switchType = 0;
	int m_switchState = 0;
	int m_shortSwitchState = 0;

	int m_currentCharacterID = 0;
	int m_previousCharacterID = 0;

	GlobalArray<SwitchArray> m_gSwitch1;
	
	// ImGui inputs / internals
	bool m_wantsUpdate = false;
	int m_locationID = 0;
	bool m_constantUpdate = true;
	char m_animDictInput[256] = "";
	char m_animNameInput[256] = "";
	unsigned int m_animFlags = 0;
	bool m_animLoop = false;
};
