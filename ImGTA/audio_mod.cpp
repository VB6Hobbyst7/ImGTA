/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "audio_mod.h"
#include "natives.h"
#include "script.h"
#include "audio_scenes.h"
#include "music_events.h"
#include "global_id.h"
#include "types.h"
#include "utils.h"


void AudioMod::Load()
{
	Mod::CommonLoad();
	m_settings = m_dllObject.GetUserSettings().audio;
}

void AudioMod::Unload()
{
	Mod::CommonUnload();
	m_dllObject.GetUserSettings().audio = m_settings;
}

void AudioMod::Think()
{
	Ped p = PLAYER::PLAYER_PED_ID();

	m_isRingtonePlaying = AUDIO::IS_PED_RINGTONE_PLAYING(p);
	m_isCallOngoing = AUDIO::IS_MOBILE_PHONE_CALL_ONGOING();

	m_isScriptedConversationLoaded = AUDIO::IS_SCRIPTED_CONVERSATION_LOADED();
	m_isScriptedConversationOngoing = AUDIO::IS_SCRIPTED_CONVERSATION_ONGOING();
	m_isInCurrentConversation = AUDIO::IS_PED_IN_CURRENT_CONVERSATION(p);
	m_currentScriptedConversationLine = AUDIO::GET_CURRENT_SCRIPTED_CONVERSATION_LINE();

	m_isStreamPlaying = AUDIO::IS_STREAM_PLAYING();
	m_streamPlayTime = AUDIO::GET_STREAM_PLAY_TIME();

	m_isScriptedMusicPlaying = AUDIO::AUDIO_IS_SCRIPTED_MUSIC_PLAYING();

	m_isAmbientSpeechPlaying = AUDIO::IS_AMBIENT_SPEECH_PLAYING(p);
	m_isScriptedSpeechPlaying = AUDIO::IS_SCRIPTED_SPEECH_PLAYING((Any)p);
	m_isAnySpeechPlaying = AUDIO::IS_ANY_SPEECH_PLAYING(p);

	if (m_supportGlobals)
	{
		m_audioName = std::string((char *)GetGlobalPtr(GlobalID::_15311));
		m_audioSource = std::string((char *)GetGlobalPtr(GlobalID::_15762));
		m_audio1 = std::string((char *)GetGlobalPtr(GlobalID::_16696));
		m_audio2 = std::string((char *)GetGlobalPtr(GlobalID::_15146));
	}
}

