#include "player_switch_mod.h"
#include "natives.h"
#include "script.h"
#include "imgui.h"
#include "main.h"
#include "utils.h"
#include "watch_entry.h"
#include "imgui_extras.h"
#include "mission_mod.h"

void PlayerSwitchMod::Load()
{

}

void PlayerSwitchMod::Unload()
{
	
}

void PlayerSwitchMod::Think()
{
	if ((m_bConstantUpdate || m_bWantsUpdate))
	{
		UpdateLocationData(m_bWantsUpdate);
		m_bWantsUpdate = false;
	}
}

void PlayerSwitchMod::UpdateLocationData(bool once) {
	if (m_supportGlobals)
	{
		int offset = m_locationArrayStartAddr + m_locationID * sizeof(LocationArray) / 8;

		m_locationCount = *(int *) getGlobalPtr(m_locationArraySizeAddr);
		m_locationArray = *(LocationArray *) getGlobalPtr(offset);
	}

	m_switchInProgress = STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS();
	m_switchType = STREAMING::GET_PLAYER_SWITCH_TYPE();
	m_switchState = STREAMING::GET_PLAYER_SWITCH_STATE();
	m_shortSwitchState = STREAMING::GET_PLAYER_SHORT_SWITCH_STATE();

	if (m_supportGlobals)
	{
		int characterArrayOffset = m_characterArrayStartAddr + m_characterID * sizeof(MessageArray) / 8;
		m_characterCount = *(int *)getGlobalPtr(m_characterArraySizeAddr);
		m_characterArray = *(MessageArray *)getGlobalPtr(characterArrayOffset);

		m_currentCharacterID = *(int *)getGlobalPtr(0x191B2); // Global_17C49.f_6C1.f_21B.f_C8D
		m_previousCharacterID = *(int *)getGlobalPtr(0x19B4); // Global_17C49.f_6C1.f_21B.f_C8F
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

std::string switchTypeStr(SwitchType type) {
	switch (type) {
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

	ImGui::Checkbox("Constant Updates?", &m_bConstantUpdate);
	if (!m_bConstantUpdate)
		if (ImGui::Button("Update"))
			m_bWantsUpdate = true;

	ImGui::Separator();
	if (m_supportGlobals)
	{
		ImGui::Text("Curent Character ID: %d (%s)", m_currentCharacterID, CharacterIDStr((CharacterID)m_currentCharacterID));
		ImGui::Text("Previous Character ID: %d (%s)", m_previousCharacterID, CharacterIDStr((CharacterID)m_previousCharacterID));
	}
	ImGui::Text("Switch in progress: %d", m_switchInProgress);
	ImGui::Text("Switch type: %s (%d)", switchTypeStr(SwitchType(m_switchType)).c_str(), m_switchType);
	ImGui::Text("Switch state: %d", m_switchState);
	ImGui::Text("Short switch state: %d", m_shortSwitchState);

	if (m_supportGlobals)
	{
		if (ImGui::TreeNode("Messages")) {
			if (ImGui::InputInt("Message ID", &m_characterID))
			{
				ClipInt(m_characterID, 0, m_characterCount - 1);
				m_bWantsUpdate = true;
			}

			ImGui::Text("Hash: %d", m_characterArray.field_0);
			ImGui::Text("Field 1: %d", m_characterArray.field_1);
			ImGui::Text("Field 2: %d", m_characterArray.field_2);
			ImGui::Text("Field 3: %s", m_characterArray.field_3);
			ImGui::Text("Field 7: %s", m_characterArray.field_7);
			ImGui::Text("Field B: %d", m_characterArray.field_B);
			ImGui::Text("Field C: %d", m_characterArray.field_C_size);
			std::string field_C = "Field C: ";
			for (int i = 0; i < m_characterArray.field_C_size; ++i)
				field_C += std::to_string(m_characterArray.field_C[i].val) + ", ";
			ImGui::Text(field_C.c_str());
			ImGui::Text("Field 11: %d", m_characterArray.field_11);
			ImGui::Text("Field 12: %d", m_characterArray.field_12);
			ImGui::Text("Field 13: %d", m_characterArray.field_13_size);
			std::string field_13 = "Field 13: ";
			for (int i = 0; i < m_characterArray.field_13_size; ++i)
				field_13 += std::to_string(m_characterArray.field_13[i].val) + ", ";
			ImGui::Text(field_13.c_str());
			ImGui::Text("Field 18: %d", m_characterArray.field_18_size);
			std::string field_18 = "Field 18: ";
			for (int i = 0; i < m_characterArray.field_18_size; ++i)
				field_18 += std::to_string(m_characterArray.field_18[i].val) + ", ";
			ImGui::Text(field_18.c_str());
			ImGui::TreePop();
		}

		ImGui::Separator();
		if (ImGui::TreeNode("Player switch locations?"))
		{
			if (ImGui::InputInt("Handle", &m_locationID)) {
				ClipInt(m_locationID, 0, m_locationCount - 1);
				m_bWantsUpdate = true;
			}

			ImGui::Text("Vector 0: (%.4f, %.4f, %.4f)", m_locationArray.field_0.x, m_locationArray.field_0.y, m_locationArray.field_0.z);
			ImGui::Text("Vector 1: (%.4f, %.4f, %.4f)", m_locationArray.field_1.x, m_locationArray.field_1.y, m_locationArray.field_1.z);
			ImGui::Text("Field 2: %f", m_locationArray.field_2);
			ImGui::Text("Field 3: %d", m_locationArray.field_3);
			ImGui::Text("Field 4: %d", m_locationArray.field_4);
			ImGui::Text("Character ID: %d (%s)", m_locationArray.field_5, CharacterIDStr((CharacterID)m_locationArray.field_5));
			ImGui::TreePop();
		}
	}
	return true;
}

