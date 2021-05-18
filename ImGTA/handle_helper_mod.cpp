#include "handle_helper_mod.h"
#include "natives.h"
#include "script.h"
#include "anim_dict.h"
#include "imgui_extras.h"
#include "utils.h"

#include <algorithm>

const char *entityTypes[] = { "Invalid", "Ped", "Vehicle", "Object" };

void HandleHelperMod::Load()
{

}

void HandleHelperMod::Unload()
{

}

void HandleHelperMod::Think()
{
    if ( ( m_bConstantUpdate || m_bWantsUpdate ) )
    {
		ListPeds();
		ListVehs();
		if (ENTITY::DOES_ENTITY_EXIST(m_iHandleInput)) {
			UpdateHandleData( m_bWantsUpdate );
		}
		else {
			ResetData();
		}
		m_bWantsUpdate = false;
    }
}

void HandleHelperMod::ResetData() {
	m_modelHash = 0;
	m_iType = 0;
	m_iHealth = 0;
	m_iMaxHealth = 0;
	m_bInjured = false;
	m_position = { 0, 0, 0 };
	m_bIsMissionEntity = false;
}

struct PaddedEntity {
	DWORD _padding;
	int id;
};

const int maxCount = 100;
struct nearbyEnts {
	int size = maxCount;
	PaddedEntity entities[maxCount] = { 0, 0 };
};

void HandleHelperMod::ListPeds() {
	nearbyEnts pedArr;
	int ped = PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID());
	int maxCount = PED::GET_PED_NEARBY_PEDS(ped, (int*)&pedArr, ped);
	int count = std::min<int>(maxCount, m_iNearbyObjectMax);

	// Go through peds
	m_pedListMutex.lock();
	m_pedList = std::to_string(count) + ": ";
	for (int i = 0; i < count; i++) {
		m_pedList += std::to_string(pedArr.entities[i].id) + ", ";
	}
	m_pedListMutex.unlock();

	if (m_drawEntityInfo && m_showInGame) {
		for (int i = 0; i < count; i++) {
			Vector3 worldPos = ENTITY::GET_ENTITY_COORDS(pedArr.entities[i].id, true);
			float screenX, screenY;
			bool retVal = HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(worldPos.x, worldPos.y, worldPos.z + m_iDrawOffsetZ,
																			&screenX, &screenY);
			char buf[256] = "";
			int health = ENTITY::GET_ENTITY_HEALTH(pedArr.entities[i].id);
			int maxHealth = ENTITY::GET_ENTITY_MAX_HEALTH(pedArr.entities[i].id);
			if (m_bDrawID && m_bDrawLife) {
				sprintf_s(buf, "Ped ID: %d\nLife: %d/%d",
					pedArr.entities[i].id, health, maxHealth);
			}
			else if (m_bDrawID) {
				sprintf_s(buf, "Ped: %d",
					pedArr.entities[i].id);
			}
			else if (m_bDrawLife) {
				sprintf_s(buf, "Ped: %d/%d",
					health, maxHealth);
			}
			
			DrawTextToScreen(buf, screenX, screenY, m_inGameFontSize, eFont::FontChaletLondon);
		}
	}
}

void HandleHelperMod::ListVehs() {
	nearbyEnts vehArr;
	int ped = PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID());
	int maxCount = PED::GET_PED_NEARBY_VEHICLES(ped, (int*)&vehArr);
	int count = std::min<int>(maxCount, m_iNearbyObjectMax);
	
	// Go through vehicles
	m_vehListMutex.lock();
	m_vehList = std::to_string(count) + ": ";
	for (int i = 0; i < count; i++) {
		m_vehList += std::to_string(vehArr.entities[i].id) + ", ";
	}
	m_vehListMutex.unlock();

	if (m_drawEntityInfo && m_showInGame) {
		for (int i = 0; i < count; i++) {
			Vector3 worldPos = ENTITY::GET_ENTITY_COORDS(vehArr.entities[i].id, true);
			float screenX, screenY;
			HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(worldPos.x, worldPos.y, worldPos.z + m_iDrawOffsetZ,
																&screenX, &screenY);
			char buf[256] = "";
			int health = ENTITY::GET_ENTITY_HEALTH(vehArr.entities[i].id);
			int maxHealth = ENTITY::GET_ENTITY_MAX_HEALTH(vehArr.entities[i].id);
			if (m_bDrawID && m_bDrawLife) {
				sprintf_s(buf, "\n\nVeh ID: %d\nLife: %d/%d",
					vehArr.entities[i].id, health, maxHealth);
			}
			else if (m_bDrawID) {
				sprintf_s(buf, "\n\nVeh: %d",
					vehArr.entities[i].id);
			}
			else if (m_bDrawLife) {
				sprintf_s(buf, "\n\nVeh: %d/%d",
					health, maxHealth);
			}
			DrawTextToScreen(buf, screenX, screenY, m_inGameFontSize, eFont::FontChaletLondon);
		}
	}
}

void HandleHelperMod::UpdateHandleData( bool once )
{
    if ( once )
        m_modelHash = ENTITY::GET_ENTITY_MODEL( m_iHandleInput );

    m_iType = ENTITY::GET_ENTITY_TYPE( m_iHandleInput );
    m_iHealth = ENTITY::GET_ENTITY_HEALTH( m_iHandleInput );
    m_iMaxHealth = ENTITY::GET_ENTITY_MAX_HEALTH( m_iHandleInput );
	m_bInjured = PED::IS_PED_INJURED(m_iHandleInput);
    m_position = ENTITY::GET_ENTITY_COORDS( m_iHandleInput, TRUE );
    m_bIsMissionEntity = ENTITY::IS_ENTITY_A_MISSION_ENTITY( m_iHandleInput );
}