void AudioMod::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Conversation"))
		{
			if (ImGui::MenuItem("Restart"))
			{
				m_dllObject.RunOnNativeThread([]
				{
					AUDIO::RESTART_SCRIPTED_CONVERSATION();
				});
			}

			if (ImGui::BeginMenu("Stop"))
			{
				ImGui::Checkbox("Unknown param", &m_stopConversationParam);
				if (ImGui::Button("Stop"))
				{
					m_dllObject.RunOnNativeThread([=]
					{
						AUDIO::STOP_SCRIPTED_CONVERSATION(m_stopConversationParam);
					});
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Pause"))
			{
				ImGui::Checkbox("Finish Current Line", &m_pauseConversationParam);

				if (ImGui::Button("Pause"))
				{
					m_dllObject.RunOnNativeThread([=]
					{
						AUDIO::PAUSE_SCRIPTED_CONVERSATION(m_pauseConversationParam);
					});
				}

				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Skip to Next Line"))
			{
				m_dllObject.RunOnNativeThread([=]
				{
					AUDIO::SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE();
				});
			}

			if (ImGui::MenuItem("Start Preloaded Conversation"))
			{
				m_dllObject.RunOnNativeThread([=]
				{
					AUDIO::START_PRELOADED_CONVERSATION();
				});
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Audio Scenes"))
		{
			if (ImGui::BeginMenu("Start"))
			{
				for (int i = 0; i < IM_ARRAYSIZE(audioScenes); i++)
				{
					if (ImGui::MenuItem(audioScenes[i]))
					{
						m_dllObject.RunOnNativeThread([=]
						{
							AUDIO::START_AUDIO_SCENE((char *)audioScenes[i]);
						});
					}
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Set Variable"))
			{
				ImGui::InputText("Name", m_audioSceneVarName, sizeof(m_audioSceneVarName));
				ImGui::InputFloat("Value", &m_audioSceneVarValue);
				if (ImGui::BeginMenu("Scene name"))
				{
					for (int i = 0; i < IM_ARRAYSIZE(audioScenes); i++)
					{
						if (ImGui::MenuItem(audioScenes[i]))
						{
							m_dllObject.RunOnNativeThread([=]
							{
								AUDIO::SET_AUDIO_SCENE_VARIABLE((char *)audioScenes[i], m_audioSceneVarName, m_audioSceneVarValue);
							});
						}
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Stop"))
			{
				for (int i = 0; i < IM_ARRAYSIZE(audioScenes); i++)
				{
					if (ImGui::MenuItem(audioScenes[i]))
					{
						m_dllObject.RunOnNativeThread([=]
						{
							if (AUDIO::IS_AUDIO_SCENE_ACTIVE((char *)audioScenes[i]))
								AUDIO::STOP_AUDIO_SCENE((char *)audioScenes[i]);
						});
					}
				}
				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Stop all"))
			{
				m_dllObject.RunOnNativeThread([]
				{
					AUDIO::STOP_AUDIO_SCENES();
				});
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Music Events"))
		{
			if (ImGui::BeginMenu("Prepare"))
			{
				for (int i = 0; i < IM_ARRAYSIZE(musicEvents); i++)
				{
					if (ImGui::MenuItem(musicEvents[i]))
					{
						m_dllObject.RunOnNativeThread([=]
						{
							AUDIO::PREPARE_MUSIC_EVENT((char *)musicEvents[i]);
						});
					}
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Trigger"))
			{
				for (int i = 0; i < IM_ARRAYSIZE(musicEvents); i++)
				{
					if (ImGui::MenuItem(musicEvents[i]))
					{
						m_dllObject.RunOnNativeThread([=]
						{
							AUDIO::TRIGGER_MUSIC_EVENT((char *)musicEvents[i]);
						});
					}
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Cancel"))
			{
				for (int i = 0; i < IM_ARRAYSIZE(musicEvents); i++)
				{
					if (ImGui::MenuItem(musicEvents[i]))
					{
						m_dllObject.RunOnNativeThread([=]
						{
							AUDIO::CANCEL_MUSIC_EVENT((char *)musicEvents[i]);
						});
					}
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

bool AudioMod::Draw()
{
	ImGui::SetWindowFontScale(m_commonSettings.menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_commonSettings.contentFontSize);
	ImGui::Text("Is Phone Ringing: %d", m_isRingtonePlaying);
	ImGui::Text("Is Call Ongoing: %d", m_isCallOngoing);
	ImGui::Separator();
	ImGui::Text("Is Scripted Conversation Loaded: %d", m_isScriptedConversationLoaded);
	ImGui::Text("Is Scripted Conversation Ongoing: %d", m_isScriptedConversationOngoing);
	ImGui::Text("Is In Current Conversation: %d", m_isInCurrentConversation);
	ImGui::Text("Current Conversation Line: %d", m_currentScriptedConversationLine);
	ImGui::Separator();
	ImGui::Text("Is Stream Playing: %d", m_isStreamPlaying);
	ImGui::Text("Stream Play Time: %d", m_streamPlayTime);
	ImGui::Separator();
	ImGui::Text("Is Scripted Music Playing: %d", m_isScriptedMusicPlaying);
	ImGui::Separator();
	ImGui::Text("Is Ambient Speech Playing: %d", m_isAmbientSpeechPlaying);
	ImGui::Text("Is Scripted Speech Playing: %d", m_isScriptedSpeechPlaying);
	ImGui::Text("Is Any Speech Playing: %d", m_isAnySpeechPlaying);

	if (m_supportGlobals)
	{
		ImGui::Separator();
		ImGui::Text("Name: %s", m_audioName.c_str());
		ImGui::Text("Source: %s", m_audioSource.c_str());
		ImGui::Text("Unknown 1: %s", m_audio1.c_str());
		ImGui::Text("Unknown 2: %s", m_audio2.c_str());
	}
	return true;
}