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
	if (m_constantUpdate || m_wantsUpdate)
	{
		ListPeds();
		ListVehs();

		if (ENTITY::DOES_ENTITY_EXIST(m_handleInput))
			UpdateHandleData();
		else
			ResetData();

		m_wantsUpdate = false;
	}
}

void HandleHelperMod::ResetData()
{
	m_modelHash = 0;
	m_type = 0;
	m_health = 0;
	m_maxHealth = 0;
	m_injured = false;
	m_position = { 0, 0, 0 };
	m_isMissionEntity = false;
}

void HandleHelperMod::ListPeds()
{
	nearbyEnts pedArr;
	int ped = PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID());
	int maxCount = PED::GET_PED_NEARBY_PEDS(ped, (int*)&pedArr, ped);
	int count = std::min<int>(maxCount, m_nearbyObjectMax);

	// Go through peds
	m_pedListMutex.lock();
	m_pedList = std::to_string(count) + ": ";
	for (int i = 0; i < count; i++)
		m_pedList += std::to_string(pedArr.entities[i].id) + ", ";
	m_pedListMutex.unlock();

	if (m_drawEntityInfo && m_showInGame)
	{
		for (int i = 0; i < count; i++)
		{
			Vector3 worldPos = ENTITY::GET_ENTITY_COORDS(pedArr.entities[i].id, true);
			float screenX, screenY;
			bool notOnScreen = HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(worldPos.x, worldPos.y, worldPos.z + m_drawOffsetZ,
				&screenX, &screenY);
			if (!m_drawOnScreenEntityOnly || !notOnScreen)
			{
				char buf[256] = "";
				int health = ENTITY::GET_ENTITY_HEALTH(pedArr.entities[i].id);
				int maxHealth = ENTITY::GET_ENTITY_MAX_HEALTH(pedArr.entities[i].id);

				if (m_drawId && m_drawLife)
					sprintf_s(buf, "Ped ID: %d\nLife: %d/%d", pedArr.entities[i].id, health, maxHealth);
				else if (m_drawId)
					sprintf_s(buf, "Ped: %d", pedArr.entities[i].id);
				else if (m_drawLife)
					sprintf_s(buf, "Ped: %d/%d", health, maxHealth);

				DrawTextToScreen(buf, screenX, screenY, m_inGameFontSize, eFont::FontChaletLondon);
			}
		}
	}
}

void HandleHelperMod::ListVehs()
{
	nearbyEnts vehArr;
	int ped = PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID());
	int maxCount = PED::GET_PED_NEARBY_VEHICLES(ped, (int*)&vehArr);
	int count = std::min<int>(maxCount, m_nearbyObjectMax);

	// Go through vehicles
	m_vehListMutex.lock();
	m_vehList = std::to_string(count) + ": ";
	for (int i = 0; i < count; i++)
		m_vehList += std::to_string(vehArr.entities[i].id) + ", ";
	m_vehListMutex.unlock();

	if (m_drawEntityInfo && m_showInGame)
	{
		for (int i = 0; i < count; i++)
		{
			Vector3 worldPos = ENTITY::GET_ENTITY_COORDS(vehArr.entities[i].id, true);
			float screenX, screenY;
			bool notOnScreen = HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(worldPos.x, worldPos.y, worldPos.z + m_drawOffsetZ,
				&screenX, &screenY);
			if (!m_drawOnScreenEntityOnly || !notOnScreen)
			{
				char buf[256] = "";
				int health = ENTITY::GET_ENTITY_HEALTH(vehArr.entities[i].id);
				int maxHealth = ENTITY::GET_ENTITY_MAX_HEALTH(vehArr.entities[i].id);

				if (m_drawId && m_drawLife)
					sprintf_s(buf, "\n\nVeh ID: %d\nLife: %d/%d", vehArr.entities[i].id, health, maxHealth);
				else if (m_drawId)
					sprintf_s(buf, "\n\nVeh: %d", vehArr.entities[i].id);
				else if (m_drawLife)
					sprintf_s(buf, "\n\nVeh: %d/%d", health, maxHealth);

				DrawTextToScreen(buf, screenX, screenY, m_inGameFontSize, eFont::FontChaletLondon);
			}
		}
	}
}

