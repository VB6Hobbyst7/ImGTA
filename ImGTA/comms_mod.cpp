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

		int messageArray2Offset = m_messageArray2StartAddr + m_characterID * sizeof(MessageArray2) / 8;
		m_messageArray2Count = *(int *)getGlobalPtr(m_messageArray2SizeAddr);
		m_messageArray2 = *(MessageArray2 *)getGlobalPtr(messageArray2Offset);

		m_unk15750 = std::string((char *)getGlobalPtr(GlobalID::_15750));
		m_unk15756 = std::string((char *)getGlobalPtr(GlobalID::_15756));
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

	ImGui::Separator();
	ImGui::Text("Unk15750: %s", m_unk15750.c_str());
	ImGui::Text("Unk15756: %s", m_unk15756.c_str());

	if (m_supportGlobals)
	{
		ImGui::Separator();
		if (ImGui::TreeNode("Messages?"))
		{
			if (ImGui::InputInt("Message ID", &m_characterID))
			{
				ClipInt(m_characterID, 0, m_characterCount - 1);
				m_wantsUpdate = true;
			}
			ImGui::SameLine();
			ImGui::Text("< %d", m_characterCount);

			ImGui::Text("Hash: %d", m_characterArray.field_0);
			ImGui::Text("Field 1: %d", m_characterArray.field_1);
			ImGui::Text("Field 2: %d", m_characterArray.field_2);
			ImGui::Text("Field 3: %s", m_characterArray.field_3);
			ImGui::Text("Field 7: %s", m_characterArray.field_7);
			ImGui::Text("Field B: %d", m_characterArray.field_11);
			ImGui::Text("Field C: %d", m_characterArray.field_12_size);
			std::string field_C = "Field C: ";
			for (int i = 0; i < m_characterArray.field_12_size; ++i)
				field_C += std::to_string(m_characterArray.field_12[i].val) + ", ";
			ImGui::Text(field_C.c_str());
			ImGui::Text("Field 11: %d", m_characterArray.field_17);
			ImGui::Text("Field 12: %d", m_characterArray.field_18);
			ImGui::Text("Field 13: %d", m_characterArray.field_20_size);
			std::string field_13 = "Field 13: ";
			for (int i = 0; i < m_characterArray.field_20_size; ++i)
				field_13 += std::to_string(m_characterArray.field_20[i].val) + ", ";
			ImGui::Text(field_13.c_str());
			ImGui::Text("Field 18: %d", m_characterArray.field_25_size);
			std::string field_18 = "Field 18: ";
			for (int i = 0; i < m_characterArray.field_25_size; ++i)
				field_18 += std::to_string(m_characterArray.field_25[i].val) + ", ";
			ImGui::Text(field_18.c_str());
			ImGui::TreePop();
		}

		ImGui::Separator();
		if (ImGui::TreeNode("Call numbers?"))
		{
			ImGui::Text("Same ID as mission ID: %d", m_characterID);
			ImGui::SameLine();
			ImGui::Text("< %d", m_messageArray2Count);
			ImGui::Text("Field 0: %s", m_messageArray2.f_0);
			ImGui::Text("Field 4: %s", m_messageArray2.f_4);
			ImGui::Text("Field 8: %d", m_messageArray2.f_8);
			ImGui::Text("Field 9: %d", m_messageArray2.f_9);
			ImGui::TreePop();
		}
	}
	return true;
}

