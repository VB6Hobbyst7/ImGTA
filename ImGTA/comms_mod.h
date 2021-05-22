#pragma once
#include "mod.h"
#include "lua_engine.h"
#include "types.h"
#include "mission_mod.h"

struct MessageArray
{
	// Global_127127 Global_17C49.f_744E
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

// TODO
/*struct MessageArray2 {
	// Global_97
};*/ // Size 


class CommsMod : public Mod
{
public:
	CommsMod(bool supportGlobals) : Mod("Comms", true, supportGlobals)
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
		
	MessageArray m_characterArray;
	int m_characterID = 0;
	int m_characterCount = 0;
	int m_characterArraySizeAddr = GlobalID::_127127;
	int m_characterArrayStartAddr = m_characterArraySizeAddr + 1;

	// ImGui inputs / internals
	bool m_wantsUpdate = false;
	int m_locationID = 0;
	bool m_constantUpdate = true;
	char m_animDictInput[256] = "";
	char m_animNameInput[256] = "";
	unsigned int m_animFlags = 0;
	bool m_animLoop = false;
};
