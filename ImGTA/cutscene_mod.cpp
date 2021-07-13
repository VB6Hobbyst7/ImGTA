/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "cutscene_mod.h"

#include "script.h"
#include "utils.h"
#include "cutscene_names.h"

#include "natives.h"

#include "imgui_extras.h"

#include <mutex>
#include <condition_variable>

void CutsceneMod::Load()
{
	m_settings = m_dllObject.GetUserSettings().cutscene;
}

void CutsceneMod::Unload()
{
	m_dllObject.GetUserSettings().cutscene = m_settings;
}

void CutsceneMod::Think()
{
	m_hasCutsceneLoaded = CUTSCENE::HAS_CUTSCENE_LOADED();
	m_hasCutsceneFinished = CUTSCENE::HAS_CUTSCENE_FINISHED();
	m_wasCutsceneSkipped = CUTSCENE::WAS_CUTSCENE_SKIPPED();
	m_isCutscenePlaying = CUTSCENE::IS_CUTSCENE_PLAYING();
	m_isCutsceneActive = CUTSCENE::IS_CUTSCENE_ACTIVE();

	m_cutsceneTime = CUTSCENE::GET_CUTSCENE_TIME();
	m_cutsceneTotalDuration = CUTSCENE::GET_CUTSCENE_TOTAL_DURATION();
	m_cutsceneSectionPlaying = CUTSCENE::GET_CUTSCENE_SECTION_PLAYING();

	m_canRequestAssetsForCutsceneEntity = CUTSCENE::CAN_REQUEST_ASSETS_FOR_CUTSCENE_ENTITY();
	m_hasCutsceneCutThisFrame = CUTSCENE::_HAS_CUTSCENE_CUT_THIS_FRAME();

	bool found = false;
	for (int i = 0; i < IM_ARRAYSIZE(cutsceneNames); i++)
	{
		// There should only be one loaded cutscene
		if (CUTSCENE::HAS_THIS_CUTSCENE_LOADED((char *)cutsceneNames[i]))
		{
			m_loadedCutsceneId = i;
			found = true;
			break;
		}
	}
	if (!found)
		m_loadedCutsceneId = -1;
}

void CutsceneMod::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Cutscene"))
		{
			if (ImGui::BeginMenu("Request"))
			{
				ImGui::InputInt("Id", &m_cutsceneId);

				ImGuiExtras::BitField("OR Flags", (unsigned *)&m_cutsceneId, nullptr);

				if (ImGui::BeginMenu("Name"))
				{
					for (int i = 0; i < IM_ARRAYSIZE(cutsceneNames); i++)
					{
						if (ImGui::MenuItem(cutsceneNames[i]))
						{
							m_dllObject.RunOnNativeThread([=]
							{
								CUTSCENE::REQUEST_CUTSCENE((char *)cutsceneNames[i], m_cutsceneId);
							});
						}
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Unload"))
			{
				m_dllObject.RunOnNativeThread([]
				{
					CUTSCENE::REMOVE_CUTSCENE();
				});
			}

			if (ImGui::BeginMenu("Set cutscene owner"))
			{
				ImGui::InputInt("Thread ID", &m_threadId);
				// Should Check the min/max IDs from thread list
				ClipInt(m_threadId, 0, 1000);
				if (ImGui::Button("Set"))
				{
					m_dllObject.RunOnNativeThread([=]
					{
						CUTSCENE::_0x8D9DF6ECA8768583(m_threadId);
					});
				}
				ImGui::EndMenu();
			}

			ImGui::Separator();

			if (ImGui::BeginMenu("Start"))
			{
				ImGuiExtras::BitField("Flags##StartCutscene", &m_cutsceneStartFlags, nullptr);

				if (ImGui::MenuItem("Start##CutsceneStart"))
				{
					m_dllObject.RunOnNativeThread([=]
					{
						CUTSCENE::START_CUTSCENE(m_cutsceneStartFlags);
					});
				}

				if (ImGui::BeginMenu("At Position"))
				{
					ImGuiExtras::InputVector3("CutsceneStartPosition", &m_startPos);
					if (ImGui::Button("Set to current position"))
					{
						m_dllObject.RunOnNativeThread([=]
						{
							m_startPos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
						});
					}

					if (ImGui::Button("Start##CutsceneStartAtPosition"))
					{
						m_dllObject.RunOnNativeThread([=]
						{
							CUTSCENE::START_CUTSCENE_AT_COORDS(m_startPos.x, m_startPos.y, m_startPos.z, m_cutsceneStartFlags);
						});
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Stop"))
			{
				if (ImGui::MenuItem("Stop##StopCutsceneDefault"))
				{
					m_dllObject.RunOnNativeThread([]
					{
						CUTSCENE::STOP_CUTSCENE(TRUE);
					});
				}

				if (ImGui::MenuItem("Stop Immediately"))
				{
					m_dllObject.RunOnNativeThread([]
					{
						CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
					});
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Set variable on audio"))
			{
				ImGui::InputText("Name", m_audioVariableName, sizeof(m_audioVariableName));
				ImGui::InputFloat("Value", &m_audioVariableValue);
				if (ImGui::MenuItem("Set"))
				{
					m_dllObject.RunOnNativeThread([=]
					{
						AUDIO::_SET_VARIABLE_ON_CUTSCENE_AUDIO(m_audioVariableName, m_audioVariableValue);
					});
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Unk function"))
			{
				ImGui::InputInt("Param0", &m_param0);
				ImGui::InputInt("Param1", &m_param1);
				if (ImGui::MenuItem("Run"))
				{
					m_dllObject.RunOnNativeThread([=]
					{
						CUTSCENE::_0x20746F7B1032A3C7(m_param0, m_param1, true, false);
					});
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

bool CutsceneMod::Draw()
{
	ImGui::SetWindowFontScale(m_settings.common.menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_settings.common.contentFontSize);

	if (m_loadedCutsceneId != -1)
		ImGui::Text("Loaded Cutscene Name: %s", cutsceneNames[m_loadedCutsceneId]);
	else
		ImGui::Text("Loaded Cutscene Name: None loaded.");
	ImGui::Text("Has Loaded: %d", m_hasCutsceneLoaded);
	ImGui::Text("Has Finished: %d", m_hasCutsceneFinished);
	ImGui::Text("Was Skipped: %d", m_wasCutsceneSkipped);
	ImGui::Text("Is Playing: %d", m_isCutscenePlaying);
	ImGui::Text("Is Active: %d", m_isCutsceneActive);
	ImGui::Text("Time: %d", m_cutsceneTime);
	ImGui::Text("Duration: %d", m_cutsceneTotalDuration);
	ImGui::Text("Section: %d", m_cutsceneSectionPlaying);

	ImGui::Separator();
	ImGui::Text("Can request assets: %d", m_canRequestAssetsForCutsceneEntity);
	ImGui::Text("Has cutscene cut this frame: %d", m_hasCutsceneCutThisFrame);

	return true;
}