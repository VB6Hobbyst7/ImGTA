#include "comms_mod.h"
#include "natives.h"
#include "script.h"
#include "imgui.h"
#include "main.h"
#include "utils.h"
#include "watch_entry.h"
#include "imgui_extras.h"
#include "mission_mod.h"
#include "global_id.h"

void CommsMod::Load()
{

}

void CommsMod::Unload()
{

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
		int characterArrayOffset = m_characterArrayStartAddr + m_characterID * sizeof(MessageArray) / 8;
		m_characterCount = *(int *)getGlobalPtr(m_characterArraySizeAddr);
		m_characterArray = *(MessageArray *)getGlobalPtr(characterArrayOffset);
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
	ImGui::SetWindowFontScale(m_menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_contentFontSize);

	ImGui::Checkbox("Constant Updates?", &m_constantUpdate);
	if (!m_constantUpdate)
		if (ImGui::Button("Update"))
			m_wantsUpdate = true;

	if (m_supportGlobals)
	{
		if (ImGui::TreeNode("Messages"))
		{
			if (ImGui::InputInt("Message ID", &m_characterID))
			{
				ClipInt(m_characterID, 0, m_characterCount - 1);
				m_wantsUpdate = true;
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
	}
	return true;
}

