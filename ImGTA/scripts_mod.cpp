#include "scripts_mod.h"
#include "natives.h"
#include <algorithm>
#include "imgui_extras.h"
#include "script.h"
#include "gta_script.h"

bool CompareScript(ScriptObject a, ScriptObject b)
{
	return a.m_handle < b.m_handle;
}

void ScriptsMod::Load()
{

}

void ScriptsMod::Unload()
{

}

void ScriptsMod::Think()
{
	if (m_wantsUpdate)
	{
		std::lock_guard<std::mutex> lock(m_scriptsMutex);
		m_wantsUpdate = false;
		m_scripts.clear();
		SCRIPT::SCRIPT_THREAD_ITERATOR_RESET();
		int id;
		while ((id = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID()) != 0)
			m_scripts.push_back(ScriptObject(SCRIPT::_GET_NAME_OF_THREAD(id), id));

		std::sort(m_scripts.begin(), m_scripts.end(), CompareScript);
	}
}

void ScriptsMod::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Scripts"))
		{
			if (ImGui::MenuItem("Update"))
				m_wantsUpdate = true;


			if (ImGui::BeginMenu("Start"))
			{
				ImGuiExtras::BitField("Flags", &m_startFlags, nullptr);
				if (ImGui::InputText("Name", m_startScriptName, sizeof(m_startScriptName), ImGuiInputTextFlags_EnterReturnsTrue))
				{
					RunOnNativeThread([=]
					{
						GTAScript script(m_startScriptName);
						if (script.IsValid())
							SYSTEM::START_NEW_SCRIPT(m_startScriptName, static_cast<int>(m_startFlags));

						m_wantsUpdate = true;
					});
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

void ScriptsMod::ShowSelectedPopup()
{
	if (ImGui::BeginPopup("ScriptPropertiesPopup"))
	{
		if (ImGui::MenuItem("Terminate"))
		{
			RunOnNativeThread([=]
			{
				SCRIPT::TERMINATE_THREAD(m_selected->m_handle);
				m_wantsUpdate = true; // ask for the update only after this has actually been terminated.
			});
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

bool ScriptsMod::Draw()
{
	ImGui::SetWindowFontScale(m_menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_contentFontSize);

	if (m_scripts.size() > 0)
	{
		ImGui::Columns(2);
		ImGui::Separator();
		ImGui::Text("Name"); ImGui::NextColumn();
		ImGui::Text("Handle"); ImGui::NextColumn();
		ImGui::Separator();

		std::lock_guard<std::mutex> lock(m_scriptsMutex);
		for (auto &s : m_scripts)
		{
			if (ImGui::Selectable(s.m_windowName.c_str(), false, ImGuiSelectableFlags_SpanAllColumns))
			{
				m_selected = &s;
				ImGui::OpenPopup("ScriptPropertiesPopup");
			}
			ImGui::NextColumn();

			ImGui::Text("%d (0x%x)", s.m_handle, s.m_handle); ImGui::NextColumn();
		}
		ImGui::Columns(1);
		ImGui::Separator();
	}

	ShowSelectedPopup();

	return true;
}