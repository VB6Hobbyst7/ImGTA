#include "mission_mod.h"
#include "natives.h"
#include "script.h"
#include "imgui.h"
#include "main.h"
#include "utils.h"
#include "watch_entry.h"
#include "imgui_extras.h"


void MissionMod::Load()
{

}

void MissionMod::Unload()
{

}

void MissionMod::Think()
{
	if ((m_bConstantUpdate || m_bWantsUpdate))
	{
		UpdateMissionData(m_bWantsUpdate);
		m_bWantsUpdate = false;
	}
}

void MissionMod::ResetData()
{
	m_missionCount = 0;
	m_currentMission.name[0] = '\0';
	m_currentMission.hash = 0;
	m_currentMission.acronym[0] = '\0';
	m_currentMission.trigger_id = 0;
	m_currentMission.field_4 = 0;
	m_currentMission.field_5 = 0;
	m_currentMission.field_6 = 0;
	m_currentMission.field_7 = 0;
	m_currentMission.field_8 = 0;

	m_currentMission2.field_1 = 0;
	m_currentMission2.field_2 = 0;

	m_missionState = 0;
	m_deathName = "";
}

void MissionMod::UpdateMissionData(bool once) {
	
	int missionOffset = m_missionArrayStartAddr + m_missionID * sizeof(MissionArray) / 8;

	// fill the MissionArray
	m_missionCount = *(int *) getGlobalPtr(m_missionArraySizeAddr);
	m_currentMission = *(MissionArray *) getGlobalPtr(missionOffset);

	int missionArray2Offset = m_missionArray2StartAddr + m_missionID * sizeof(MissionArray2) / 8;
	m_currentMission2 = *(MissionArray2 *) getGlobalPtr(missionArray2Offset);

	int missionArray3Offset = m_missionArray3StartAddr + m_missionID3 * sizeof(MissionArray3) / 8;
	m_mission3Size = *(int *)getGlobalPtr(m_missionArray3SizeAddr);
	m_mission3 = *(MissionArray3 *) getGlobalPtr(missionArray3Offset);

	int missionArray4Offset = m_missionArray4StartAddr + m_missionID4 * sizeof(MissionArray4) / 8;
	m_mission4Size = *(int *)getGlobalPtr(m_missionArray4SizeAddr);
	m_mission4 = *(MissionArray4 *)getGlobalPtr(missionArray4Offset);

	int missionArray5Offset = m_missionArray5StartAddr + m_missionID5 * sizeof(MissionArray5) / 8;
	m_mission5Size = *(int *)getGlobalPtr(m_missionArray5SizeAddr);
	m_mission5 = *(MissionArray5 *)getGlobalPtr(missionArray5Offset);

	int missionArray6Offset = m_missionArray6StartAddr + m_missionID6 * sizeof(MissionArray6) / 8;
	m_mission6Size = *(int *)getGlobalPtr(m_missionArray6SizeAddr);
	m_mission6 = *(MissionArray6 *)getGlobalPtr(missionArray6Offset);

	int missionArray7Offset = m_missionArray7StartAddr + m_missionID7 * sizeof(MissionArray7) / 8;
	m_mission7Size = *(int *)getGlobalPtr(m_missionArray7SizeAddr);
	m_mission7 = *(MissionArray7 *)getGlobalPtr(missionArray7Offset);

	m_missionState = *(int *) getGlobalPtr(0x15F6A);
	m_deathName = std::string((char *) getGlobalPtr(0x10B7D));
	m_missionUnk0 = *(int *)getGlobalPtr(0x10B9B);
	m_missionUnk1 = *(int *)getGlobalPtr(0x10BAB); // 0x10BAB->Global_10BA2.f_9;
}

