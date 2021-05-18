#pragma once
#include "mod.h"
#include "lua_engine.h"
#include "types.h"


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
}; // 56 Bytes



class PlayerSwitchMod : public Mod
{
public:
	PlayerSwitchMod() : Mod("Player Switch", true)
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

	LocationArray m_locationArray;
	int m_locationCount = 0;
	int m_locationArraySizeAddr = 0x14D9D;
	int m_locationArrayStartAddr = m_locationArraySizeAddr + 1;

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
