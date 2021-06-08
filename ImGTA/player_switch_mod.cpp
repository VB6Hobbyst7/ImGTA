/*
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "player_switch_mod.h"

#include "script.h"
#include "watch_entry.h"
#include "global_id.h"

#include "natives.h"

#include "imgui.h"
#include "imgui_extras.h"

PlayerSwitchMod::PlayerSwitchMod(DLLObject & dllObject, bool supportGlobals) :
	Mod(dllObject, "Player Switch", true, supportGlobals),
	m_gSwitch1(GlobalID::_85405),
	m_gSwitch2(GlobalID::_85570),
	m_gSwitch4(GlobalID::_101149),
	m_gSwitch5(GlobalID::_88538)
{
	m_windowFlags = ImGuiWindowFlags_MenuBar;
}

void PlayerSwitchMod::Load()
{
	m_settings = m_dllObject.GetUserSettings().playerSwitch;
}

void PlayerSwitchMod::Unload()
{
	m_dllObject.GetUserSettings().playerSwitch = m_settings;
}

void PlayerSwitchMod::Think()
{
	if (m_constantUpdate || m_wantsUpdate)
	{
		UpdateLocationData();
		m_wantsUpdate = false;
	}
}

void PlayerSwitchMod::UpdateLocationData()
{
	m_switchInProgress = STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS();
	m_switchType = STREAMING::GET_PLAYER_SWITCH_TYPE();
	m_switchState = STREAMING::GET_PLAYER_SWITCH_STATE();
	m_shortSwitchState = STREAMING::GET_PLAYER_SHORT_SWITCH_STATE();
	m_switchJumpCutIndex = STREAMING::GET_PLAYER_SWITCH_JUMP_CUT_INDEX();
	m_switchReadyForDescent = STREAMING::IS_SWITCH_READY_FOR_DESCENT();
	m_switchSkippingDescent = STREAMING::IS_SWITCH_SKIPPING_DESCENT();
	m_unkSwitch = STREAMING::_0x933BBEEB8C61B5F4();
	m_unkSwitch2 = STREAMING::_0x71E7B2E657449AAD();
	m_switchInterpOutDuration = STREAMING::GET_PLAYER_SWITCH_INTERP_OUT_DURATION();
	m_switchInterpOutCurrentTime = STREAMING::GET_PLAYER_SWITCH_INTERP_OUT_CURRENT_TIME();

	if (m_supportGlobals)
	{
		m_gSwitch1.LoadElement();
		m_gSwitch2.LoadElement();
		m_gSwitch4.LoadElement();
		m_gSwitch5.LoadElement();

		m_currentCharacterID = *(int *)GetGlobalPtr(GlobalID::_102834); 
		m_previousCharacterID = *(int *)GetGlobalPtr(GlobalID::_102835);
	}
}

void PlayerSwitchMod::DrawMenuBar()
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

std::string SwitchTypeStr(SwitchType type)
{
	switch (type)
	{
	case SwitchType::SWITCH_TYPE_AUTO:
		return std::string("AUTO");
	case SwitchType::SWITCH_TYPE_LONG:
		return std::string("LONG");
	case SwitchType::SWITCH_TYPE_MEDIUM:
		return std::string("MEDIUM");
	case SwitchType::SWITCH_TYPE_SHORT:
		return std::string("SHORT");
	default:
		return std::string("");
	}
}

bool PlayerSwitchMod::Draw()
{
	ImGui::SetWindowFontScale(m_settings.common.menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_settings.common.contentFontSize);

	ImGui::Checkbox("Constant Updates?", &m_constantUpdate);
	if (!m_constantUpdate)
		if (ImGui::Button("Update"))
			m_wantsUpdate = true;

	ImGui::Separator();
	if (m_supportGlobals)
	{
		ImGui::Text("Curent Character ID: %d (%s)", m_currentCharacterID, CharacterIDStr((CharacterID)m_currentCharacterID));
		ImGui::Text("Previous Character ID: %d (%s)", m_previousCharacterID, CharacterIDStr((CharacterID)m_previousCharacterID));
	}
	ImGui::Text("Switch in progress: %d", m_switchInProgress);
	ImGui::Text("Switch type: %s (%d)", SwitchTypeStr(SwitchType(m_switchType)).c_str(), m_switchType);
	ImGui::Text("Switch state: %d", m_switchState);
	ImGui::Text("Short switch state: %d", m_shortSwitchState);
	ImGui::Text("Switch jump cut index: %d", m_switchJumpCutIndex);
	ImGui::Text("Switch ready for descent: %s", BoolToStr(m_switchReadyForDescent));
	ImGui::Text("Switch skipping descent: %s", BoolToStr(m_switchSkippingDescent));
	ImGui::Text("Unk switch1: %s", BoolToStr(m_unkSwitch));
	ImGui::Text("Unk switch2: %s", BoolToStr(m_unkSwitch2));
	ImGui::Text("Switch interp out duration: %d", m_switchInterpOutDuration);
	ImGui::Text("Switch interp out current time: %d", m_switchInterpOutCurrentTime);

	if (m_supportGlobals)
	{
		ImGui::Separator();
		if (ImGui::TreeNodeEx("Places close to player switch locations?", ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
			if (ImGui::InputInt("ID", &m_gSwitch1.id)) {
				ClipInt(m_gSwitch1.id, 0, m_gSwitch1.size - 1);
				m_wantsUpdate = true;
			}
			ImGui::SameLine();
			ImGui::Text("(max: %d)", m_gSwitch1.size);

			ImGui::Text("Vector 0: (%.4f, %.4f, %.4f)", m_gSwitch1.arr.field_0.x, m_gSwitch1.arr.field_0.y, m_gSwitch1.arr.field_0.z);
			ImGui::Text("Vector 1: (%.4f, %.4f, %.4f)", m_gSwitch1.arr.field_3.x, m_gSwitch1.arr.field_3.y, m_gSwitch1.arr.field_3.z);
			ImGui::Text("Field 2: %f", m_gSwitch1.arr.field_6);
			ImGui::Text("Field 3: %d", m_gSwitch1.arr.field_7);
			ImGui::Text("Field 4: %d", m_gSwitch1.arr.field_8);
			ImGui::Text("Character ID: %d (%s)", m_gSwitch1.arr.characterId, CharacterIDStr((CharacterID)m_gSwitch1.arr.characterId));
			ImGui::TreePop();
		}

		ImGui::Separator();
		if (ImGui::TreeNodeEx("Hospital switches", ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
			if (ImGui::InputInt("ID", &m_gSwitch2.id)) {
				ClipInt(m_gSwitch2.id, 0, m_gSwitch2.size - 1);
				m_wantsUpdate = true;
			}
			ImGui::SameLine();
			ImGui::Text("(max: %d)", m_gSwitch2.size);

			ImGui::Text("Vector 0: (%.4f, %.4f, %.4f)", m_gSwitch2.arr.f_0.x, m_gSwitch2.arr.f_0.y, m_gSwitch2.arr.f_0.z);
			ImGui::Text("Potential coords: (%.4f, %.4f, %.4f)", m_gSwitch2.arr.f_3.x, m_gSwitch2.arr.f_3.y, m_gSwitch2.arr.f_3.z);
			ImGui::Text("Field 2: %f", m_gSwitch2.arr.f_6);
			ImGui::Text("Field 3: %d", m_gSwitch2.arr.f_7);
			ImGui::Text("Hospital ID: %d", m_gSwitch2.arr.hospitalIndex);
			ImGui::TreePop();
		}

		ImGui::Separator();
		if (ImGui::TreeNodeEx("Switch array 4", ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
			if (ImGui::InputInt("ID", &m_gSwitch4.id)) {
				ClipInt(m_gSwitch4.id, 0, m_gSwitch4.size - 1);
				m_wantsUpdate = true;
			}
			ImGui::SameLine();
			ImGui::Text("(max: %d)", m_gSwitch4.size);

			ImGui::Text("Potential coords: (%.4f, %.4f, %.4f)", m_gSwitch4.arr.f_0.x, m_gSwitch4.arr.f_0.y, m_gSwitch4.arr.f_0.z);
			ImGui::TreePop();
		}

		ImGui::Separator();
		if (ImGui::TreeNodeEx("Switch array 5", ImGuiTreeNodeFlags_SpanAvailWidth))
		{
			ImGui::SetNextItemWidth(m_inputIDWidgetWidth);
			if (ImGui::InputInt("ID", &m_gSwitch5.id)) {
				ClipInt(m_gSwitch5.id, 0, m_gSwitch5.size - 1);
				m_wantsUpdate = true;
			}
			ImGui::SameLine();
			ImGui::Text("(max: %d)", m_gSwitch5.size);

			ImGui::Text("Potential coords: (%.4f, %.4f, %.4f)", m_gSwitch5.arr.f_0.x, m_gSwitch5.arr.f_0.y, m_gSwitch5.arr.f_0.z);
			ImGui::TreePop();
		}
	}
	return true;
}

