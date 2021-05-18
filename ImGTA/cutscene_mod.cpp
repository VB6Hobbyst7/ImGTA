#include "cutscene_mod.h"
#include "natives.h"
#include "script.h"
#include "imgui_extras.h"
#include "cutscene_names.h"

#include <mutex>
#include <condition_variable>

void CutsceneMod::Load()
{

}

void CutsceneMod::Unload()
{

}

void CutsceneMod::Think()
{
    m_bHasCutsceneLoaded = CUTSCENE::HAS_CUTSCENE_LOADED();
    m_bHasCutsceneFinished = CUTSCENE::HAS_CUTSCENE_FINISHED();
	m_bWasCutsceneSkipped = CUTSCENE::WAS_CUTSCENE_SKIPPED();
    m_bIsCutscenePlaying = CUTSCENE::IS_CUTSCENE_PLAYING();
    m_bIsCutsceneActive = CUTSCENE::IS_CUTSCENE_ACTIVE();

    m_iCutsceneTime = CUTSCENE::GET_CUTSCENE_TIME();
    m_iCutsceneTotalDuration = CUTSCENE::GET_CUTSCENE_TOTAL_DURATION();
    m_iCutsceneSectionPlaying = CUTSCENE::GET_CUTSCENE_SECTION_PLAYING();

	m_bCanRequestAssetsForCutsceneEntity = CUTSCENE::CAN_REQUEST_ASSETS_FOR_CUTSCENE_ENTITY(); // CAN_REQUEST_ASSETS_FOR_CUTSCENE_ENTITY
	m_bHasCutsceneCutThisFrame = CUTSCENE::_HAS_CUTSCENE_CUT_THIS_FRAME(); // HAS_CUTSCENE_CUT_THIS_FRAME
}

void CutsceneMod::DrawMenuBar()
{
    if ( ImGui::BeginMenuBar() )
    {
        if ( ImGui::BeginMenu( "Cutscene" ) )
        {
			if (ImGui::BeginMenu("Request"))
			{
				ImGui::InputInt("Id", &m_iCutsceneId);

				ImGuiExtras::BitField("OR Flags", (unsigned *) &m_iCutsceneId, nullptr);

				if (ImGui::BeginMenu("Name"))
				{
					for (int i = 0; i < IM_ARRAYSIZE(cutscene_names); i++)
					{
						if (ImGui::MenuItem(cutscene_names[i]))
						{
							RunOnNativeThread([ = ]
							{
								CUTSCENE::REQUEST_CUTSCENE((char *) cutscene_names[i], m_iCutsceneId);
							});
						}
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Loaded Cutscene"))
			{
				RunOnNativeThread([ = ]
				{
					bool found = false;
					for (int i = 0; i < IM_ARRAYSIZE(cutscene_names); i++)
					{
						// There should only be one loaded cutscene maximum
						if (CUTSCENE::HAS_THIS_CUTSCENE_LOADED((char *)cutscene_names[i])) {
							m_loaded_cutscene_id = i;
							found = true;
						}
					}
					if (!found)
						m_loaded_cutscene_id = -1;
				});
				if (m_loaded_cutscene_id != -1)
					ImGui::Text(cutscene_names[m_loaded_cutscene_id]);
				else
					ImGui::Text("None loaded.");
				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Unload"))
			{
				RunOnNativeThread([]
				{
					CUTSCENE::REMOVE_CUTSCENE();
				});
			}
			
			ImGui::Separator();

            if ( ImGui::BeginMenu( "Start" ) )
            {
                ImGuiExtras::BitField( "Flags##StartCutscene", &m_iCutsceneStartFlags, nullptr );

                if ( ImGui::MenuItem( "Start##CutsceneStart" ) )
                {
                    RunOnNativeThread( [ = ]
                    {
                        CUTSCENE::START_CUTSCENE( m_iCutsceneStartFlags );
                    } );
                }

                if ( ImGui::BeginMenu( "At Position" ) )
                {
                    ImGuiExtras::InputVector3( "CutsceneStartPosition", &m_startPos );
                    if ( ImGui::Button( "Set to current position" ) )
                    {
                        RunOnNativeThread( [ = ]
                        {
                            m_startPos = ENTITY::GET_ENTITY_COORDS( PLAYER::PLAYER_PED_ID(), TRUE );
                        } );
                    }

                    if ( ImGui::Button( "Start##CutsceneStartAtPosition" ) )
                    {
                        RunOnNativeThread( [ = ]
                        {
                            CUTSCENE::START_CUTSCENE_AT_COORDS( m_startPos.x, m_startPos.y, m_startPos.z, m_iCutsceneStartFlags );
                        } );
                    }

                    ImGui::EndMenu();
                }

                ImGui::EndMenu();
            }

            if ( ImGui::BeginMenu( "Stop" ) )
            {
                if ( ImGui::MenuItem( "Stop##StopCutsceneDefault" ) )
                {
                    RunOnNativeThread( []
                    {
                        CUTSCENE::STOP_CUTSCENE( TRUE );
                    } );
                }

                if ( ImGui::MenuItem( "Stop Immediately" ) )
                {
                    RunOnNativeThread( []
                    {
                        CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
                    } );
                }

                ImGui::EndMenu();
            }

			if (ImGui::BeginMenu("Set variable on audio"))
			{
				ImGui::InputText("Name", m_audioVariableName, sizeof(m_audioVariableName));
				ImGui::InputFloat("Value", &m_audioVariableValue);
				if (ImGui::MenuItem("Set"))
				{
					RunOnNativeThread([=]
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
					RunOnNativeThread( [ = ]
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
	ImGui::SetWindowFontScale(m_menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_contentFontSize);
    ImGui::Text( "Has Loaded: %d", m_bHasCutsceneLoaded );
    ImGui::Text( "Has Finished: %d", m_bHasCutsceneFinished );
	ImGui::Text("Was Skipped: %d", m_bWasCutsceneSkipped);
    ImGui::Text( "Is Playing: %d", m_bIsCutscenePlaying );
    ImGui::Text( "Is Active: %d", m_bIsCutsceneActive );
    ImGui::Text( "Time: %d", m_iCutsceneTime );
    ImGui::Text( "Duration: %d", m_iCutsceneTotalDuration );
    ImGui::Text( "Section: %d", m_iCutsceneSectionPlaying );

	ImGui::Separator();
	ImGui::Text("Can request assets: %d", m_bCanRequestAssetsForCutsceneEntity);
	ImGui::Text("Has cutscene cut this frame: %d", m_bHasCutsceneCutThisFrame);

    return true;
}