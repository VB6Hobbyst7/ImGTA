#include "mission_mod.h"
#include "natives.h"
#include "script.h"
#include "imgui.h"
#include "main.h"
#include "utils.h"
#include "watch_entry.h"
#include "imgui_extras.h"
#include "global_id.h"


void MissionMod::Load()
{

}

void MissionMod::Unload()
{

}

void MissionMod::Think()
{
	if (m_constantUpdate || m_wantsUpdate)
	{
		UpdateMissionData();
		m_wantsUpdate = false;
	}
}

void MissionMod::ResetData()
{
	m_missionCount = 0;
	m_currentMission.name[0] = '\0';
	m_currentMission.hash = 0;
	m_currentMission.acronym[0] = '\0';
	m_currentMission.triggerId = 0;
	m_currentMission.characterSetID = 0;
	m_currentMission.field_12 = 0;
	m_currentMission.timeframeStart = 0;
	m_currentMission.timeframeEnd = 0;
	m_currentMission.field_15 = 0;

	m_currentMission2.field_1 = 0;
	m_currentMission2.field_2 = 0;

	m_missionState = 0;
	m_deathName = "";
}

void MissionMod::UpdateMissionData()
{
	// fill the MissionArray
	int missionOffset = m_missionArrayStartAddr + m_missionID * sizeof(MissionArray) / 8;
	m_missionCount = *(int *)getGlobalPtr(m_missionArraySizeAddr);
	m_currentMission = *(MissionArray *)getGlobalPtr(missionOffset);

	int missionArray2Offset = m_missionArray2StartAddr + m_missionID * sizeof(MissionArray2) / 8;
	m_mission2Size = *(int *)getGlobalPtr(m_missionArray2SizeAddr);
	m_currentMission2 = *(MissionArray2 *)getGlobalPtr(missionArray2Offset);

	if (m_updateSafArray)
	{
		GetStrangersAndFreaksArray(m_safID, m_safArray);
		m_updateSafArray = false;
	}
	int safArray2Offset = m_safArray2StartAddr + m_safID * sizeof(StrangersAndFreaksArray2) / 8;
	m_saf2Size = *(int *)getGlobalPtr(m_safArray2SizeAddr);
	m_safArray2 = *(StrangersAndFreaksArray2 *)getGlobalPtr(safArray2Offset);

	int missionArray3Offset = m_missionArray3StartAddr + m_missionID3 * sizeof(MissionArray3) / 8;
	m_mission3Size = *(int *)getGlobalPtr(m_missionArray3SizeAddr);
	m_mission3 = *(MissionArray3 *)getGlobalPtr(missionArray3Offset);

	int missionArray4Offset = m_missionArray4StartAddr + m_missionID4 * sizeof(MissionArray4) / 8;
	m_mission4Size = *(int *)getGlobalPtr(m_missionArray4SizeAddr);
	m_mission4 = *(MissionArray4 *)getGlobalPtr(missionArray4Offset);

	int missionArray5Offset = m_missionArray5StartAddr + m_missionID5 * sizeof(MissionArray5) / 8;
	m_mission5Size = *(int *)getGlobalPtr(m_missionArray5SizeAddr);
	m_mission5 = *(MissionArray5 *)getGlobalPtr(missionArray5Offset);

	int missionArray5BisOffset = m_missionArray5BisStartAddr + m_missionID5 * sizeof(MissionArray5Bis) / 8;
	m_mission5BisSize = *(int *)getGlobalPtr(m_missionArray5BisSizeAddr);
	m_mission5Bis = *(MissionArray5Bis *)getGlobalPtr(missionArray5BisOffset);

	int missionArray5Bis2Offset = m_missionArray5Bis2StartAddr + m_missionID5 * sizeof(MissionArray5Bis2) / 8;
	m_mission5Bis2Size = *(int *)getGlobalPtr(m_missionArray5Bis2SizeAddr);
	m_mission5Bis2 = *(MissionArray5Bis2 *)getGlobalPtr(missionArray5Bis2Offset);

	int missionArray6Offset = m_missionArray6StartAddr + m_missionID6 * sizeof(MissionArray6) / 8;
	m_mission6Size = *(int *)getGlobalPtr(m_missionArray6SizeAddr);
	m_mission6 = *(MissionArray6 *)getGlobalPtr(missionArray6Offset);

	int missionArray7Offset = m_missionArray7StartAddr + m_missionID7 * sizeof(MissionArray7) / 8;
	m_mission7Size = *(int *)getGlobalPtr(m_missionArray7SizeAddr);
	m_mission7 = *(MissionArray7 *)getGlobalPtr(missionArray7Offset);

	int missionArray8Offset = m_missionArray8StartAddr + m_missionID8 * sizeof(MissionArray8) / 8;
	m_mission8Size = *(int *)getGlobalPtr(m_missionArray8SizeAddr);
	m_mission8 = *(MissionArray8 *)getGlobalPtr(missionArray8Offset);

	int missionArray9Offset = m_missionArray9StartAddr + m_missionID9 * sizeof(MissionArray9) / 8;
	m_mission9Size = *(int *)getGlobalPtr(m_missionArray9SizeAddr);
	m_mission9 = *(MissionArray9 *)getGlobalPtr(missionArray9Offset);

	int missionArray10Offset = m_missionArray10StartAddr + m_missionID10 * sizeof(MissionArray10) / 8;
	m_mission10Size = *(int *)getGlobalPtr(m_missionArray10SizeAddr);
	m_mission10 = *(MissionArray10 *)getGlobalPtr(missionArray10Offset);

	m_availableMissionCount = *(int *)getGlobalPtr(GlobalID::_87299);
	m_missionState = *(int *)getGlobalPtr(GlobalID::_89962);
	m_deathName = std::string((char *)getGlobalPtr(GlobalID::_68477));
	m_missionUnk0 = *(int *)getGlobalPtr(GlobalID::_68507);
	m_missionUnk68523 = *(int *)getGlobalPtr(GlobalID::_68523);
	m_missionUnk87289 = *(int *)getGlobalPtr(GlobalID::_87289);
	m_missionUnk87290 = *(int *)getGlobalPtr(GlobalID::_87290);
	m_missionUnk87298 = *(int *)getGlobalPtr(GlobalID::_87298);
	m_missionUnk81105 = *(int *)getGlobalPtr(GlobalID::_81105);
}

