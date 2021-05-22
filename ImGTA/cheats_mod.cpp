#include <sstream>
#include <iomanip>

#include "cheats_mod.h"
#include "natives.h"
#include "script.h"
#include "utils.h"
#include "imgui_extras.h"
#include "input_controls.h"
#include "model.h"

#pragma region Weapon Array
const char *weapons[] = { "weapon_dagger", "weapon_bat", "weapon_bottle", "weapon_crowbar", "weapon_unarmed", "weapon_flashlight", "weapon_golfclub", "weapon_hammer", "weapon_hatchet", "weapon_knuckle", "weapon_knife", "weapon_machete", "weapon_switchblade", "weapon_nightstick", "weapon_wrench", "weapon_battleaxe", "weapon_poolcue", "weapon_stone_hatchet", "weapon_pistol", "weapon_pistol_mk2", "weapon_combatpistol", "weapon_appistol", "weapon_stungun", "weapon_pistol50", "weapon_snspistol", "weapon_snspistol_mk2", "weapon_heavypistol", "weapon_vintagepistol", "weapon_flaregun", "weapon_marksmanpistol", "weapon_revolver", "weapon_revolver_mk2", "weapon_doubleaction", "weapon_raypistol", "weapon_ceramicpistol", "weapon_navyrevolver", "weapon_microsmg", "weapon_smg", "weapon_smg_mk2", "weapon_assaultsmg", "weapon_combatpdw", "weapon_machinepistol", "weapon_minismg", "weapon_raycarbine", "weapon_pumpshotgun", "weapon_pumpshotgun_mk2", "weapon_sawnoffshotgun", "weapon_assaultshotgun", "weapon_bullpupshotgun", "weapon_musket", "weapon_heavyshotgun", "weapon_dbshotgun", "weapon_autoshotgun", "weapon_assaultrifle", "weapon_assaultrifle_mk2", "weapon_carbinerifle", "weapon_carbinerifle_mk2", "weapon_advancedrifle", "weapon_specialcarbine", "weapon_specialcarbine_mk2", "weapon_bullpuprifle", "weapon_bullpuprifle_mk2", "weapon_compactrifle", "weapon_mg", "weapon_combatmg", "weapon_combatmg_mk2", "weapon_gusenberg", "weapon_sniperrifle", "weapon_heavysniper", "weapon_heavysniper_mk2", "weapon_marksmanrifle", "weapon_marksmanrifle_mk2", "weapon_rpg", "weapon_grenadelauncher", "weapon_grenadelauncher_smoke", "weapon_minigun", "weapon_firework", "weapon_railgun", "weapon_hominglauncher", "weapon_compactlauncher", "weapon_rayminigun", "weapon_grenade", "weapon_bzgas", "weapon_molotov", "weapon_stickybomb", "weapon_proxmine", "weapon_snowball", "weapon_pipebomb", "weapon_ball", "weapon_smokegrenade", "weapon_flare", "weapon_petrolcan", "gadget_parachute", "weapon_fireextinguisher", "weapon_hazardcan" };
#pragma endregion

void CheatsMod::Load()
{
	m_helper = new MissionHelper(getGameVersion());
}

void CheatsMod::Unload()
{

}