void HandleHelperMod::UpdateHandleData()
{
	m_modelHash = ENTITY::GET_ENTITY_MODEL(m_handleInput);
	m_type = ENTITY::GET_ENTITY_TYPE(m_handleInput);
	m_health = ENTITY::GET_ENTITY_HEALTH(m_handleInput);
	m_maxHealth = ENTITY::GET_ENTITY_MAX_HEALTH(m_handleInput);
	m_injured = PED::IS_PED_INJURED(m_handleInput);
	m_position = ENTITY::GET_ENTITY_COORDS(m_handleInput, TRUE);
	m_isMissionEntity = ENTITY::IS_ENTITY_A_MISSION_ENTITY(m_handleInput);
}

void HandleHelperMod::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Entity"))
		{
			if (ImGui::BeginMenu("Persistence"))
			{
				if (ImGui::MenuItem("Set Mission Entity"))
				{
					RunOnNativeThread([=]
					{
						if (ENTITY::DOES_ENTITY_EXIST(m_handleInput))
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(m_handleInput, true, false);
					});
				}

				if (ImGui::MenuItem("Mark as No Longer Needed"))
				{
					RunOnNativeThread([=]
					{
						if (ENTITY::DOES_ENTITY_EXIST(m_handleInput))
						{
							int tempHandle = m_handleInput;
							ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&tempHandle);
						}
					});
				}

				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Kill"))
			{
				RunOnNativeThread([=]
				{
					if (ENTITY::DOES_ENTITY_EXIST(m_handleInput))
						ENTITY::SET_ENTITY_HEALTH(m_handleInput, 0, true);
				});
			}

			if (ImGui::MenuItem("Delete"))
			{
				RunOnNativeThread([=]
				{
					if (ENTITY::DOES_ENTITY_EXIST(m_handleInput))
						ENTITY::DELETE_ENTITY(&m_handleInput);
				});
			}

			if (ImGui::BeginMenu("Animation"))
			{
				if (ImGui::BeginMenu("Play"))
				{
					ImGui::InputText("Anim Dict", m_animDictInput, sizeof(m_animDictInput));
					ImGui::InputText("Anim Name", m_animNameInput, sizeof(m_animNameInput));
					ImGuiExtras::BitField("Flags", &m_animFlags, nullptr);
					if (ImGui::Button("Play"))
					{
						RunOnNativeThread([=]
						{
							if (ENTITY::DOES_ENTITY_EXIST(m_handleInput))
							{
								AnimDict dict(m_animDictInput);
								if (dict.IsValid())
									TASK::TASK_PLAY_ANIM(m_handleInput, m_animDictInput, m_animNameInput, 8.0f, 1.0f, -1, m_animFlags, 1.0f, FALSE, FALSE, FALSE);
							}
						});
					}
					ImGui::EndMenu();
				}

				if (ImGui::MenuItem("Stop"))
				{
					RunOnNativeThread([=]
					{
						if (ENTITY::DOES_ENTITY_EXIST(m_handleInput))
							TASK::STOP_ANIM_PLAYBACK(m_handleInput, 0, 0);
					});
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("HUD"))
		{
			ImGui::MenuItem("Show entities on scren only", NULL, &m_drawOnScreenEntityOnly);
			ImGui::MenuItem("Show on HUD", NULL, &m_drawEntityInfo);
			ImGui::MenuItem("Show Handle", NULL, &m_drawId);
			ImGui::MenuItem("Show Life", NULL, &m_drawLife);


			if (ImGui::BeginMenu("Misc"))
			{
				ImGui::InputInt("Max display count", &m_nearbyObjectMax);
				ImGui::InputInt("Z offset", &m_drawOffsetZ);
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

	ImGui::Checkbox("Constant Updates?", &m_constantUpdate);
	if (!m_constantUpdate)
		if (ImGui::Button("Update"))
			m_wantsUpdate = true;

	ImGui::Separator();
	if (ImGui::TreeNode("Entity"))
	{
		if (ImGui::InputInt("Handle", &m_handleInput))
		{
			if (m_handleInput < 0)
				m_handleInput = 0;
			m_wantsUpdate = true;
		}

		ImGui::Text("Entity Type: %s (%d)", entityTypes[m_type], m_type);
		ImGui::Text("Health: %d / %d", m_health, m_maxHealth);
		ImGui::Text("Injured: %d", m_injured);
		ImGui::Text("Model: %u (0x%x)", m_modelHash, m_modelHash);
		ImGui::Text("Position: %.2f, %.2f, %.2f", m_position.x, m_position.y, m_position.z);
		ImGui::Text("Is Mission Entity: %d", m_isMissionEntity);
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