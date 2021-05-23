#include "player_switch_mod.h"
#include "natives.h"
#include "script.h"
#include "imgui.h"
#include "main.h"
#include "utils.h"
#include "watch_entry.h"
#include "imgui_extras.h"
#include "mission_mod.h"
#include "global_id.h"

void PlayerSwitchMod::Load()
{

}

void PlayerSwitchMod::Unload()
{

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
	if (m_supportGlobals)
	{
		int offset = m_locationArrayStartAddr + m_locationID * sizeof(LocationArray) / 8;

		m_locationCount = *(int *)getGlobalPtr(m_locationArraySizeAddr);
		m_locationArray = *(LocationArray *)getGlobalPtr(offset);
	}

	m_switchInProgress = STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS();
	m_switchType = STREAMING::GET_PLAYER_SWITCH_TYPE();
	m_switchState = STREAMING::GET_PLAYER_SWITCH_STATE();
	m_shortSwitchState = STREAMING::GET_PLAYER_SHORT_SWITCH_STATE();

	if (m_supportGlobals)
	{
		m_currentCharacterID = *(int *)getGlobalPtr(GlobalID::_102834); 
		m_previousCharacterID = *(int *)getGlobalPtr(GlobalID::_102835);
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
	ImGui::SetWindowFontScale(m_menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_contentFontSize);

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

	if (m_supportGlobals)
	{
		ImGui::Separator();
		if (ImGui::TreeNode("Player switch locations?"))
		{
			if (ImGui::InputInt("Handle", &m_locationID)) {
				ClipInt(m_locationID, 0, m_locationCount - 1);
				m_wantsUpdate = true;
			}

			ImGui::Text("Vector 0: (%.4f, %.4f, %.4f)", m_locationArray.field_0.x, m_locationArray.field_0.y, m_locationArray.field_0.z);
			ImGui::Text("Vector 1: (%.4f, %.4f, %.4f)", m_locationArray.field_3.x, m_locationArray.field_3.y, m_locationArray.field_3.z);
			ImGui::Text("Field 2: %f", m_locationArray.field_6);
			ImGui::Text("Field 3: %d", m_locationArray.field_7);
			ImGui::Text("Field 4: %d", m_locationArray.field_8);
			ImGui::Text("Character ID: %d (%s)", m_locationArray.field_9, CharacterIDStr((CharacterID)m_locationArray.field_9));
			ImGui::TreePop();
		}
	}
	return true;
}

