/*
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "mission_mod.h"
#include "natives.h"
#include "script.h"
#include "utils.h"
#include "imgui.h"
#include "imgui_extras.h"
#include "watch_entry.h"
#include "global_id.h"


MissionMod::MissionMod(DLLObject & dllObject, bool supportGlobals) :
	Mod(dllObject, "Mission", true, supportGlobals),
	m_gMission1(GlobalID::_81155),
	m_gMission2(GlobalID::_84352),
	m_gMission3(GlobalID::_24748),
	m_gMission4(GlobalID::_87300),
	m_gMission5(GlobalID::_68623),
	m_gMission5Bis(GlobalID::_75198),
	m_gMission5Bis2(GlobalID::_72674),
	m_gMission5Bis3(GlobalID::_72104),
	m_gMission6(GlobalID::_75339),
	m_gMission7(GlobalID::_104696),
	m_gMission8(GlobalID::_81040),
	m_gMission9(GlobalID::_81119),
	m_gMission10(GlobalID::_81106),
	m_gMission12(GlobalID::_84546),
	m_gSaf1(0),
	m_gSaf2(GlobalID::_114181)
{
	m_windowFlags = ImGuiWindowFlags_MenuBar;
	m_gSaf1.size = 63;
}

void MissionMod::Load()
{
	Mod::CommonLoad();
	m_settings = m_dllObject.GetUserSettings().mission;
}

void MissionMod::Unload()
{
	Mod::CommonUnload();
	m_dllObject.GetUserSettings().mission = m_settings;
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
	m_missionState = 0;
	m_deathName = "";
}

void MissionMod::UpdateMissionData()
{
	// Load arrays
	m_gMission1.LoadElement();
	m_gMission2.LoadElement();
	m_gMission3.LoadElement();
	m_gMission4.LoadElement();
	m_gMission5.LoadElement();
	m_gMission5Bis.LoadElement();
	m_gMission5Bis2.LoadElement();
	m_gMission5Bis3.LoadElement();
	m_gMission6.LoadElement();
	m_gMission7.LoadElement();
	m_gMission8.LoadElement();
	m_gMission9.LoadElement();
	m_gMission10.LoadElement();
	m_gMission12.LoadElement();
	
	// Strangers and Freaks
	if (m_updateSafArray)
	{
		GetStrangersAndFreaksArray(m_gSaf1.id, m_gSaf1.arr);
		m_updateSafArray = false;
	}
	m_gSaf2.LoadElement();


	m_availableMissionCount = *(int *)GetGlobalPtr(GlobalID::_87299);
	m_missionState = *(int *)GetGlobalPtr(GlobalID::_89962);
	m_deathName = std::string((char *)GetGlobalPtr(GlobalID::_68477));
	m_missionUnk0 = *(int *)GetGlobalPtr(GlobalID::_68507);
	m_missionUnk68523 = *(int *)GetGlobalPtr(GlobalID::_68523);
	m_missionUnk87289 = *(int *)GetGlobalPtr(GlobalID::_87289);
	m_missionUnk87290 = *(int *)GetGlobalPtr(GlobalID::_87290);
	m_missionUnk87298 = *(int *)GetGlobalPtr(GlobalID::_87298);
	m_missionUnk81105 = *(int *)GetGlobalPtr(GlobalID::_81105);
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
	ImGui::SetWindowFontScale(m_commonSettings.menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_commonSettings.contentFontSize);

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
	ImGui::Text("Mission count: %d", m_gMission1.size);

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Mission info", ImGuiTreeNodeFlags_SpanAvailWidth)) {
		ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
		if (ImGui::InputInt("Mission ID", &m_gMission1.id)) {
			ClipInt(m_gMission1.id, 0, m_gMission1.size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission1.size);

		ImGui::Text("Name: %s", m_gMission1.arr.name);
		ImGui::Text("Hash: %u", m_gMission1.arr.hash);
		ImGui::Text("Field 2: %d", m_gMission1.arr.field_7);
		ImGui::Text("Acronym: %s", m_gMission1.arr.acronym);
		ImGui::Text("Cutscene trigger ID: %d", m_gMission1.arr.triggerId);
		ImGui::SameLine();
		if (ImGui::Button("View"))
		{
			if (m_gMission1.arr.triggerId >= 0 && m_gMission1.arr.triggerId < m_gMission3.size)
				m_gMission3.id = m_gMission1.arr.triggerId;
		}
		ImGui::Text("Character List: %d (%s)", m_gMission1.arr.characterSetID,
			CharacterSetIDStr(m_gMission1.arr.characterSetID).c_str());
		ImGui::Text("Field 4b: %d", m_gMission1.arr.field_11b);
		ImGui::Text("Field 5: %d", m_gMission1.arr.field_12);
		ImGui::Text("Timeframe start: %d", m_gMission1.arr.timeframeStart);
		ImGui::Text("Timeframe end: %d", m_gMission1.arr.timeframeEnd);
		ImGui::Text("Field 8: %s", m_gMission1.arr.field_15.to_string().c_str());
		ImGui::Text("Field 9: %d", m_gMission1.arr.field_16);

		ImGui::Text("Field 11 size: %d", m_gMission1.arr.field_17_size);
		std::string field_11 = "Field 11: ";
		for (int i = 0; i < m_gMission1.arr.field_17_size; ++i)
			field_11 += std::to_string(m_gMission1.arr.field_17[i].val) + ", ";
		ImGui::Text(field_11.c_str());
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Mission Array 2", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		if (m_gMission1.id < m_gMission2.size)
			m_gMission2.id = m_gMission1.id;
		ImGui::Text("Same ID as mission ID: %d", m_gMission2.id);
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission2.size);
		ImGui::Text("Field 1: %d", m_gMission2.arr.field_1);
		ImGui::Text("Field 2: %.2f", m_gMission2.arr.field_2);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Cutscene trigger zones", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
		if (ImGui::InputInt("Trigger ID", &m_gMission3.id)) {
			ClipInt(m_gMission3.id, 0, m_gMission3.size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission3.size);

		ImGui::Text("Field 0 Size: %d", m_gMission3.arr.field_0_size);
		for (int i = 0; i < m_gMission3.arr.field_0_size; ++i)
			ImGui::Text("Field 0[%d]: (%.4f, %.4f, %.4f)", i, m_gMission3.arr.positions[i].x, m_gMission3.arr.positions[i].y, m_gMission3.arr.positions[i].z);
		ImGui::Text("Field A: %f", m_gMission3.arr.field_10);
		ImGui::Text("Field B: %s", m_gMission3.arr.field_11.to_string().c_str());
		ImGui::Text("Sprite id size: %d", m_gMission3.arr.sprite_id_size);
		for (int i = 0; i < m_gMission3.arr.sprite_id_size; ++i)
			ImGui::Text("Sprite %d: %d", i, m_gMission3.arr.sprite_id[i]);
		ImGui::Text("Field 10: %d", m_gMission3.arr.field_13);
		ImGui::Text("Field 11: %d", m_gMission3.arr.field_14);
		ImGui::Text("Field 12: %d", m_gMission3.arr.field_15);
		ImGui::Text("Blip ref: %d", m_gMission3.arr.field_16);
		ImGui::Text("Text file: %s", m_gMission3.arr.field_17);
		ImGui::Text("Field 16: %d", m_gMission3.arr.field_18);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Available missions", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
		if (ImGui::InputInt("Available index", &m_gMission4.id)) {
			ClipInt(m_gMission4.id, 0, m_gMission4.size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission4.size);

		ImGui::Text("Available count: %d", m_availableMissionCount);

		ImGui::Text("Ready: %d", m_gMission4.arr.isReady);
		ImGui::Text("Field 1: %d", m_gMission4.arr.field_1);
		ImGui::Text("Field 2: %d", m_gMission4.arr.field_2);
		ImGui::Text("Field 3: %d", m_gMission4.arr.field_3);
		ImGui::Text("Field 4: %d", m_gMission4.arr.field_4);
		ImGui::Text("Mission ID: %d", m_gMission4.arr.missionID);
		ImGui::SameLine();
		if (ImGui::Button("View##1"))
		{
			if (m_gMission4.arr.missionID >= 0 && m_gMission4.arr.missionID < m_gMission1.size)
				m_gMission1.id = m_gMission4.arr.missionID;
		}
		ImGui::Text("Mission array 7 ID: %d", m_gMission4.arr.missionArray7ID);
		ImGui::SameLine();
		if (ImGui::Button("View##2"))
		{
			if (m_gMission4.arr.missionArray7ID >= 0 && m_gMission4.arr.missionArray7ID < m_gMission7.size)
				m_gMission7.id = m_gMission4.arr.missionArray7ID;
		}
		ImGui::Text("Field 7: %d", m_gMission4.arr.field_7);
		ImGui::Text("Character List: %d, (%s)", m_gMission4.arr.field_8, CharacterSetIDStr(m_gMission4.arr.field_8).c_str());
		ImGui::Text("Cutscene Trigger ID: %d", m_gMission4.arr.triggerID);
		ImGui::SameLine();
		if (ImGui::Button("View##3"))
		{
			if (m_gMission4.arr.triggerID >= 0 && m_gMission4.arr.triggerID < m_gMission3.size)
				m_gMission3.id = m_gMission4.arr.triggerID;
		}
		ImGui::Text("Mission ID: %d", m_gMission4.arr.field_10.missionID);
		ImGui::SameLine();
		if (ImGui::Button("View##4"))
		{
			if (m_gMission4.arr.field_10.missionID >= 0 && m_gMission4.arr.field_10.missionID < m_gMission1.size)
				m_gMission1.id = m_gMission4.arr.field_10.missionID;
		}
		ImGui::Text("Field A_1: %s", m_gMission4.arr.field_10.field_1.to_string().c_str());
		ImGui::Text("Distance squared: %f", m_gMission4.arr.field_10.distanceSq);
		ImGui::Text("Distance squared 2: %f", m_gMission4.arr.field_10.distanceSq2);
		ImGui::Text("Distance squared 3: %f", m_gMission4.arr.field_10.distanceSq3);
		ImGui::Text("Distance squared 4: %f", m_gMission4.arr.field_10.distanceSq4);
		ImGui::Text("Field A_6: %s", m_gMission4.arr.field_10.field_6.to_string().c_str());
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Array 5", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
		if (ImGui::InputInt("Array 5 ID", &m_gMission5.id)) {
			ClipInt(m_gMission5.id, 0, m_gMission5.size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission5.size);

		ImGui::Text("Mission array ID: %d", m_gMission5.arr.missionArrayID);
		ImGui::SameLine();
		if (ImGui::Button("View"))
		{
			if (m_gMission5.arr.missionArrayID >= 0 && m_gMission5.arr.missionArrayID < m_gMission1.size)
				m_gMission1.id = m_gMission5.arr.missionArrayID;
		}
		ImGui::Text("Field 1: %d", m_gMission5.arr.field_1);
		ImGui::Text("Field 2: %d", m_gMission5.arr.field_2);
		ImGui::Text("Money spent?: %d", m_gMission5.arr.moneySpent);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Array 5 Bis", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		if (m_gMission5.id < m_gMission5Bis.size)
			m_gMission5Bis.id = m_gMission5.id;
		ImGui::Text("Same ID as mission ID 5: %d", m_gMission5Bis.id);
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission5Bis.size);
		ImGui::Text("Field 0: %d", m_gMission5Bis.arr.f_0);
		ImGui::Text("Field 1: %d", m_gMission5Bis.arr.f_1);
		ImGui::Text("Field 2: %d", m_gMission5Bis.arr.f_2);
		ImGui::Text("Field 3: %d", m_gMission5Bis.arr.f_3);
		ImGui::Text("Field 4: %d", m_gMission5Bis.arr.f_4);
		ImGui::Text("Field 5: %d", m_gMission5Bis.arr.f_5);
		ImGui::Text("Field 6: %d", m_gMission5Bis.arr.f_6);
		ImGui::Text("Field 7: %d", m_gMission5Bis.arr.f_7);
		ImGui::Text("Field 8: %d", m_gMission5Bis.arr.f_8);
		ImGui::Text("Field 9: %d", m_gMission5Bis.arr.f_9);
		ImGui::Text("Field 10: %d", m_gMission5Bis.arr.f_10);
		ImGui::Text("Field 11: %d", m_gMission5Bis.arr.f_11);
		ImGui::Text("Field 12: %d", m_gMission5Bis.arr.f_12);
		ImGui::Text("Field 13: %d", m_gMission5Bis.arr.f_13);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Array 5 Bis 2", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		if (m_gMission5.id < m_gMission5Bis2.size)
			m_gMission5Bis2.id = m_gMission5.id;
		ImGui::Text("Same ID as mission ID 5: %d", m_gMission5Bis2.id);
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission5Bis2.size);
		ImGui::Text("Script name: %s", m_gMission5Bis2.arr.scriptName);
		ImGui::Text("Stack size: %d", m_gMission5Bis2.arr.stackSize);
		ImGui::Text("Field 9: %d", m_gMission5Bis2.arr.f_9);
		ImGui::Text("Field 10: %d", m_gMission5Bis2.arr.f_10);
		ImGui::Text("Field 11: %d", m_gMission5Bis2.arr.f_11);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Array 5 Bis 3", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		if (m_gMission5.id < m_gMission5Bis3.size)
			m_gMission5Bis3.id = m_gMission5.id;
		ImGui::Text("Same ID as mission ID 5: %d", m_gMission5Bis3.id);
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission5Bis3.size);
		ImGui::Text("Field 0: %d", m_gMission5Bis3.arr.field_0);
		ImGui::Text("Field 1: %d", m_gMission5Bis3.arr.field_1);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Array 6", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
		if (ImGui::InputInt("Array 6 ID", &m_gMission6.id)) {
			ClipInt(m_gMission6.id, 0, m_gMission6.size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission6.size);
		ImGui::Text("Hash: %d", m_gMission6.arr.hash);
		ImGui::Text("Mission array 10 ID: %d", m_gMission6.arr.missionArray10ID);
		ImGui::SameLine();
		if (ImGui::Button("View##1"))
		{
			if (m_gMission6.arr.missionArray10ID >= 0 && m_gMission6.arr.missionArray10ID < m_gMission10.size)
				m_gMission10.id = m_gMission6.arr.missionArray10ID;
		}
		ImGui::Text("Mission array 5 ID: %d", m_gMission6.arr.missionArray5ID);
		ImGui::SameLine();
		if (ImGui::Button("View##2"))
		{
			if (m_gMission6.arr.missionArray5ID >= 0 && m_gMission6.arr.missionArray5ID < m_gMission5.size)
				m_gMission5.id = m_gMission6.arr.missionArray5ID;
		}
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Array 7", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
		if (ImGui::InputInt("Array 7 ID", &m_gMission7.id)) {
			ClipInt(m_gMission7.id, 0, m_gMission7.size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission7.size);
		ImGui::Text("Field 0: %s", m_gMission7.arr.field_0.to_string().c_str());
		ImGui::Text("Mission array 6 ID: %d", m_gMission7.arr.missionArray6ID);
		ImGui::SameLine();
		if (ImGui::Button("View"))
		{
			if (m_gMission7.arr.missionArray6ID >= 0 && m_gMission7.arr.missionArray6ID < m_gMission6.size)
				m_gMission6.id = m_gMission7.arr.missionArray6ID;
		}
		ImGui::Text("Hash: %d", m_gMission7.arr.hash);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Array 8", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
		if (ImGui::InputInt("Array 8 ID", &m_gMission8.id)) {
			ClipInt(m_gMission8.id, 0, m_gMission8.size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission8.size);
		ImGui::Text("Mission array 6 ID min?: %d", m_gMission8.arr.missionArray6IDMin);
		ImGui::Text("Mission array 6 ID max?: %d", m_gMission8.arr.missionArray6IDMax);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Enabled mission script", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
		if (ImGui::InputInt("Array 9 ID", &m_gMission9.id)) {
			ClipInt(m_gMission9.id, 0, m_gMission9.size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission9.size);
		ImGui::Text("Mission array 5 ID: %d", m_gMission9.arr.missionArray5ID);
		ImGui::SameLine();
		if (ImGui::Button("View"))
		{
			if (m_gMission9.arr.missionArray5ID >= 0 && m_gMission9.arr.missionArray5ID < m_gMission5.size)
				m_gMission5.id = m_gMission9.arr.missionArray5ID;
		}
		ImGui::Text("Field 1: %s", m_gMission9.arr.f_1.to_string().c_str());
		ImGui::Text("Field 2: %d", m_gMission9.arr.f_2);
		ImGui::Text("Field 3: %d", m_gMission9.arr.f_3);
		ImGui::Text("Thread ID: %d", m_gMission9.arr.threadId);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Array 10", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
		if (ImGui::InputInt("Array 10 ID", &m_gMission10.id)) {
			ClipInt(m_gMission10.id, 0, m_gMission10.size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission10.size);
		ImGui::Text("Mission array 5 ID: %d", m_gMission10.arr.missionArray5ID);
		ImGui::SameLine();
		if (ImGui::Button("View"))
		{
			if (m_gMission10.arr.missionArray5ID >= 0 && m_gMission10.arr.missionArray5ID < m_gMission5.size)
				m_gMission5.id = m_gMission10.arr.missionArray5ID;
		}
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Array 12", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
		if (ImGui::InputInt("Array 12 ID", &m_gMission12.id)) {
			ClipInt(m_gMission12.id, 0, m_gMission12.size - 1);
			m_wantsUpdate = true;
		}
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gMission12.size);

		ImGui::Text("Script name: %s", m_gMission12.arr.scriptName);
		ImGui::Text("Stack size: %d", m_gMission12.arr.stackSize);
		ImGui::Text("ScriptHash: %d", m_gMission12.arr.scriptHash);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Strangers And Freaks Array", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
		if (ImGui::InputInt("Strangers And Freaks ID", &m_gSaf1.id)) {
			ClipInt(m_gSaf1.id, 0, m_gSaf1.size - 1);
			m_wantsUpdate = true;
			m_updateSafArray = true;
		}
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gSaf1.size);
		ImGui::TextColored(ImVec4(255, 0, 0, 255), "This data is not updated by the game, it's taken from the game files!");
		ImGui::Text("Field 0: %s", m_gSaf1.arr.f_0.str);
		ImGui::Text("Field 1: %s", m_gSaf1.arr.f_1.str);
		ImGui::Text("Field 3: %d", m_gSaf1.arr.f_3);
		ImGui::Text("Field 4: %d", m_gSaf1.arr.f_4);
		ImGui::Text("Field 5: %d", m_gSaf1.arr.f_5);
		ImGui::Text("Field 6: (%.4f, %.4f, %.4f)", m_gSaf1.arr.f_6[0], m_gSaf1.arr.f_6[1], m_gSaf1.arr.f_6[2]);
		ImGui::Text("Field 9: %d", m_gSaf1.arr.f_9);
		ImGui::Text("Field 10: %s", m_gSaf1.arr.f_10.str);
		ImGui::Text("Field 14: %d", m_gSaf1.arr.f_14);
		ImGui::Text("Field 15: %d", m_gSaf1.arr.f_15);
		ImGui::Text("Field 16: %s", m_gSaf1.arr.f_16.str);
		ImGui::Text("Field 22: %d", m_gSaf1.arr.f_22);
		ImGui::Text("Field 23: %d", m_gSaf1.arr.f_23);
		ImGui::Text("Field 24: %d", m_gSaf1.arr.f_24);
		ImGui::Text("Field 25: %d", m_gSaf1.arr.f_25);
		ImGui::Text("Field 26: %d", m_gSaf1.arr.f_26);
		ImGui::Text("Field 27: %d", m_gSaf1.arr.f_27);
		ImGui::Text("Field 28: %d", m_gSaf1.arr.f_28);
		ImGui::Text("Field 29: %d", m_gSaf1.arr.f_29);
		ImGui::Text("Field 30: %d", m_gSaf1.arr.f_30);
		ImGui::Text("Field 31: %d", m_gSaf1.arr.f_31);
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Strangers And Freaks Array 2", ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		if (m_gSaf1.id < m_gSaf2.size)
			m_gSaf2.id = m_gSaf1.id;
		ImGui::Text("Same ID as strangers and freaks ID: %d", m_gSaf2.id);
		ImGui::SameLine();
		ImGui::Text("(max: %d)", m_gSaf2.size);
		ImGui::Text("Field 0: %s", m_gSaf2.arr.f_0.to_string().c_str());
		ImGui::Text("Field 1: %d", m_gSaf2.arr.f_1);
		ImGui::Text("Field 2: %d", m_gSaf2.arr.f_2);
		ImGui::Text("Field 3: %d", m_gSaf2.arr.f_3);
		ImGui::Text("Field 4: %d", m_gSaf2.arr.f_4);
		ImGui::Text("Field 5: %f", m_gSaf2.arr.f_5);
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

	// Not sure about these next ones
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
