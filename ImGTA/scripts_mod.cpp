#include "scripts_mod.h"
#include <algorithm>
#include "natives.h"
#include "imgui.h"
#include "imgui_extras.h"
#include "utils.h"
#include "script.h"
#include "gta_script.h"
#include "script_names.h"

bool CompareScriptByHandle(ScriptObject a, ScriptObject b)
{
	return a.m_handle < b.m_handle;
}

bool CompareScriptByName(ScriptObject a, ScriptObject b)
{
	return a.m_scriptName < b.m_scriptName;
}

void ScriptsMod::Load()
{

}

void ScriptsMod::Unload()
{

}

void ScriptsMod::Think()
{
	if (m_constantUpdate || m_wantsUpdate)
	{
		std::lock_guard<std::mutex> lock(m_scriptsMutex);
		m_scripts.clear();
		SCRIPT::SCRIPT_THREAD_ITERATOR_RESET();
		int id;
		while ((id = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID()) != 0)
			m_scripts.push_back(ScriptObject(SCRIPT::_GET_NAME_OF_THREAD(id), id));

		if (m_sortByName)
			std::sort(m_scripts.begin(), m_scripts.end(), CompareScriptByName);
		else
			std::sort(m_scripts.begin(), m_scripts.end(), CompareScriptByHandle);

		m_noLoadingScreen = SCRIPT::GET_NO_LOADING_SCREEN();
		m_wantsUpdate = false;
	}

	if (m_drawInGame) {
		std::lock_guard<std::mutex> lock(m_scriptsMutex);
		char buf[128] = "";
		float yOff = m_inGameOffsetY;
		eFont font = eFont::FontChaletLondon;

		sprintf_s(buf, "Constant updates: %s", BoolToStr(m_constantUpdate));
		DrawTextToScreen(buf, m_inGameOffsetX, yOff, m_inGameFontSize, font);
		yOff += 0.02f;

		for (const auto & script : m_scripts)
		{
			sprintf_s(buf, "%s", script.m_scriptName.c_str());
			DrawTextToScreen(buf, m_inGameOffsetX, yOff, m_inGameFontSize, font);
			yOff += 0.02f;
		}
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
				if (ImGui::InputText("Custom name", m_startScriptName, sizeof(m_startScriptName), ImGuiInputTextFlags_EnterReturnsTrue))
				{
					RunOnNativeThread([=]
					{
						GTAScript script(m_startScriptName);
						if (script.IsValid())
							SYSTEM::START_NEW_SCRIPT(m_startScriptName, static_cast<int>(m_startFlags));

						m_wantsUpdate = true;
					});
				}
				if (ImGui::BeginMenu("Name"))
				{
					for (int i = 0; i < IM_ARRAYSIZE(scriptNames); i++)
					{
						if (ImGui::MenuItem(scriptNames[i]))
						{
							RunOnNativeThread([=]
							{
								GTAScript script(scriptNames[i]);
								if (script.IsValid())
									SYSTEM::START_NEW_SCRIPT(scriptNames[i], static_cast<int>(m_startFlags));

								m_wantsUpdate = true;
							});
						}
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Loading"))
		{
			if (ImGui::MenuItem("Stop loading screen"))
			{
				RunOnNativeThread([=]
				{
					SCRIPT::SHUTDOWN_LOADING_SCREEN();
				});
			}
			if (ImGui::BeginMenu("Set loading screen"))
			{
				ImGui::Checkbox("Toggle", &m_noLoadingScreenOption);
				if (ImGui::MenuItem("Set no loading screen"))
				{
					RunOnNativeThread([=]
					{
						SCRIPT::SET_NO_LOADING_SCREEN(m_noLoadingScreenOption);
					});
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Options"))
		{
			ImGui::MenuItem("Sort by name", NULL, &m_sortByName);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("HUD"))
		{
			ImGui::MenuItem("Show in game", NULL, &m_drawInGame);
			if (ImGui::BeginMenu("Offsets"))
			{
				if (ImGui::InputFloat("X offset", &m_inGameOffsetX, 0.01f))
					ClipFloat(m_inGameOffsetX, 0.0f, 0.95f);
				if (ImGui::InputFloat("Y offset", &m_inGameOffsetY, 0.01f))
					ClipFloat(m_inGameOffsetY, 0.0f, 0.95f);

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

	ImGui::Checkbox("Constant Updates?", &m_constantUpdate);
	if (!m_constantUpdate)
		if (ImGui::Button("Update"))
			m_wantsUpdate = true;

	ImGui::Text("Set no loading screen: %s", BoolToStr(m_noLoadingScreen));

	ImGui::Columns(2);
	if (m_initColumnWidth < 2)
		ImGui::SetColumnWidth(0, 200);
	else
		m_initColumnWidth++;
	ImGui::Separator();
	ImGui::Text("Name %c", m_sortByName ? '^' : ' '); ImGui::NextColumn();
	ImGui::Text("Handle %c", m_sortByName ? ' ' : '^'); ImGui::NextColumn();
	ImGui::Separator();

	std::lock_guard<std::mutex> lock(m_scriptsMutex);
	if (m_scripts.size() > 0)
	{
		for (auto &s : m_scripts)
		{
			if (ImGui::Selectable(s.m_scriptName.c_str(), false, ImGuiSelectableFlags_SpanAllColumns))
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