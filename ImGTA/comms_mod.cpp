/*
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "comms_mod.h"

#include "script.h"
#include "watch_entry.h"
#include "mission_mod.h"
#include "global_id.h"

#include "natives.h"

#include "imgui.h"
#include "imgui_extras.h"

#include <cmath>

CommsMod::CommsMod(DLLObject & dllObject, bool supportGlobals) :
	Mod(dllObject, "Comms", true, supportGlobals),
	m_gMessage1(GlobalID::_127127),
	m_gMessage2(GlobalID::_97),
	m_gMessage3(GlobalID::_2270),
	m_gMessage4(GlobalID::_120988),
	m_gMessage5(GlobalID::_2873),
	m_gMessage6(GlobalID::_1683749),
	m_gMessage7(GlobalID::_109748),
	m_gEmail1(GlobalID::_45154)
{
	m_windowFlags = ImGuiWindowFlags_MenuBar;
}

void CommsMod::Load()
{
	m_settings = m_dllObject.GetUserSettings().comms;
}

void CommsMod::Unload()
{
	m_dllObject.GetUserSettings().comms = m_settings;
}

void CommsMod::Think()
{
	if (m_constantUpdate || m_wantsUpdate)
	{
		UpdateLocationData();
		m_wantsUpdate = false;
	}
}

void CommsMod::UpdateLocationData()
{
	if (m_supportGlobals)
	{
		m_gMessage1.LoadElement();
		m_gMessage2.LoadElement();
		m_gMessage3.LoadElement();
		m_gMessage4.LoadElement();
		m_gMessage5.LoadElement();
		m_gMessage6.LoadElement();
		m_gMessage7.LoadElement();
		m_gEmail1.LoadElement();

		// Global_35464 -> store time where it's possible to receive message. not always updated though
		m_nextReceivingTime = *(int *)GetGlobalPtr(GlobalID::_35464);
		int tmp = (MISC::GET_GAME_TIMER() - m_nextReceivingTime) / 1000;
		m_timeLeftForReceiving = tmp >= 0 ? tmp : 0;
		m_unk15750 = std::string((char *)GetGlobalPtr(GlobalID::_15750));
		m_unk15756 = std::string((char *)GetGlobalPtr(GlobalID::_15756));
		m_unk15774 = std::string((char *)GetGlobalPtr(GlobalID::_15774));
		m_unk15780 = std::string((char *)GetGlobalPtr(GlobalID::_15780));
		m_unk15840 = std::string((char *)GetGlobalPtr(GlobalID::_15840));
	}
}

void CommsMod::DrawMenuBar()
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

bool CommsMod::Draw()
{
	ImGui::SetWindowFontScale(m_settings.common.menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_settings.common.contentFontSize);

	ImGui::Checkbox("Constant Updates?", &m_constantUpdate);
	if (!m_constantUpdate)
		if (ImGui::Button("Update"))
			m_wantsUpdate = true;

	ImGui::Separator();
	ImGui::Text("Next time comms can be received: %d", m_nextReceivingTime);
	ImGui::Text("Time left for being able to receive comms: %d sec", m_timeLeftForReceiving);
	ImGui::Text("Unk15750: %s", m_unk15750.c_str());
	ImGui::Text("Unk15756: %s", m_unk15756.c_str());
	ImGui::Text("Unk15774: %s", m_unk15774.c_str());
	ImGui::Text("Unk15780: %s", m_unk15780.c_str());
	ImGui::Text("Unk15840: %s", m_unk15840.c_str());

	if (m_supportGlobals)
	{
		ImGui::Separator();
		if (ImGui::TreeNodeEx("Messages?", ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
			if (ImGui::InputInt("Message ID", &m_gMessage1.id))
			{
				ClipInt(m_gMessage1.id, 0, m_gMessage1.size - 1);
				m_wantsUpdate = true;
			}
			ImGui::SameLine();
			ImGui::Text("(max: %d)", m_gMessage1.size);

			ImGui::Text("Hash: %d", m_gMessage1.arr.field_0);
			ImGui::Text("Field 1: %d", m_gMessage1.arr.field_1);
			ImGui::Text("Field 2: %d", m_gMessage1.arr.field_2);
			ImGui::Text("Field 3: %s", m_gMessage1.arr.field_3);
			ImGui::Text("Field 7: %s", m_gMessage1.arr.field_7);
			ImGui::Text("Field B: %d", m_gMessage1.arr.field_11);
			ImGui::Text("Field C: %d", m_gMessage1.arr.field_12_size);
			std::string field_C = "Field C: ";
			for (int i = 0; i < m_gMessage1.arr.field_12_size; ++i)
				field_C += std::to_string(m_gMessage1.arr.field_12[i].val) + ", ";
			ImGui::Text(field_C.c_str());
			ImGui::Text("Field 11: %d", m_gMessage1.arr.field_17);
			ImGui::Text("Field 12: %d", m_gMessage1.arr.field_18);
			ImGui::Text("Field 13: %d", m_gMessage1.arr.field_20_size);
			std::string field_13 = "Field 13: ";
			for (int i = 0; i < m_gMessage1.arr.field_20_size; ++i)
				field_13 += std::to_string(m_gMessage1.arr.field_20[i].val) + ", ";
			ImGui::Text(field_13.c_str());
			ImGui::Text("Field 18: %d", m_gMessage1.arr.field_25_size);
			std::string field_18 = "Field 18: ";
			for (int i = 0; i < m_gMessage1.arr.field_25_size; ++i)
				field_18 += std::to_string(m_gMessage1.arr.field_25[i].val) + ", ";
			ImGui::Text(field_18.c_str());
			ImGui::TreePop();
		}

		ImGui::Separator();
		if (ImGui::TreeNodeEx("Call numbers?", ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			if (m_gMessage1.id < m_gMessage2.size)
				m_gMessage2.id = m_gMessage1.id;
			ImGui::Text("Same ID as mission ID: %d", m_gMessage2.id);
			ImGui::SameLine();
			ImGui::Text("(max: %d)", m_gMessage2.size);
			ImGui::Text("Field 0: %s", m_gMessage2.arr.f_0);
			ImGui::Text("Field 4: %s", m_gMessage2.arr.f_4);
			ImGui::Text("Field 8: %d", m_gMessage2.arr.f_8);
			ImGui::Text("Field 9: %d", m_gMessage2.arr.f_9);
			ImGui::TreePop();
		}

		ImGui::Separator();
		if (ImGui::TreeNodeEx("Message Array 3", ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
			if (ImGui::InputInt("Array 3 ID", &m_gMessage3.id))
			{
				ClipInt(m_gMessage3.id, 0, m_gMessage3.size - 1);
				m_wantsUpdate = true;
			}
			ImGui::SameLine();
			ImGui::Text("(max: %d)", m_gMessage3.size);

			ImGui::Text("Field 0: %s", m_gMessage3.arr.f_0);
			ImGui::Text("Field 4: %d", m_gMessage3.arr.f_4);
			ImGui::Text("Script name: %s", m_gMessage3.arr.scriptName);
			ImGui::Text("Script hash: %d", m_gMessage3.arr.scriptHash);
			ImGui::Text("Field 10: %d", m_gMessage3.arr.f_10);
			ImGui::Text("Field 11: %d", m_gMessage3.arr.f_11);
			ImGui::Text("Field 12: %d", m_gMessage3.arr.f_12);
			ImGui::Text("Field 13: %d", m_gMessage3.arr.f_13);
			ImGui::Text("Field 14: %d", m_gMessage3.arr.f_14);
			ImGui::TreePop();
		}

		ImGui::Separator();
		if (ImGui::TreeNodeEx("Message Array 4", ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
			if (ImGui::InputInt("Array 4 ID", &m_gMessage4.id))
			{
				ClipInt(m_gMessage4.id, 0, m_gMessage4.size - 1);
				m_wantsUpdate = true;
			}
			ImGui::SameLine();
			ImGui::Text("(max: %d)", m_gMessage4.size);

			ImGui::Text("Field 0: %s", m_gMessage4.arr.f_0);
			ImGui::Text("Field 4: %s", m_gMessage4.arr.f_4);
			ImGui::Text("Timer: %d", m_gMessage4.arr.timer);
			ImGui::Text("Field 9: %d", m_gMessage4.arr.f_9);
			ImGui::Text("Field 10: %d", m_gMessage4.arr.f_10);
			ImGui::Text("Field 11: %d", m_gMessage4.arr.f_11);
			ImGui::Text("Field 12: %d", m_gMessage4.arr.f_12);
			ImGui::Text("Field 13: %d", m_gMessage4.arr.f_13);
			ImGui::Text("Field 14: %d", m_gMessage4.arr.f_14);
			ImGui::Text("Field 15: %d", m_gMessage4.arr.f_15);
			ImGui::TreePop();
		}

		ImGui::Separator();
		if (ImGui::TreeNodeEx("Message Array 5", ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
			if (ImGui::InputInt("Array 5 ID", &m_gMessage5.id))
			{
				ClipInt(m_gMessage5.id, 0, m_gMessage5.size - 1);
				m_wantsUpdate = true;
			}
			ImGui::SameLine();
			ImGui::Text("(max: %d)", m_gMessage5.size);

			ImGui::Text("Field 0: %s", m_gMessage5.arr.f_0);
			ImGui::Text("Field 5: %d", m_gMessage5.arr.f_5);
			ImGui::TreePop();
		}

		ImGui::Separator();
		if (ImGui::TreeNodeEx("Message Array 6", ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
			if (ImGui::InputInt("Array 6 ID", &m_gMessage6.id))
			{
				ClipInt(m_gMessage6.id, 0, m_gMessage6.size - 1);
				m_wantsUpdate = true;
			}
			ImGui::SameLine();
			ImGui::Text("(max: %d)", m_gMessage6.size);

			ImGui::Text("Field 0: %s", m_gMessage6.arr.f_0);
			ImGui::TreePop();
		}

		ImGui::Separator();
		if (ImGui::TreeNodeEx("Received texts", ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
			if (ImGui::InputInt("Array 7 ID", &m_gMessage7.id))
			{
				ClipInt(m_gMessage7.id, 0, m_gMessage7.size - 1);
				m_wantsUpdate = true;
			}
			ImGui::SameLine();
			ImGui::Text("(max: %d)", m_gMessage7.size);

			ImGui::Text("Name: %s", m_gMessage7.arr.name);
			ImGui::Text("Notification ID: %d", m_gMessage7.arr.notificationId);
			ImGui::Text("Field 17: %d", m_gMessage7.arr.f_17);
			ImGui::Text("Reception Time (hour, min, sec): %d, %d, %d", m_gMessage7.arr.timeAndDate.hours,
				m_gMessage7.arr.timeAndDate.minutes,
				m_gMessage7.arr.timeAndDate.seconds);
			ImGui::Text("Reception Date (day,month,year): %d, %d, %d", m_gMessage7.arr.timeAndDate.day,
				m_gMessage7.arr.timeAndDate.month,
				m_gMessage7.arr.timeAndDate.year);
			ImGui::Text("Field 24: %d", m_gMessage7.arr.f_24);
			ImGui::Text("Field 25: %d", m_gMessage7.arr.f_25);
			ImGui::Text("Field 26: %d", m_gMessage7.arr.f_26);
			ImGui::Text("Field 27: %d", m_gMessage7.arr.f_27);
			ImGui::Text("Field 28: %d", m_gMessage7.arr.f_28);
			ImGui::Text("Field 29: %d", m_gMessage7.arr.f_29);
			ImGui::Text("Field 30: %d", m_gMessage7.arr.f_30);
			ImGui::Text("Field 31: %d", m_gMessage7.arr.f_31);
			ImGui::Text("Field 32: %d", m_gMessage7.arr.f_32);
			ImGui::Text("Field 33: %s", m_gMessage7.arr.f_33);
			ImGui::Text("Field 49: %d", m_gMessage7.arr.f_49);
			ImGui::Text("Field 50: %s", m_gMessage7.arr.f_50);
			ImGui::Text("Field 66: %d", m_gMessage7.arr.f_66);
			ImGui::Text("Field 67: %s", m_gMessage7.arr.f_67);
			ImGui::Text("Field 83: %s", m_gMessage7.arr.f_83);
			ImGui::Text("Message recipient array size: %d", m_gMessage7.arr.f_99_size);
			std::string field_99 = "Message recipient (michael, franklin, trevor, multiplayer?): ";
			for (int i = 0; i < m_gMessage7.arr.f_99_size; ++i)
				field_99 += std::to_string(m_gMessage7.arr.type[i].val) + ", ";
			ImGui::Text(field_99.c_str());
			ImGui::TreePop();
		}

		ImGui::Separator();
		if (ImGui::TreeNodeEx("Email array", ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
			if (ImGui::InputInt("Email ID", &m_gEmail1.id))
			{
				ClipInt(m_gEmail1.id, 0, m_gEmail1.size - 1);
				m_wantsUpdate = true;
			}
			ImGui::SameLine();
			ImGui::Text("(max: %d)", m_gEmail1.size);

			ImGui::Text("Field 0: %d", m_gEmail1.arr.f_0);
			ImGui::Text("Field 1: %d", m_gEmail1.arr.f_1);
			ImGui::Text("Field 2: %d", m_gEmail1.arr.f_2);
			ImGui::Text("Field 3: %d", m_gEmail1.arr.f_3);
			std::string field_4 = "Field 4: ";
			for (int i = 0; i < m_gEmail1.arr.f_3; ++i)
				field_4 += std::to_string(m_gEmail1.arr.f_4[i].val) + ", ";
			ImGui::Text(field_4.c_str());
			ImGui::Text("Field 9: %d", m_gEmail1.arr.f_9);
			ImGui::Text("Field 10 size: %d", m_gEmail1.arr.f_10_size);
			for (int i = 0; i < m_gEmail1.arr.f_10_size; ++i)
			{
				ImGui::Text("Field 0 of field 10: %d", m_gEmail1.arr.f_10[i].f_0);
				ImGui::Text("Field 1 of field 10: %d", m_gEmail1.arr.f_10[i].f_1);
				ImGui::Text("Field 2 of field 10: %s", m_gEmail1.arr.f_10[i].f_2);
				ImGui::Text("Field 6 of field 10: %d", m_gEmail1.arr.f_10[i].f_6);
				ImGui::Text("Field 7 size of field 10: %d", m_gEmail1.arr.f_10[i].f_7_size);
				for (int j = 0; j < m_gEmail1.arr.f_10[i].f_7_size; ++j)
					ImGui::Text("Field 0 of field 7 of field 10: %s", m_gEmail1.arr.f_10[i].f_7[j].f_0);
			}
			ImGui::TreePop();
		}
	}
	return true;
}