void CheatsMod::Think()
{
	int playerID = PLAYER::PLAYER_PED_ID();
	if (m_explosiveBullets)
		MISC::SET_EXPLOSIVE_AMMO_THIS_FRAME(playerID);

	if (m_showDebug && m_showInGame)
	{
		char buf[256] = "";
		std::ostringstream buffer;
		float startX = 0.155f;
		float startY = 0.75f;
		float step = 0.02f;
		float valueStep = 0.04f;
		eFont font = eFont::FontChaletLondon;
		std::string speedUnits = m_displayKMH ? "km/h" : "m/s";

		// TODO: Remove the manual tweaks here and there... It's unreadable

		// Position
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerID, TRUE);
		buffer << "Position (x, y, z): (";
		DrawTextToScreen(buffer.str().c_str(), startX, startY, m_inGameFontSize, font);
		buffer.str("");
		buffer.clear();
		buffer << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(8) << pos.x << ",";
		DrawTextToScreen(buffer.str().c_str(), startX + valueStep * 2.2f, startY, m_inGameFontSize, font);

		buffer.str("");
		buffer.clear();
		buffer << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(8) << pos.y << ", ";
		DrawTextToScreen(buffer.str().c_str(), startX + valueStep * 3.2f, startY, m_inGameFontSize, font);

		buffer.str("");
		buffer.clear();
		buffer << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(8) << pos.z << ")";
		DrawTextToScreen(buffer.str().c_str(), startX + valueStep * 4.2f, startY, m_inGameFontSize, font);

		startY += step;

		int health = ENTITY::GET_ENTITY_HEALTH(playerID);
		int maxHealth = ENTITY::GET_ENTITY_MAX_HEALTH(playerID);
		sprintf_s(buf, "Health: %d / %d", health, maxHealth);
		DrawTextToScreen(buf, startX, startY, m_inGameFontSize, font);
		startY += step;

		int armour = PED::GET_PED_ARMOUR(playerID);
		int maxArmour = PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_ID());
		sprintf_s(buf, "Armour: %d / %d", armour, maxArmour);
		DrawTextToScreen(buf, startX, startY, m_inGameFontSize, font);
		startY += step;

		float speed = ENTITY::GET_ENTITY_SPEED(playerID);
		if (m_displayKMH)
			speed *= 3.6f;
		buffer.str("");
		buffer.clear();
		buffer << std::fixed << std::setprecision(2) << "Speed: " << std::setfill(' ') << std::setw(7) << speed << std::setfill(' ') << std::setw(5) << speedUnits;
		DrawTextToScreen(buffer.str().c_str(), startX, startY, m_inGameFontSize, font);
		startY += step;

		Vector3 speed3;
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(playerID, FALSE);
		if (vehicle)
			speed3 = ENTITY::GET_ENTITY_SPEED_VECTOR(vehicle, TRUE);
		else
			speed3 = ENTITY::GET_ENTITY_SPEED_VECTOR(playerID, TRUE);
		if (m_displayKMH)
		{
			speed3.x *= 3.6f;
			speed3.y *= 3.6f;
			speed3.z *= 3.6f;
		}
		buffer.str("");
		buffer.clear();
		buffer << "Speed vector (x, y, z): (";
		DrawTextToScreen(buffer.str().c_str(), startX, startY, m_inGameFontSize, font);
		buffer.str("");
		buffer.clear();
		buffer << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(8) << speed3.x << ",";
		DrawTextToScreen(buffer.str().c_str(), startX + valueStep * 2.5f, startY, m_inGameFontSize, font);

		buffer.str("");
		buffer.clear();
		buffer << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(8) << speed3.y << ", ";
		DrawTextToScreen(buffer.str().c_str(), startX + valueStep * 3.5f, startY, m_inGameFontSize, font);

		buffer.str("");
		buffer.clear();
		buffer << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(8) << speed3.z << ")" << std::setw(5) << speedUnits;
		DrawTextToScreen(buffer.str().c_str(), startX + valueStep * 4.5f, startY, m_inGameFontSize, font);
		startY += step;

		//bool damagePossible = ENTITY::_GET_ENTITY_CAN_BE_DAMAGED(playerID);
		bool invincible = PLAYER::GET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID());
		sprintf_s(buf, "Invincible: %s", BoolToStr(invincible));
		DrawTextToScreen(buf, startX, startY, m_inGameFontSize, font);
		startY += step;

		bool ragdollPossible = PED::CAN_PED_RAGDOLL(playerID);
		sprintf_s(buf, "Can ragdoll: %s", BoolToStr(ragdollPossible));
		DrawTextToScreen(buf, startX, startY, m_inGameFontSize, font);
		startY += step;

		/*
		// NOT USEFUL, INPUTS ALWAYS ON.... Could it be that scripts don't share the control settings ?
		std::string inputs{ "Inputs available: " };
		bool skipCutscene = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SKIP_CUTSCENE);
		bool jump = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_JUMP);
		bool sprint = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SPRINT);
		bool cover = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_COVER);
		bool attack = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_ATTACK);
		bool phone = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_PHONE);
		bool characterWheel = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_CHARACTER_WHEEL);
		bool selectWeapon = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SELECT_WEAPON);
		bool specialAbility = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SPECIAL_ABILITY);
		inputs += std::string((skipCutscene ? "SKIP_CUTSCENE, " : ""));
		inputs += std::string((jump ? "JUMP, " : ""));
		inputs += std::string((sprint ? "SPRINT, " : ""));
		inputs += std::string((cover ? "COVER, " : ""));
		inputs += std::string((attack ? "ATTACK, " : ""));
		inputs += std::string((phone ? "PHONE, " : ""));
		inputs += std::string((characterWheel ? "CHARACTER_WHEEL, " : ""));
		inputs += std::string((selectWeapon ? "SELECT_WEAPON, " : ""));
		inputs += std::string((specialAbility ? "SPECIAL_ABILITY, " : ""));
		//inputs[255] = '\0'; // Make sure it's maximum 256
		DrawTextToScreen(inputs.c_str(), startX, startY, m_ingameFontSize, font);
		startY += step;*/

		sprintf_s(buf, "Game Time: %d", MISC::GET_GAME_TIMER());
		DrawTextToScreen(buf, startX, startY, m_inGameFontSize, font);
		startY += step;

		int streamingCount = STREAMING::GET_NUMBER_OF_STREAMING_REQUESTS();

		if (streamingCount >= m_largestStreaming)
		{
			m_largestStreaming = streamingCount;
			m_largestStreamingTime = MISC::GET_GAME_TIMER();

		}
		sprintf_s(buf, "Streaming: %d (%d)", streamingCount, m_largestStreaming);
		DrawTextToScreen(buf, startX, startY, m_inGameFontSize, font);
		startY += step;

		if (m_largestStreaming != 0 && MISC::GET_GAME_TIMER() >= m_largestStreamingTime + 3000)
			m_largestStreaming = 0;

		sprintf_s(buf, "Your Ped Handle: %d", playerID);
		DrawTextToScreen(buf, startX, startY, m_inGameFontSize, font);
		startY += step;

		sprintf_s(buf, "Menu key: 'Insert'");
		DrawTextToScreen(buf, 0.5f, 0.98f, m_inGameFontSize, font, false, 200, 0, 0);
	}

	if (m_scriptVarNeedsUpdate)
	{
		SetFloatingMenu(m_floatingMenu);
		SetShowAllInGame(m_showInGame);
		m_scriptVarNeedsUpdate = false;
	}
}