void HandleHelperMod::DrawMenuBar()
{
    if ( ImGui::BeginMenuBar() )
    {
        if ( ImGui::BeginMenu( "Entity" ) )
        {
            if ( ImGui::BeginMenu( "Persistence" ) )
            {
                if ( ImGui::MenuItem( "Set Mission Entity" ) )
                {
                    RunOnNativeThread( [ = ]
                    {
                        if ( ENTITY::DOES_ENTITY_EXIST( m_iHandleInput ) )
                            ENTITY::SET_ENTITY_AS_MISSION_ENTITY( m_iHandleInput, true, false );
                    } );
                }

                if ( ImGui::MenuItem( "Mark as No Longer Needed" ) )
                {
                    RunOnNativeThread( [ = ]
                    {
                        if ( ENTITY::DOES_ENTITY_EXIST( m_iHandleInput ) )
                        {
                            int tempHandle = m_iHandleInput;
                            ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED( &tempHandle );
                        }
                    } );
                }

                ImGui::EndMenu();
            }

            if ( ImGui::MenuItem( "Kill" ) )
            {
                RunOnNativeThread( [ = ]
                {
                    if ( ENTITY::DOES_ENTITY_EXIST( m_iHandleInput ) )
                        ENTITY::SET_ENTITY_HEALTH( m_iHandleInput, 0, true);
                } );
            }

            if ( ImGui::MenuItem( "Delete" ) )
            {
                RunOnNativeThread( [ = ]
                {
                    if ( ENTITY::DOES_ENTITY_EXIST( m_iHandleInput ) )
                        ENTITY::DELETE_ENTITY( &m_iHandleInput );
                } );
            }

            if ( ImGui::BeginMenu( "Animation" ) )
            {
                if ( ImGui::BeginMenu( "Play" ) )
                {
                    ImGui::InputText( "Anim Dict", m_szAnimDictInput, sizeof( m_szAnimDictInput ) );
                    ImGui::InputText( "Anim Name", m_szAnimNameInput, sizeof( m_szAnimNameInput ) );
                    ImGuiExtras::BitField( "Flags", &m_iAnimFlags, nullptr );
                    if ( ImGui::Button( "Play" ) )
                    {
                        RunOnNativeThread( [ = ]
                        {
                            if ( ENTITY::DOES_ENTITY_EXIST( m_iHandleInput ) )
                            {
                                AnimDict dict( m_szAnimDictInput );
                                if ( dict.IsValid() )
                                    TASK::TASK_PLAY_ANIM( m_iHandleInput, m_szAnimDictInput, m_szAnimNameInput, 8.0f, 1.0f, -1, m_iAnimFlags, 1.0f, FALSE, FALSE, FALSE );
                            }
                        } );
                    }
                    ImGui::EndMenu();
                }

                if ( ImGui::MenuItem( "Stop" ) )
                {
                    RunOnNativeThread( [ = ]
                    {
                        if ( ENTITY::DOES_ENTITY_EXIST( m_iHandleInput ) )
                            TASK::STOP_ANIM_PLAYBACK( m_iHandleInput, 0, 0 );
                    } );
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }
        
		if (ImGui::BeginMenu("HUD")) {
			ImGui::MenuItem("Show on HUD", NULL, &m_drawEntityInfo);
			ImGui::MenuItem("Show Handle", NULL, &m_bDrawID);
			ImGui::MenuItem("Show Life", NULL, &m_bDrawLife);

			
			if (ImGui::BeginMenu("Misc"))
			{
				ImGui::InputInt("Max display count", &m_iNearbyObjectMax);
				ImGui::InputInt("Z offset", &m_iDrawOffsetZ);
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
    }
}

bool HandleHelperMod::Draw()
{
	ImGui::SetWindowFontScale(m_menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_contentFontSize);

    ImGui::Checkbox( "Constant Updates?", &m_bConstantUpdate );
    if ( !m_bConstantUpdate )
        if ( ImGui::Button( "Update" ) )
            m_bWantsUpdate = true;

    ImGui::Separator();
	if (ImGui::TreeNode("Entity"))
	{
		if (ImGui::InputInt("Handle", &m_iHandleInput)) {
			if (m_iHandleInput < 0)
				m_iHandleInput = 0;
			m_bWantsUpdate = true;
		}

		ImGui::Text("Entity Type: %s (%d)", entityTypes[m_iType], m_iType);
		ImGui::Text("Health: %d / %d", m_iHealth, m_iMaxHealth);
		ImGui::Text("Injured: %d", m_bInjured);
		ImGui::Text("Model: %u (0x%x)", m_modelHash, m_modelHash);
		ImGui::Text("Position: %.2f, %.2f, %.2f", m_position.x, m_position.y, m_position.z);
		ImGui::Text("Is Mission Entity: %d", m_bIsMissionEntity);
		ImGui::TreePop();
	}

	ImGui::Separator();
	m_pedListMutex.lock();
	ImGui::Text("Nearby Ped list: %s", m_pedList.c_str());
	m_pedListMutex.unlock();
	m_vehListMutex.lock();
	ImGui::Text("Nearby Vehicles list: %s", m_vehList.c_str());
	m_vehListMutex.unlock();
    return true;
}