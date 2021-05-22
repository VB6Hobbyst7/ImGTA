#pragma once
#include "mod.h"
#include "lua_engine.h"
#include "types.h"
#include "mission_mod.h"


enum class SwitchType
{
	SWITCH_TYPE_AUTO = 0,
	SWITCH_TYPE_LONG = 1,
	SWITCH_TYPE_MEDIUM = 2,
	SWITCH_TYPE_SHORT = 3
};

struct LocationArray
{
	// Global_85405
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

std::string SwitchTypeStr(SwitchType type);

class PlayerSwitchMod : public Mod
{
public:
	PlayerSwitchMod(bool supportGlobals) : Mod("Player Switch", true, supportGlobals)
	{
		m_windowFlags = ImGuiWindowFlags_MenuBar;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawMenuBar();
	void UpdateLocationData();

	bool m_switchInProgress = false;
	int m_switchType = 0;
	int m_switchState = 0;
	int m_shortSwitchState = 0;

	int m_currentCharacterID = 0;
	int m_previousCharacterID = 0;

	LocationArray m_locationArray;
	int m_locationCount = 0;
	int m_locationArraySizeAddr = GlobalID::_85405;
	int m_locationArrayStartAddr = m_locationArraySizeAddr + 1;
	
	// ImGui inputs / internals
	bool m_wantsUpdate = false;
	int m_locationID = 0;
	bool m_constantUpdate = true;
	char m_animDictInput[256] = "";
	char m_animNameInput[256] = "";
	unsigned int m_animFlags = 0;
	bool m_animLoop = false;
};
