#pragma once
#include "mod.h"
#include "lua_engine.h"
#include "types.h"
#include "mission_mod.h"

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
	MessageArray2 m_messageArray2;
	int m_characterID = 0;
	int m_messageArrayID2 = 0;
	int m_characterCount = 0;
	int m_messageArray2Count = 0;
	int m_characterArraySizeAddr = GlobalID::_127127;
	int m_characterArrayStartAddr = m_characterArraySizeAddr + 1;
	int m_messageArray2SizeAddr = GlobalID::_97;
	int m_messageArray2StartAddr = m_messageArray2SizeAddr + 1;

	std::string m_unk15750 = "";
	std::string m_unk15756 = "";

	// ImGui inputs / internals
	bool m_wantsUpdate = false;
	int m_locationID = 0;
	bool m_constantUpdate = true;
	char m_animDictInput[256] = "";
	char m_animNameInput[256] = "";
	unsigned int m_animFlags = 0;
	bool m_animLoop = false;
};
