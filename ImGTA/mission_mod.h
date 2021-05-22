#pragma once
#include "mod.h"
#include "types.h"
#include "global_id.h"

#include <bitset>
#include <string>

enum CharacterID { // Guess from standard_global_reg
	MICHAEL = 0,
	FRANKLIN = 1,
	TREVOR = 2,
	LAMAR = 3,
	JIMMY = 4,
	AMANDA = 5,
	FRIEND = 145
};

std::string CharacterSetIDStr(int characterSetID);
const char * CharacterIDStr(CharacterID id);


struct PaddedInt {
	int val = 0;
	DWORD _padding;
};

struct MissionArray {
	// Global_81155
	char name[48] = { '\0' }; // 0
	uint64_t hash = 0; // 6
	int field_2 = 0; // 7
	DWORD _paddings2;
	char acronym[16] = { '\0' }; // 8
	int trigger_id = 0; // A
	DWORD _paddings3;
	int characterSetID = 0; // B or set of character (bit0: michael, bit1: franklin, bit2: trevor)
	int field_4b = 0;
	int field_5 = 0; // C
	DWORD _paddings5;
	int timeframeStart = 0; // D
	DWORD _paddings6;
	int timeframeEnd = 0; // E
	DWORD _paddings7;
	std::bitset<64> field_8; // F
	int field_9 = 0; // 10
	DWORD _paddings9;
	int field_11_size = 16; // 11 // Array size even though fixed size
	DWORD _paddings10;
	PaddedInt field_11[16]; // Fixed size
}; // Size 34 * 8 bytes

struct MissionArray2 {
	// Global_84352
	int field_1 = 0;
	DWORD _paddings1;
	float field_2 = 0;
	DWORD _paddings2;
}; // Size 2 * 8 bytes

struct MissionArray3 {
	// Global_24748
	int field_0_size = 3; // 0 // Fixed size
	DWORD _padding0;
	Vector3 positions[3];
	float field_A;
	DWORD _paddingA;
	std::bitset<64> field_B; // B
	int sprite_id_size = 3; // C
	DWORD _paddingC;
	PaddedInt sprite_id[3]; // C
	int field_10;
	DWORD _padding10;
	int field_11;
	DWORD _padding11;
	int field_12;
	DWORD _padding12;
	int field_13; // Blip
	DWORD _padding13;
	char field_14[16] = { '\0' }; // text file
	int field_16;
	DWORD _padding16;
}; // Size 23 * 8 bytes

struct MissionArray4Bis {
	int field_0;
	DWORD _padding0;
	std::bitset<64> field_1;
	float field_2;
	DWORD _padding2;
	float field_3;
	DWORD _padding3;
	float field_4;
	DWORD _padding4;
	float field_5;
	DWORD _padding5;
	std::bitset<64> field_6; // possible bit 145 is accessed... size 192?
};

struct MissionArray4 {
	// Global_87300
	int isReady;
	DWORD _padding0;
	int field_1;
	DWORD _padding1;
	int field_2;
	DWORD _padding2;
	int field_3;
	DWORD _padding3;
	int field_4;
	DWORD _padding4;
	int missionID; // 5
	DWORD _padding5;
	int field_6;
	DWORD _padding6;
	int field_7;
	DWORD _padding7;
	int field_8; // Character that see it 
	DWORD _padding8;
	int triggerID; // 9
	DWORD _padding9;
	MissionArray4Bis field_A;
}; // Size 17 * 8 bytes

struct MissionArray5 {
	// Global_68623 -> Global_10BA2.f_6D
	int missionArrayID; // MissionArrayID
	DWORD _padding0;
	int field_1;
	DWORD _padding1;
	int field_2;
	DWORD _padding2;
	int field_3;
	DWORD _padding3;
}; // Size 4 * 8 bytes

struct MissionArray6 {
	// Global_75339 -> Global_10BA2.f_1AA9
	int hash;
	DWORD _padding0;
	int field_1;
	DWORD _padding1;
	int field_2;
	DWORD _padding2;
}; // Size 3 * 8 bytes

struct MissionArray7 {
	// Global_104696 -> Global_17C49.f_1CAD.f_2
	std::bitset<64> field_0;
	int field_1;
	DWORD _padding1;
	int field_2;
	DWORD _padding2;
}; // Size 3 * 8 bytes

class MissionMod : public Mod
{
public:
	MissionMod(bool supportGlobals) : Mod("Mission", true, supportGlobals)
	{
		m_windowFlags = ImGuiWindowFlags_MenuBar;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawMenuBar();
	void ResetData();
	void UpdateMissionData();

	MissionArray m_currentMission;
	MissionArray2 m_currentMission2;
	MissionArray3 m_mission3;
	MissionArray4 m_mission4;
	MissionArray5 m_mission5;
	MissionArray6 m_mission6;
	MissionArray7 m_mission7;
	int m_missionCount = 0;
	int m_mission3Size = 0;
	int m_mission4Size = 0;
	int m_mission5Size = 0;
	int m_mission6Size = 0;
	int m_mission7Size = 0;
	int m_missionArraySizeAddr = GlobalID::_81155;
	int m_missionArrayStartAddr = m_missionArraySizeAddr + 1;
	int m_missionArray2StartAddr = GlobalID::_84353;
	int m_missionArray3SizeAddr = GlobalID::_24748;
	int m_missionArray3StartAddr = m_missionArray3SizeAddr + 1;
	int m_missionArray4SizeAddr = GlobalID::_87300;
	int m_missionArray4StartAddr = m_missionArray4SizeAddr + 1;
	int m_missionArray5SizeAddr = GlobalID::_68623;
	int m_missionArray5StartAddr = m_missionArray5SizeAddr + 1;
	int m_missionArray6SizeAddr = GlobalID::_75339;
	int m_missionArray6StartAddr = m_missionArray6SizeAddr + 1;
	int m_missionArray7SizeAddr = GlobalID::_104696;
	int m_missionArray7StartAddr = m_missionArray7SizeAddr + 1;

	int m_availableMissionCount = 0;
	int m_missionState = 0;
	std::string m_deathName = "";
	int m_missionUnk0 = 0;
	int m_missionUnk1 = 0;

	// ImGui inputs / internals
	bool m_wantsUpdate = false;
	int m_missionID = 0;
	int m_missionID3 = 0;
	int m_missionID4 = 0;
	int m_missionID5 = 0;
	int m_missionID6 = 0;
	int m_missionID7 = 0;
	bool m_constantUpdate = true;
	char m_animDictInput[256] = "";
	char m_animNameInput[256] = "";
	unsigned int m_animFlags = 0;
	bool m_animLoop = false;
};