void MissionMod::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
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

	ImGui::Checkbox("Constant Updates?", &m_bConstantUpdate);
	if (!m_bConstantUpdate)
		if (ImGui::Button("Update"))
			m_bWantsUpdate = true;

	ImGui::Separator();
	ImGui::Text("Mission state: %d", m_missionState);
	ImGui::Text("Death name: %s", m_deathName.c_str());
	ImGui::Text("Unknown0: %d", m_missionUnk0);
	ImGui::Text("Mission count: %d", m_missionCount);

	ImGui::Separator();
	if (ImGui::TreeNode("Mission info")) {
		if (ImGui::InputInt("MissionArrayID", &m_missionID)) {
			ClipInt(m_missionID, 0, m_missionCount - 1);
			m_bWantsUpdate = true;
		}

		ImGui::Text("Name: %s", m_currentMission.name);
		ImGui::Text("Hash: %u", m_currentMission.hash);
		ImGui::Text("Field 2: %d", m_currentMission.field_2);
		ImGui::Text("Acronym: %s", m_currentMission.acronym);
		ImGui::Text("Trigger ID: %d", m_currentMission.trigger_id);
		ImGui::Text("Field 4: %d", m_currentMission.field_4);
		ImGui::Text("Field 4b: %d", m_currentMission.field_4b);
		ImGui::Text("Field 5: %d", m_currentMission.field_5);
		ImGui::Text("Field 6: %d", m_currentMission.field_6);
		ImGui::Text("Field 7: %d", m_currentMission.field_7);
		ImGui::Text("Field 8: %d", m_currentMission.field_8);
		ImGui::Text("Field 8b: %d", m_currentMission.field_8b);
		ImGui::Text("Field 9: %d", m_currentMission.field_9);

		ImGui::Text("Field 11 size: %d", m_currentMission.field_11_size);
		std::string field_11 = "Field 11: ";
		for (int i = 0; i < m_currentMission.field_11_size; ++i)
			field_11 += std::to_string(m_currentMission.field_11[i].val) + ", ";
		ImGui::Text(field_11.c_str());
		ImGui::TreePop();
	}
	
	ImGui::Separator();
	if (ImGui::TreeNode("Mission Array 2"))
	{
		ImGui::Text("Field 1: %d", m_currentMission2.field_1);
		ImGui::Text("Field 2: %.2f", m_currentMission2.field_2);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Cutscene trigger zones"))
	{
		if (ImGui::InputInt("Trigger ID", &m_missionID3)) {
			ClipInt(m_missionID3, 0, m_mission3Size - 1);
			m_bWantsUpdate = true;
		}

		ImGui::Text("Field 0 Size: %d", m_mission3.field_0_size);
		for (int i = 0; i < m_mission3.field_0_size; ++i)
			ImGui::Text("Field 0[%d]: (%.4f, %.4f, %.4f)", i, m_mission3.positions[i].x, m_mission3.positions[i].y, m_mission3.positions[i].z);
		ImGui::Text("Field A: %f", m_mission3.field_A);
		ImGui::Text("Field B: %s", m_mission3.field_B.to_string().c_str());
		ImGui::Text("Sprite id size: %d", m_mission3.sprite_id_size);
		for (int i = 0; i < m_mission3.sprite_id_size; ++i)
			ImGui::Text("Sprite %d: %d", i, m_mission3.sprite_id[i]);
		ImGui::Text("Field 10: %d", m_mission3.field_10);
		ImGui::Text("Field 11: %d", m_mission3.field_11);
		ImGui::Text("Field 12: %d", m_mission3.field_12);
		ImGui::Text("Blip ref: %d", m_mission3.field_13);
		ImGui::Text("Text file: %s", m_mission3.field_14);
		ImGui::Text("Field 16: %d", m_mission3.field_16);
		ImGui::TreePop();
	}
	
	ImGui::Separator();
	if (ImGui::TreeNode("Available missions"))
	{
		if (ImGui::InputInt("Available index", &m_missionID4)) {
			ClipInt(m_missionID4, 0, m_mission4Size - 1);
			m_bWantsUpdate = true;
		}

		ImGui::Text("Field 0: %d", m_mission4.field_0);
		ImGui::Text("Field 1: %d", m_mission4.field_1);
		ImGui::Text("Field 2: %d", m_mission4.field_2);
		ImGui::Text("Field 3: %d", m_mission4.field_3);
		ImGui::Text("Field 4: %d", m_mission4.field_4);
		ImGui::Text("Field 5: %d", m_mission4.field_5);
		ImGui::Text("Field 6: %d", m_mission4.field_6);
		ImGui::Text("Field 7: %d", m_mission4.field_7);
		ImGui::Text("Field 8: %d", m_mission4.field_8);
		ImGui::Text("Mission ID: %d", m_mission4.mission_id);

		ImGui::Text("Field A_0: %d", m_mission4.field_A.field_0);
		ImGui::Text("Field A_1: %s", m_mission4.field_A.field_1.to_string().c_str());
		ImGui::Text("Field A_2: %f", m_mission4.field_A.field_2);
		ImGui::Text("Field A_3: %f", m_mission4.field_A.field_3);
		ImGui::Text("Field A_4: %f", m_mission4.field_A.field_4);
		ImGui::Text("Field A_5: %f", m_mission4.field_A.field_5);
		ImGui::Text("Field A_6: %s", m_mission4.field_A.field_6.to_string().c_str());
		ImGui::TreePop();
	}
	
	ImGui::Separator();
	if (ImGui::TreeNode("Array 5"))
	{
		if (ImGui::InputInt("Array 5 ID", &m_missionID5)) {
			ClipInt(m_missionID5, 0, m_mission5Size - 1);
			m_bWantsUpdate = true;
		}

		ImGui::Text("Field 0: %d", m_mission5.missionArrayID);
		ImGui::Text("Field 1: %d", m_mission5.field_1);
		ImGui::Text("Field 2: %d", m_mission5.field_2);
		ImGui::Text("Field 3: %d", m_mission5.field_3);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Array 6"))
	{
		if (ImGui::InputInt("Array 6 ID", &m_missionID6)) {
			ClipInt(m_missionID6, 0, m_mission6Size - 1);
			m_bWantsUpdate = true;
		}
		ImGui::Text("Hash: %d", m_mission6.hash);
		ImGui::Text("Field 1: %d", m_mission6.field_1);
		ImGui::Text("Field 2: %d", m_mission6.field_2);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Array 7"))
	{
		if (ImGui::InputInt("Array 7 ID", &m_missionID7)) {
			ClipInt(m_missionID7, 0, m_mission7Size - 1);
			m_bWantsUpdate = true;
		}
		ImGui::Text("Field 0: %s", m_mission7.field_0.to_string().c_str());
		ImGui::Text("Field 1: %d", m_mission7.field_1);
		ImGui::Text("Field 2: %d", m_mission7.field_2);
		ImGui::TreePop();
	}

	return true;
}