void CheatsMod::DrawPlayerMenu()
{
	if (ImGui::BeginMenu("Player"))
	{
		if (ImGui::MenuItem("Heal"))
		{
			RunOnNativeThread([]
			{
				auto p = PLAYER::PLAYER_PED_ID();
				ENTITY::SET_ENTITY_HEALTH(p, PED::GET_PED_MAX_HEALTH(p), FALSE);
			});
		}

		if (ImGui::MenuItem("Kill"))
		{
			RunOnNativeThread([]
			{
				ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0, FALSE);
			});
		}

		if (ImGui::BeginMenu("Teleport"))
		{
			ImGuiExtras::InputVector3("TeleportPos", &m_teleportPos);
			if (ImGui::Button("Teleport"))
			{
				RunOnNativeThread([=]
				{
					ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), m_teleportPos.x, m_teleportPos.y, m_teleportPos.z, TRUE, TRUE, TRUE, FALSE);
				});
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Weapon"))
		{
			ImGui::MenuItem("Explosive Bullets", NULL, &m_explosiveBullets);

			if (ImGui::MenuItem("Clear"))
			{
				RunOnNativeThread([]
				{
					WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_PED_ID(), FALSE);
				});
			}

			if (ImGui::MenuItem("Give All"))
			{
				RunOnNativeThread([]
				{
					for (int i = 0; i < IM_ARRAYSIZE(weapons); i++)
					{
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY((char *)weapons[i]), 99999, FALSE, TRUE);
					}
				});
			}

			if (ImGui::BeginMenu("Give..."))
			{
				for (int i = 0; i < IM_ARRAYSIZE(weapons); i++)
				{
					if (ImGui::MenuItem(weapons[i]))
					{
						RunOnNativeThread([i]
						{
							WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY((char *)weapons[i]), 99999, FALSE, TRUE);
						});
					}
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}

