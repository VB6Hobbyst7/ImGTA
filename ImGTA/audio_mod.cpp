#include "audio_mod.h"
#include "natives.h"
#include "script.h"
#include "audio_scenes.h"
#include "music_events.h"


void AudioMod::Load()
{

}

void AudioMod::Unload()
{

}

void AudioMod::Think()
{
    Ped p = PLAYER::PLAYER_PED_ID();

    m_bIsRingtonePlaying = AUDIO::IS_PED_RINGTONE_PLAYING( p );
    m_bIsCallOngoing = AUDIO::IS_MOBILE_PHONE_CALL_ONGOING();

    m_bIsScriptedConversationLoaded = AUDIO::IS_SCRIPTED_CONVERSATION_LOADED();
    m_bIsScriptedConversationOngoing = AUDIO::IS_SCRIPTED_CONVERSATION_ONGOING();
    m_bIsInCurrentConversation = AUDIO::IS_PED_IN_CURRENT_CONVERSATION( p );
    m_iCurrentScriptedConversationLine = AUDIO::GET_CURRENT_SCRIPTED_CONVERSATION_LINE();

    m_bIsStreamPlaying = AUDIO::IS_STREAM_PLAYING();
    m_iStreamPlayTime = AUDIO::GET_STREAM_PLAY_TIME();

    m_bIsScriptedMusicPlaying = AUDIO::AUDIO_IS_SCRIPTED_MUSIC_PLAYING();

    m_bIsAmbientSpeechPlaying = AUDIO::IS_AMBIENT_SPEECH_PLAYING( p );
    m_bIsScriptedSpeechPlaying = AUDIO::IS_SCRIPTED_SPEECH_PLAYING( p );
    m_bIsAnySpeechPlaying = AUDIO::IS_ANY_SPEECH_PLAYING( p );

	m_audioName = std::string((char *) getGlobalPtr(0x3BCF));
	m_audioSource = std::string((char *) getGlobalPtr(0x3D92));
	m_audio1 = std::string((char *) getGlobalPtr(0x4138));
	m_audio2 = std::string((char *) getGlobalPtr(0x3B2A));
}

void AudioMod::DrawMenuBar()
{
    if ( ImGui::BeginMenuBar() )
    {
		if (ImGui::BeginMenu("Conversation"))
		{
			if (ImGui::MenuItem("Restart"))
			{
				RunOnNativeThread([]
				{
					AUDIO::RESTART_SCRIPTED_CONVERSATION();
				});
			}

			if (ImGui::BeginMenu("Stop"))
			{
				ImGui::Checkbox("Unknown param", &m_bStopConversationParam);
				if (ImGui::Button("Stop"))
				{
					RunOnNativeThread([=]
					{
						AUDIO::STOP_SCRIPTED_CONVERSATION(m_bStopConversationParam);
					});
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Pause"))
			{
				ImGui::Checkbox("Finish Current Line", &m_bPauseConversationParam);

				if (ImGui::Button("Pause"))
				{
					RunOnNativeThread([=]
					{
						AUDIO::PAUSE_SCRIPTED_CONVERSATION(m_bPauseConversationParam);
					});
				}

				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Skip to Next Line"))
			{
				RunOnNativeThread([=]
				{
					AUDIO::SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE();
				});
			}

			if (ImGui::MenuItem("Start Preloaded Conversation"))
			{
				RunOnNativeThread([=]
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
				for (int i = 0; i < IM_ARRAYSIZE(audio_scenes); i++)
				{
					if (ImGui::MenuItem(audio_scenes[i]))
					{
						RunOnNativeThread([=]
						{
							AUDIO::START_AUDIO_SCENE((char *)audio_scenes[i]);
						});
					}
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Set Variable"))
			{
				ImGui::InputText("Name", m_audioSceneVarName, sizeof( m_audioSceneVarName ));
				ImGui::InputFloat("Value", &m_audioSceneVarValue);
				if (ImGui::BeginMenu("Scene name"))
				{
					for (int i = 0; i < IM_ARRAYSIZE(audio_scenes); i++)
					{
						if (ImGui::MenuItem(audio_scenes[i]))
						{
							RunOnNativeThread([=]
							{
								AUDIO::SET_AUDIO_SCENE_VARIABLE((char *)audio_scenes[i], m_audioSceneVarName, m_audioSceneVarValue);
							});
						}
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Stop"))
			{
				for (int i = 0; i < IM_ARRAYSIZE(audio_scenes); i++)
				{
					if (ImGui::MenuItem(audio_scenes[i]))
					{
						RunOnNativeThread([=]
						{
							if (AUDIO::IS_AUDIO_SCENE_ACTIVE((char *)audio_scenes[i]))
								AUDIO::STOP_AUDIO_SCENE((char *)audio_scenes[i]);
						});
					}
				}
				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Stop all"))
			{
				RunOnNativeThread([]
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
				for (int i = 0; i < IM_ARRAYSIZE(music_events); i++)
				{
					if (ImGui::MenuItem(music_events[i]))
					{
						RunOnNativeThread([=]
						{
							AUDIO::PREPARE_MUSIC_EVENT((char *)music_events[i]);
						});
					}
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Trigger"))
			{
				for (int i = 0; i < IM_ARRAYSIZE(music_events); i++)
				{
					if (ImGui::MenuItem(music_events[i]))
					{
						RunOnNativeThread([=]
						{
							AUDIO::TRIGGER_MUSIC_EVENT((char *)music_events[i]);
						});
					}
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Cancel"))
			{
				for (int i = 0; i < IM_ARRAYSIZE(music_events); i++)
				{
					if (ImGui::MenuItem(music_events[i]))
					{
						RunOnNativeThread([=]
						{
							AUDIO::CANCEL_MUSIC_EVENT((char *)music_events[i]);
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
	ImGui::SetWindowFontScale(m_menuFontSize);
    DrawMenuBar();

	ImGui::SetWindowFontScale(m_contentFontSize);
    ImGui::Text( "Is Phone Ringing: %d", m_bIsRingtonePlaying );
    ImGui::Text( "Is Call Ongoing: %d", m_bIsCallOngoing );
    ImGui::Separator();
    ImGui::Text( "Is Scripted Conversation Loaded: %d", m_bIsScriptedConversationLoaded );
    ImGui::Text( "Is Scripted Conversation Ongoing: %d", m_bIsScriptedConversationOngoing );
    ImGui::Text( "Is In Current Conversation: %d", m_bIsInCurrentConversation );
    ImGui::Text( "Current Conversation Line: %d", m_iCurrentScriptedConversationLine );
    ImGui::Separator();
    ImGui::Text( "Is Stream Playing: %d", m_bIsStreamPlaying );
    ImGui::Text( "Stream Play Time: %d", m_iStreamPlayTime );
    ImGui::Separator();
    ImGui::Text( "Is Scripted Music Playing: %d", m_bIsScriptedMusicPlaying );
    ImGui::Separator();
    ImGui::Text( "Is Ambient Speech Playing: %d", m_bIsAmbientSpeechPlaying );
    ImGui::Text( "Is Scripted Speech Playing: %d", m_bIsScriptedSpeechPlaying );
    ImGui::Text( "Is Any Speech Playing: %d", m_bIsAnySpeechPlaying );

	ImGui::Separator();
	ImGui::Text("Name: %s", m_audioName.c_str());
	ImGui::Text("Source: %s", m_audioSource.c_str());
	ImGui::Text("Unknown 1: %s", m_audio1.c_str());
	ImGui::Text("Unknown 2: %s", m_audio2.c_str());
    return true;
}