void MissionMod::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			ImGui::MenuItem("Empty");
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

bool MissionMod::Draw()
{
	ImGui::SetWindowFontScale(m_menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_contentFontSize);

	ImGui::Checkbox("Constant Updates?", &m_constantUpdate);
	if (!m_constantUpdate)
		if (ImGui::Button("Update"))
			m_wantsUpdate = true;

	ImGui::Separator();
	ImGui::Text("Mission state: %d", m_missionState);
	ImGui::Text("Death name: %s", m_deathName.c_str());
	ImGui::Text("Unknown0: %d", m_missionUnk0);
	ImGui::Text("Global_68523: %d", m_missionUnk68523);
	ImGui::Text("Global_87289: %d", m_missionUnk87289);
	ImGui::Text("Global_87290: %d", m_missionUnk87290);
	ImGui::Text("Global_87298: %d", m_missionUnk87298);
	ImGui::Text("Global_81105: %d", m_missionUnk81105);
	ImGui::Text("Mission count: %d", m_missionCount);

	ImGui::Separator();
	if (ImGui::TreeNode("Mission info")) {
		if (ImGui::InputInt("Mission ID", &m_missionID)) {
			ClipInt(m_missionID, 0, m_missionCount - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("< %d", m_missionCount);

		ImGui::Text("Name: %s", m_currentMission.name);
		ImGui::Text("Hash: %u", m_currentMission.hash);
		ImGui::Text("Field 2: %d", m_currentMission.field_7);
		ImGui::Text("Acronym: %s", m_currentMission.acronym);
		ImGui::Text("Cutscene trigger ID: %d", m_currentMission.triggerId);
		ImGui::SameLine();
		if (ImGui::Button("View"))
		{
			if (m_currentMission.triggerId >= 0 && m_currentMission.triggerId < m_mission3Size)
				m_missionID3 = m_currentMission.triggerId;
		}
		ImGui::Text("Character List: %d (%s)", m_currentMission.characterSetID,
			CharacterSetIDStr(m_currentMission.characterSetID).c_str());
		ImGui::Text("Field 4b: %d", m_currentMission.field_11b);
		ImGui::Text("Field 5: %d", m_currentMission.field_12);
		ImGui::Text("Timeframe start: %d", m_currentMission.timeframeStart);
		ImGui::Text("Timeframe end: %d", m_currentMission.timeframeEnd);
		ImGui::Text("Field 8: %s", m_currentMission.field_15.to_string().c_str());
		ImGui::Text("Field 9: %d", m_currentMission.field_16);

		ImGui::Text("Field 11 size: %d", m_currentMission.field_17_size);
		std::string field_11 = "Field 11: ";
		for (int i = 0; i < m_currentMission.field_17_size; ++i)
			field_11 += std::to_string(m_currentMission.field_17[i].val) + ", ";
		ImGui::Text(field_11.c_str());
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Mission Array 2"))
	{
		ImGui::Text("Same ID as mission ID: %d", m_missionID);
		ImGui::SameLine();
		ImGui::Text("< %d", m_mission2Size);
		ImGui::Text("Field 1: %d", m_currentMission2.field_1);
		ImGui::Text("Field 2: %.2f", m_currentMission2.field_2);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Cutscene trigger zones"))
	{
		if (ImGui::InputInt("Trigger ID", &m_missionID3)) {
			ClipInt(m_missionID3, 0, m_mission3Size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("< %d", m_mission3Size);

		ImGui::Text("Field 0 Size: %d", m_mission3.field_0_size);
		for (int i = 0; i < m_mission3.field_0_size; ++i)
			ImGui::Text("Field 0[%d]: (%.4f, %.4f, %.4f)", i, m_mission3.positions[i].x, m_mission3.positions[i].y, m_mission3.positions[i].z);
		ImGui::Text("Field A: %f", m_mission3.field_10);
		ImGui::Text("Field B: %s", m_mission3.field_11.to_string().c_str());
		ImGui::Text("Sprite id size: %d", m_mission3.sprite_id_size);
		for (int i = 0; i < m_mission3.sprite_id_size; ++i)
			ImGui::Text("Sprite %d: %d", i, m_mission3.sprite_id[i]);
		ImGui::Text("Field 10: %d", m_mission3.field_13);
		ImGui::Text("Field 11: %d", m_mission3.field_14);
		ImGui::Text("Field 12: %d", m_mission3.field_15);
		ImGui::Text("Blip ref: %d", m_mission3.field_16);
		ImGui::Text("Text file: %s", m_mission3.field_17);
		ImGui::Text("Field 16: %d", m_mission3.field_18);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Available missions"))
	{
		if (ImGui::InputInt("Available index", &m_missionID4)) {
			ClipInt(m_missionID4, 0, m_mission4Size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("< %d", m_mission4Size);

		ImGui::Text("Available count: %d", m_availableMissionCount);

		ImGui::Text("Ready: %d", m_mission4.isReady);
		ImGui::Text("Field 1: %d", m_mission4.field_1);
		ImGui::Text("Field 2: %d", m_mission4.field_2);
		ImGui::Text("Field 3: %d", m_mission4.field_3);
		ImGui::Text("Field 4: %d", m_mission4.field_4);
		ImGui::Text("Mission ID: %d", m_mission4.missionID);
		ImGui::SameLine();
		if (ImGui::Button("View##1"))
		{
			if (m_mission4.missionID >= 0 && m_mission4.missionID < m_missionCount)
				m_missionID = m_mission4.missionID;
		}
		ImGui::Text("Mission array 7 ID: %d", m_mission4.missionArray7ID);
		ImGui::SameLine();
		if (ImGui::Button("View##2"))
		{
			if (m_mission4.missionArray7ID >= 0 && m_mission4.missionArray7ID < m_mission7Size)
				m_missionID7 = m_mission4.missionArray7ID;
		}
		ImGui::Text("Field 7: %d", m_mission4.field_7);
		ImGui::Text("Character List: %d, (%s)", m_mission4.field_8, CharacterSetIDStr(m_mission4.field_8).c_str());
		ImGui::Text("Cutscene Trigger ID: %d", m_mission4.triggerID);
		ImGui::SameLine();
		if (ImGui::Button("View##3"))
		{
			if (m_mission4.triggerID >= 0 && m_mission4.triggerID < m_mission3Size)
				m_missionID3 = m_mission4.triggerID;
		}
		ImGui::Text("Mission ID: %d", m_mission4.field_10.missionID);
		ImGui::SameLine();
		if (ImGui::Button("View##4"))
		{
			if (m_mission4.field_10.missionID >= 0 && m_mission4.field_10.missionID < m_missionCount)
				m_missionID = m_mission4.field_10.missionID;
		}
		ImGui::Text("Field A_1: %s", m_mission4.field_10.field_1.to_string().c_str());
		ImGui::Text("Distance squared: %f", m_mission4.field_10.distanceSq);
		ImGui::Text("Distance squared 2: %f", m_mission4.field_10.distanceSq2);
		ImGui::Text("Distance squared 3: %f", m_mission4.field_10.distanceSq3);
		ImGui::Text("Distance squared 4: %f", m_mission4.field_10.distanceSq4);
		ImGui::Text("Field A_6: %s", m_mission4.field_10.field_6.to_string().c_str());
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Array 5"))
	{
		if (ImGui::InputInt("Array 5 ID", &m_missionID5)) {
			ClipInt(m_missionID5, 0, m_mission5Size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("< %d", m_mission5Size);

		ImGui::Text("Mission array ID: %d", m_mission5.missionArrayID);
		ImGui::SameLine();
		if (ImGui::Button("View"))
		{
			if (m_mission5.missionArrayID >= 0 && m_mission5.missionArrayID < m_missionCount)
				m_missionID = m_mission5.missionArrayID;
		}
		ImGui::Text("Field 1: %d", m_mission5.field_1);
		ImGui::Text("Field 2: %d", m_mission5.field_2);
		ImGui::Text("Money spent?: %d", m_mission5.moneySpent);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Array 5 Bis"))
	{
		ImGui::Text("Same ID as mission ID 5: %d", m_missionID5);
		ImGui::SameLine();
		ImGui::Text("< %d", m_mission5BisSize);
		ImGui::Text("Field 0: %d", m_mission5Bis.f_0);
		ImGui::Text("Field 1: %d", m_mission5Bis.f_1);
		ImGui::Text("Field 2: %d", m_mission5Bis.f_2);
		ImGui::Text("Field 3: %d", m_mission5Bis.f_3);
		ImGui::Text("Field 4: %d", m_mission5Bis.f_4);
		ImGui::Text("Field 5: %d", m_mission5Bis.f_5);
		ImGui::Text("Field 6: %d", m_mission5Bis.f_6);
		ImGui::Text("Field 7: %d", m_mission5Bis.f_7);
		ImGui::Text("Field 8: %d", m_mission5Bis.f_8);
		ImGui::Text("Field 9: %d", m_mission5Bis.f_9);
		ImGui::Text("Field 10: %d", m_mission5Bis.f_10);
		ImGui::Text("Field 11: %d", m_mission5Bis.f_11);
		ImGui::Text("Field 12: %d", m_mission5Bis.f_12);
		ImGui::Text("Field 13: %d", m_mission5Bis.f_13);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Array 5 Bis 2"))
	{
		ImGui::Text("Same ID as mission ID 5: %d", m_missionID5);
		ImGui::SameLine();
		ImGui::Text("< %d", m_mission5Bis2Size);
		ImGui::Text("Script name: %s", m_mission5Bis2.scriptName);
		ImGui::Text("Stack size: %d", m_mission5Bis2.stackSize);
		ImGui::Text("Field 9: %d", m_mission5Bis2.f_9);
		ImGui::Text("Field 10: %d", m_mission5Bis2.f_10);
		ImGui::Text("Field 11: %d", m_mission5Bis2.f_11);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Array 6"))
	{
		if (ImGui::InputInt("Array 6 ID", &m_missionID6)) {
			ClipInt(m_missionID6, 0, m_mission6Size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("< %d", m_mission6Size);
		ImGui::Text("Hash: %d", m_mission6.hash);
		ImGui::Text("Mission array 10 ID: %d", m_mission6.missionArray10ID);
		ImGui::SameLine();
		if (ImGui::Button("View##1"))
		{
			if (m_mission6.missionArray10ID >= 0 && m_mission6.missionArray10ID < m_mission10Size)
				m_missionID10 = m_mission6.missionArray10ID;
		}
		ImGui::Text("Mission array 5 ID: %d", m_mission6.missionArray5ID);
		ImGui::SameLine();
		if (ImGui::Button("View##2"))
		{
			if (m_mission6.missionArray5ID >= 0 && m_mission6.missionArray5ID < m_mission5Size)
				m_missionID5 = m_mission6.missionArray5ID;
		}
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Array 7"))
	{
		if (ImGui::InputInt("Array 7 ID", &m_missionID7)) {
			ClipInt(m_missionID7, 0, m_mission7Size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("< %d", m_mission7Size);
		ImGui::Text("Field 0: %s", m_mission7.field_0.to_string().c_str());
		ImGui::Text("Mission array 6 ID: %d", m_mission7.missionArray6ID);
		ImGui::SameLine();
		if (ImGui::Button("View"))
		{
			if (m_mission7.missionArray6ID >= 0 && m_mission7.missionArray6ID < m_mission6Size)
				m_missionID6 = m_mission7.missionArray6ID;
		}
		ImGui::Text("Hash: %d", m_mission7.hash);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Array 8"))
	{
		if (ImGui::InputInt("Array 8 ID", &m_missionID8)) {
			ClipInt(m_missionID8, 0, m_mission8Size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("< %d", m_mission8Size);
		ImGui::Text("Mission array 6 ID min?: %d", m_mission8.missionArray6IDMin);
		ImGui::Text("Mission array 6 ID max?: %d", m_mission8.missionArray6IDMax);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Currently runing mission script"))
	{
		if (ImGui::InputInt("Array 9 ID", &m_missionID9)) {
			ClipInt(m_missionID9, 0, m_mission9Size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("< %d", m_mission9Size);
		ImGui::Text("Mission array 5 ID: %d", m_mission9.missionArray5ID);
		ImGui::SameLine();
		if (ImGui::Button("View"))
		{
			if (m_mission9.missionArray5ID >= 0 && m_mission9.missionArray5ID < m_mission5Size)
				m_missionID5 = m_mission9.missionArray5ID;
		}
		ImGui::Text("Field 1: %s", m_mission9.f_1.to_string().c_str());
		ImGui::Text("Field 2: %d", m_mission9.f_2);
		ImGui::Text("Field 3: %d", m_mission9.f_3);
		ImGui::Text("Thread ID: %d", m_mission9.threadId);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Array 10"))
	{
		if (ImGui::InputInt("Array 10 ID", &m_missionID10)) {
			ClipInt(m_missionID10, 0, m_mission10Size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("< %d", m_mission10Size);
		ImGui::Text("Mission array 5 ID: %d", m_mission10.missionArray5ID);
		ImGui::SameLine();
		if (ImGui::Button("View"))
		{
			if (m_mission10.missionArray5ID >= 0 && m_mission10.missionArray5ID < m_mission5Size)
				m_missionID5 = m_mission10.missionArray5ID;
		}
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Strangers And Freaks Array"))
	{
		if (ImGui::InputInt("Strangers And Freaks ID", &m_safID)) {
			ClipInt(m_safID, 0, m_safCount - 1);
			m_wantsUpdate = true;
			m_updateSafArray = true;
		}
		ImGui::SameLine();
		ImGui::Text("< %d", m_safCount);
		ImGui::TextColored(ImVec4(255, 0, 0, 255), "This data is not updated by the game, it's taken from the game files!");
		ImGui::Text("Field 0: %s", m_safArray.f_0.str);
		ImGui::Text("Field 1: %s", m_safArray.f_1.str);
		ImGui::Text("Field 3: %d", m_safArray.f_3);
		ImGui::Text("Field 4: %d", m_safArray.f_4);
		ImGui::Text("Field 5: %d", m_safArray.f_5);
		ImGui::Text("Field 6: (%.4f, %.4f, %.4f)", m_safArray.f_6[0], m_safArray.f_6[1], m_safArray.f_6[2]);
		ImGui::Text("Field 9: %d", m_safArray.f_9);
		ImGui::Text("Field 10: %s", m_safArray.f_10.str);
		ImGui::Text("Field 14: %d", m_safArray.f_14);
		ImGui::Text("Field 15: %d", m_safArray.f_15);
		ImGui::Text("Field 16: %s", m_safArray.f_16.str);
		ImGui::Text("Field 22: %d", m_safArray.f_22);
		ImGui::Text("Field 23: %d", m_safArray.f_23);
		ImGui::Text("Field 24: %d", m_safArray.f_24);
		ImGui::Text("Field 25: %d", m_safArray.f_25);
		ImGui::Text("Field 26: %d", m_safArray.f_26);
		ImGui::Text("Field 27: %d", m_safArray.f_27);
		ImGui::Text("Field 28: %d", m_safArray.f_28);
		ImGui::Text("Field 29: %d", m_safArray.f_29);
		ImGui::Text("Field 30: %d", m_safArray.f_30);
		ImGui::Text("Field 31: %d", m_safArray.f_31);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Strangers And Freaks Array 2"))
	{
		ImGui::Text("Same ID as strangers and freaks ID: %d", m_safID);
		ImGui::SameLine();
		ImGui::Text("< %d", m_saf2Size);
		ImGui::Text("Field 0: %s", m_safArray2.f_0.to_string().c_str());
		ImGui::Text("Field 1: %d", m_safArray2.f_1);
		ImGui::Text("Field 2: %d", m_safArray2.f_2);
		ImGui::Text("Field 3: %d", m_safArray2.f_3);
		ImGui::Text("Field 4: %d", m_safArray2.f_4);
		ImGui::Text("Field 5: %f", m_safArray2.f_5);
		ImGui::TreePop();
	}

	return true;
}

const char * CharacterIDStr(CharacterID id)
{
	switch (id)
	{
	case MICHAEL:
		return "Michael";
	case FRANKLIN:
		return "Franklin";
	case TREVOR:
		return "Trevor";
	case LAMAR:
		return "Lamar";
	case JIMMY:
		return "Jimmy";
	case AMANDA:
		return "Amanda";
	case FRIEND:
		return "Friend";
	default:
		return "NULL";
	}
}

std::string CharacterSetIDStr(int characterSetID)
{
	if (characterSetID < 0 || characterSetID > 7)
		return std::string("NULL");
	std::bitset<32> set = characterSetID;
	std::string names;
	if (set.test(0))
		names = "Michael, ";
	if (set.test(1))
		names += "Franklin, ";
	if (set.test(2))
		names += "Trevor";
	return names;
}
