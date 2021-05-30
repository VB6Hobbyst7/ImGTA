/*
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "mod.h"
#include "types.h"
#include "strangers_and_freaks_names.h"
#include "utils.h"

#include <bitset>
#include <string>

struct MissionSettings;

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

struct MissionArray {
	// Global_81155
	char name[48] = { '\0' }; // 0
	uint64_t hash = 0; // 6
	int field_7 = 0; // 7
	DWORD _paddings7;
	char acronym[16] = { '\0' }; // 8
	int triggerId = 0; // 10
	DWORD _paddings10;
	int characterSetID = 0; // 11 or set of character (bit0: michael, bit1: franklin, bit2: trevor)
	int field_11b = 0;
	int field_12 = 0; // 12
	DWORD _paddings12;
	int timeframeStart = 0; // 13
	DWORD _paddings13;
	int timeframeEnd = 0; // 14
	DWORD _paddings14;
	std::bitset<64> field_15; // 15
	int field_16 = 0; // 16
	DWORD _paddings16;
	int field_17_size = 16; // 17 // Array size even though fixed size
	DWORD _paddings17;
	PaddedInt field_17[16]; // 17 // Fixed size
}; // Size 34 * 8 bytes

struct MissionArray2 {
	// Global_84352
	int field_1 = 0; // 0
	DWORD _paddings1;
	float field_2 = 0; // 1
	DWORD _paddings2;
}; // Size 2 * 8 bytes

struct MissionArray3 {
	// Global_24748
	int field_0_size = 3; // 0 // Fixed size
	DWORD _padding0;
	Vector3 positions[3]; // 1
	float field_10; // 10
	DWORD _padding10;
	std::bitset<64> field_11; // 11
	int sprite_id_size = 3; // 12
	DWORD _padding12;
	PaddedInt sprite_id[3]; // 12
	int field_13; // 13
	DWORD _padding13;
	int field_14; // 14
	DWORD _padding14;
	int field_15; // 15
	DWORD _padding15;
	int field_16; // 16 // Blip
	DWORD _padding16;
	char field_17[16] = { '\0' }; // 17 // text file
	int field_18; // 18
	DWORD _padding18;
}; // Size 23 * 8 bytes

struct MissionArray4Bis {
	int missionID; // 0
	DWORD _padding0;
	std::bitset<64> field_1; // 1
	float distanceSq; // 2
	DWORD _padding2;
	float distanceSq2; // 3
	DWORD _padding3;
	float distanceSq3; // 4
	DWORD _padding4;
	float distanceSq4; // 5
	DWORD _padding5;
	std::bitset<64> field_6; // possible bit 145 is accessed... size 192?
};

struct MissionArray4 {
	// Global_87300
	int isReady;
	DWORD _padding0;
	int field_1; // A boolean probably
	DWORD _padding1;
	int field_2;
	DWORD _padding2;
	int field_3;
	DWORD _padding3;
	int field_4; // If equal to 0, sets set_player_invincible
	DWORD _padding4;
	int missionID; // 5
	DWORD _padding5;
	int missionArray7ID;
	DWORD _padding6;
	int field_7;
	DWORD _padding7;
	int field_8; // Character that see it
	DWORD _padding8;
	int triggerID; // 9
	DWORD _padding9;
	MissionArray4Bis field_10; // 10
}; // Size 17 * 8 bytes

struct MissionArray5 {
	// Global_68623 -> Global_68514.f_109
	int missionArrayID; // MissionArrayID
	DWORD _padding0;
	int field_1;
	DWORD _padding1;
	int field_2;
	DWORD _padding2;
	int moneySpent; // Related to money spent because it's used to set 'money spent' stats
	DWORD _padding3;
}; // Size 4 * 8 bytes

struct MissionArray5Bis {
	// Global_75198 -> Global_68514.f_6684
	int f_0;
	DWORD _padding0;
	int f_1;
	DWORD _padding1;
	int f_2;
	DWORD _padding2;
	int f_3;
	DWORD _padding3;
	int f_4;
	DWORD _padding4;
	int f_5;
	DWORD _padding5;
	int f_6;
	DWORD _padding6;
	int f_7;
	DWORD _padding7;
	int f_8;
	DWORD _padding8;
	int f_9;
	DWORD _padding9;
	int f_10;
	DWORD _padding10;
	int f_11;
	DWORD _padding11;
	int f_12;
	DWORD _padding12;
	int f_13;
	DWORD _padding13;
}; // Size 14 * 8 bytes

struct MissionArray5Bis2 {
	// Global_72674 -> Global_68514.f_4160
	char scriptName[64];
	int stackSize;
	DWORD _padding8;
	int f_9;
	DWORD _padding9;
	int f_10;
	DWORD _padding10;
	int f_11;
	DWORD _padding11;
}; // Size 12 * 8 bytes

struct MissionArray5Bis3 {
	// Global_72104 -> Global_68514.f_3590
	int field_0;
	DWORD _padding0;
	int field_1; // 2
	DWORD _padding1;
}; // Size 2 * 8 bytes

struct MissionArray6 {
	// Global_75339 -> Global_68514.f_6825
	int hash; // 0
	DWORD _padding0;
	int missionArray10ID; // Index of Array10
	DWORD _padding1;
	int missionArray5ID; // 2 // Sometimes a weird multiple of 1000000 is added
	DWORD _padding2;
}; // Size 3 * 8 bytes

struct MissionArray7 {
	// Global_104696 -> Global_97353.f_7341.f_2
	std::bitset<64> field_0;
	int missionArray6ID;
	DWORD _padding1;
	int hash; // 2
	DWORD _padding2;
}; // Size 3 * 8 bytes

struct MissionArray8 {
	// Global_81040 -> Global_68514.f_12526
	int missionArray6IDMin;
	DWORD _padding0;
	int missionArray6IDMax;
	DWORD _padding1;
}; // Size 2 * 8 bytes

struct MissionArray9 {
	// Global_81119
	int missionArray5ID; // 0
	DWORD _padding0;
	std::bitset<64> f_1;
	int f_2;
	DWORD _padding2;
	int f_3; // 3
	DWORD _padding3;
	int threadId; // 4
	DWORD _padding4;
}; // Size 5 * 8 bytes

struct MissionArray10 {
	// Global_81106 -> Global_68514.f_12592
	int missionArray5ID; // 0
	DWORD _padding0;
}; // Size 1 * 8 bytes

struct MissionArray12 {
	// Global_84546
	char scriptName[128];
	int stackSize;
	DWORD _padding16;
	int scriptHash;
	DWORD _padding17;
}; // Size 18 * 8 bytes

struct StrangersAndFreaksArray2 {
	// Global_114181 -> Global_97353.f_16828
	std::bitset<64> f_0;
	int f_1; // Bool values
	DWORD _padding1;
	int f_2;
	DWORD _padding2;
	int f_3;
	DWORD _padding3;
	int f_4;
	DWORD _padding4;
	float f_5;
	DWORD _padding5;
};


class MissionMod : public Mod
{
public:
	MissionMod(DLLObject & dllObject, bool supportGlobals);

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawMenuBar();
	void ResetData();
	void UpdateMissionData();

	MissionSettings m_settings;
	GlobalArray<MissionArray> m_gMission1;
	GlobalArray<MissionArray2> m_gMission2;
	GlobalArray<MissionArray3> m_gMission3;
	GlobalArray<MissionArray4> m_gMission4;
	GlobalArray<MissionArray5> m_gMission5;
	GlobalArray<MissionArray5Bis> m_gMission5Bis;
	GlobalArray<MissionArray5Bis2> m_gMission5Bis2;
	GlobalArray<MissionArray5Bis3> m_gMission5Bis3;
	GlobalArray<MissionArray6> m_gMission6;
	GlobalArray<MissionArray7> m_gMission7;
	GlobalArray<MissionArray8> m_gMission8;
	GlobalArray<MissionArray9> m_gMission9;
	GlobalArray<MissionArray10> m_gMission10;
	GlobalArray<MissionArray12> m_gMission12;

	GlobalArray<StrangersAndFreaksArray> m_gSaf1;
	GlobalArray<StrangersAndFreaksArray2> m_gSaf2;

	bool m_updateSafArray = true;

	int m_availableMissionCount = 0;
	int m_missionState = 0;
	std::string m_deathName = "";
	int m_missionUnk0 = 0;
	int m_missionUnk68523 = 0;
	int m_missionUnk87289 = 0; // Mission ID used to check the available mission number by mission_triggerer
	int m_missionUnk87290 = 0; // Similar to Global_87290
	int m_missionUnk87298 = 0;
	int m_missionUnk81105 = 0; // An array 6 ID

	// ImGui inputs / internals
	bool m_wantsUpdate = false;
	bool m_constantUpdate = true;
	char m_animDictInput[256] = "";
	char m_animNameInput[256] = "";
	unsigned int m_animFlags = 0;
	bool m_animLoop = false;
};