void CheatsMod::DrawVehicleMenu()
{
	if (ImGui::BeginMenu("Vehicle"))
	{
		if (ImGui::MenuItem("Repair"))
		{
			RunOnNativeThread([]
			{
				Vehicle v = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (v != NULL)
					VEHICLE::SET_VEHICLE_FIXED(v);
			});
		}

		if (ImGui::BeginMenu("Destroy##Vehicle"))
		{
			if (ImGui::MenuItem("Kill"))
			{
				RunOnNativeThread([]
				{
					Vehicle v = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
					if (v != NULL)
					{
						VEHICLE::SET_VEHICLE_ENGINE_HEALTH(v, 0.0f);
						VEHICLE::SET_VEHICLE_BODY_HEALTH(v, 0.0f);
						ENTITY::SET_ENTITY_HEALTH(v, 0, true);
					}
				});
			}

			if (ImGui::MenuItem("Explode"))
			{
				RunOnNativeThread([]
				{
					Vehicle v = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
					if (v != NULL)
						VEHICLE::EXPLODE_VEHICLE(v, TRUE, FALSE);
				});
			}

			ImGui::EndMenu();
		}
		/*
		if ( ImGui::MenuItem( "Customize" ) )
		{
			// TODO: show customization window
		}
		*/
		ImGui::EndMenu();
	}
}

void CheatsMod::DrawWorldMenu()
{
	if (ImGui::BeginMenu("World"))
	{
		if (m_lastSpawned != 0)
			ImGui::Text("Last Spawned Handle: %d", m_lastSpawned);
		if (ImGui::BeginMenu("Spawn Vehicle"))
		{
			if (ImGui::BeginMenu("Hash##SpawnVehicleMenu"))
			{
				if (ImGui::InputText("Hash##SpawnVehicleInput", m_vehicleHashInput, sizeof(m_vehicleHashInput), ImGuiInputTextFlags_EnterReturnsTrue))
				{
					RunOnNativeThread([=]
					{
						Model vehModel(m_vehicleHashInput);
						if (vehModel.IsValid() && vehModel.IsVehicle())
						{
							Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
							m_lastSpawned = VEHICLE::CREATE_VEHICLE(vehModel.GetHash(), pos.x, pos.y, pos.z, 0.0f, TRUE, TRUE, FALSE);
						}
					});
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}

void CheatsMod::DrawMissionMenu()
{
	if (ImGui::BeginMenu("Mission"))
	{
		if (m_helper == nullptr)
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Version unsupported.");
		else
		{
			if (ImGui::MenuItem("Skip"))
				m_helper->Skip();
		}

		ImGui::EndMenu();
	}
}

void CheatsMod::DrawHUDMenu()
{
	if (ImGui::BeginMenu("HUD"))
	{
		if (ImGui::InputFloat("Menu Font size", &m_menuFontSize, 0.1f))
			ClipFloat(m_menuFontSize, 0.6f, 2.0f);

		if (ImGui::InputFloat("Content Font size", &m_contentFontSize, 0.1f))
			ClipFloat(m_contentFontSize, 0.6f, 2.0f);

		if (ImGui::InputFloat("Ingame Font size", &m_inGameFontSize, 0.1f))
			ClipFloat(m_inGameFontSize, 0.1f, 2.0f);

		if (ImGui::Button("Reset"))
		{
			m_menuFontSize = 1.0f;
			m_contentFontSize = 1.0f;
			m_inGameFontSize = 0.3f;
			SetAllFontSize(m_menuFontSize, m_contentFontSize, m_inGameFontSize);
		}

		if (ImGui::Button("Set"))
			SetAllFontSize(m_menuFontSize, m_contentFontSize, m_inGameFontSize);
		ImGui::EndMenu();
	}
}

bool CheatsMod::Draw()
{
	ImGui::SetWindowFontScale(m_menuFontSize);
	if (ImGui::BeginMainMenuBar())
	{
		DrawPlayerMenu();
		DrawVehicleMenu();
		DrawWorldMenu();
		//DrawMissionMenu();
		DrawHUDMenu();

		if (m_supportGlobals)
			ImGui::SameLine(ImGui::GetContentRegionAvailWidth() - 100);
		else
		{
			ImGui::SameLine(ImGui::GetContentRegionAvailWidth() - 530);
			ImGui::TextColored(ImVec4(255, 0, 0, 255), "Your game version (%d) does not support specific memory access.", getGameVersion());
		}
		ImGui::Checkbox("Debug", &m_showDebug);
		if (ImGui::Checkbox("Show in game", &m_showInGame))
			m_scriptVarNeedsUpdate = true;
		if (ImGui::Checkbox("Floating menu", &m_floatingMenu))
			m_scriptVarNeedsUpdate = true;

		ImGui::EndMainMenuBar();
	}

	return false;
}