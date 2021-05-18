#pragma once
#include "mod.h"
#include "lua_engine.h"
#include "types.h"
#include "mission_mod.h"


enum class SwitchType {
	SWITCH_TYPE_AUTO = 0,
	SWITCH_TYPE_LONG = 1,
	SWITCH_TYPE_MEDIUM = 2,
	SWITCH_TYPE_SHORT = 3
};

struct LocationArray {
	// 0x14D9D
	Vector3 field_0 = { 0 }; // 0
	Vector3 field_1 = { 0 }; // 3
	float field_2 = 0; // 6
	DWORD _padding2;
	int field_3 = 0; // 7
	DWORD _padding3;
	int field_4 = 0; // 8
	DWORD _padding4;
	int field_5 = 0; // 9
	DWORD _padding5;
}; // Size 10 * 8 bytes

struct MessageArray {
	// 0x1F097 Global_17C49.f_744E
	int field_0; // Hash example 'ig_devin' -> Look in standard_global_reg for correspondance
	DWORD _padding0;
	int field_1;
	DWORD _padding1;
	int field_2;
	DWORD _padding2;
	char field_3[32];
	char field_7[32];
	int field_B;
	DWORD _paddingB;
	int field_C_size; // 4?
	DWORD _paddingC;
	PaddedInt field_C[4];
	int field_11;
	DWORD _padding11;
	int field_12;
	DWORD _padding12;
	int field_13_size = 4;
	DWORD _padding13;
	PaddedInt field_13[4];
	int field_18_size; // 4?
	DWORD _padding18;
	PaddedInt field_18[4];
}; // Size 29 * 8 bytes

struct MessageArray2 {
	// 0x61
}; // Size 


class PlayerSwitchMod : public Mod
{
public:
	PlayerSwitchMod(bool supportGlobals) : Mod("Player Switch", true, supportGlobals)
	{
		m_iWindowFlags = ImGuiWindowFlags_MenuBar;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	bool m_switchInProgress = false;
	int m_switchType = 0;
	int m_switchState = 0;
	int m_shortSwitchState = 0;

	int m_currentCharacterID = 0;
	int m_previousCharacterID = 0;

	LocationArray m_locationArray;
	int m_locationCount = 0;
	int m_locationArraySizeAddr = 0x14D9D;
	int m_locationArrayStartAddr = m_locationArraySizeAddr + 1;

	MessageArray m_characterArray;
	int m_characterID = 0;
	int m_characterCount = 0;
	int m_characterArraySizeAddr = 0x1F097;
	int m_characterArrayStartAddr = m_characterArraySizeAddr + 1;

	// ImGui inputs / internals
	bool m_bWantsUpdate = false;
	int m_locationID = 0;
	bool m_bConstantUpdate = true;
	char m_szAnimDictInput[256] = "";
	char m_szAnimNameInput[256] = "";
	unsigned int m_iAnimFlags = 0;
	bool m_bAnimLoop = false;

	void DrawMenuBar();
	void UpdateLocationData(bool once);
};
