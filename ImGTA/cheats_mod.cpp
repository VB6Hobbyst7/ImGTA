/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "cheats_mod.h"

#include "script.h"
#include "utils.h"
#include "input_controls.h"
#include "mission_helper.h"
#include "model.h"
#include "vehicle_names.h"

#include "natives.h"

#include "imgui_extras.h"

#include <sstream>
#include <iomanip>
#include <vector>
#include <bitset>
#include <cstdio>

#pragma region Weapon Array
const char *weapons[] = { "weapon_dagger", "weapon_bat", "weapon_bottle", "weapon_crowbar", "weapon_unarmed", "weapon_flashlight", "weapon_golfclub", "weapon_hammer", "weapon_hatchet", "weapon_knuckle", "weapon_knife", "weapon_machete", "weapon_switchblade", "weapon_nightstick", "weapon_wrench", "weapon_battleaxe", "weapon_poolcue", "weapon_stone_hatchet", "weapon_pistol", "weapon_pistol_mk2", "weapon_combatpistol", "weapon_appistol", "weapon_stungun", "weapon_pistol50", "weapon_snspistol", "weapon_snspistol_mk2", "weapon_heavypistol", "weapon_vintagepistol", "weapon_flaregun", "weapon_marksmanpistol", "weapon_revolver", "weapon_revolver_mk2", "weapon_doubleaction", "weapon_raypistol", "weapon_ceramicpistol", "weapon_navyrevolver", "weapon_microsmg", "weapon_smg", "weapon_smg_mk2", "weapon_assaultsmg", "weapon_combatpdw", "weapon_machinepistol", "weapon_minismg", "weapon_raycarbine", "weapon_pumpshotgun", "weapon_pumpshotgun_mk2", "weapon_sawnoffshotgun", "weapon_assaultshotgun", "weapon_bullpupshotgun", "weapon_musket", "weapon_heavyshotgun", "weapon_dbshotgun", "weapon_autoshotgun", "weapon_assaultrifle", "weapon_assaultrifle_mk2", "weapon_carbinerifle", "weapon_carbinerifle_mk2", "weapon_advancedrifle", "weapon_specialcarbine", "weapon_specialcarbine_mk2", "weapon_bullpuprifle", "weapon_bullpuprifle_mk2", "weapon_compactrifle", "weapon_mg", "weapon_combatmg", "weapon_combatmg_mk2", "weapon_gusenberg", "weapon_sniperrifle", "weapon_heavysniper", "weapon_heavysniper_mk2", "weapon_marksmanrifle", "weapon_marksmanrifle_mk2", "weapon_rpg", "weapon_grenadelauncher", "weapon_grenadelauncher_smoke", "weapon_minigun", "weapon_firework", "weapon_railgun", "weapon_hominglauncher", "weapon_compactlauncher", "weapon_rayminigun", "weapon_grenade", "weapon_bzgas", "weapon_molotov", "weapon_stickybomb", "weapon_proxmine", "weapon_snowball", "weapon_pipebomb", "weapon_ball", "weapon_smokegrenade", "weapon_flare", "weapon_petrolcan", "gadget_parachute", "weapon_fireextinguisher", "weapon_hazardcan" };
#pragma endregion

void CheatsMod::Load()
{
	m_settings = m_dllObject.GetUserSettings().cheats;

	if (m_supportGlobals)
		m_helper = new MissionHelper(getGameVersion());

	// Setup available vehicles
	for (const auto & category : vehicle_names)
	{
		std::vector<int> tmpAvailableVehicles;
		for (int i = 0; i < category.second.size(); ++i)
		{
			if (STREAMING::IS_MODEL_A_VEHICLE(MISC::GET_HASH_KEY(category.second.at(i).c_str())))
				tmpAvailableVehicles.push_back(i);
		}
		m_availableVehicles.insert({ category.first, tmpAvailableVehicles });
	}
}

void CheatsMod::Unload()
{
	m_dllObject.GetUserSettings().cheats = m_settings;
}

void CheatsMod::Think()
{
	m_pauseMenuOn = HUD::IS_PAUSE_MENU_ACTIVE();
	m_currentPos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
	int playerPedID = PLAYER::PLAYER_PED_ID();
	int playerID = PLAYER::PLAYER_ID();
	char buf[112] = "";
	if (m_explosiveBullets)
		MISC::SET_EXPLOSIVE_AMMO_THIS_FRAME(playerPedID);

	if (m_dllObject.GetEnableHUD() && m_settings.common.showInGame)
	{
		if (m_settings.showGeneralInfo)
		{
			std::ostringstream buffer;
			float startX = m_settings.common.inGameOffsetX;
			float startY = m_settings.common.inGameOffsetY;
			const float step = 1.2f * TextFontHeight(m_settings.common.inGameFontSize, m_font);
			const float valueStep = 2.4f * TextFontHeight(m_settings.common.inGameFontSize, m_font);
			std::string speedUnits = m_settings.displayKMH ? "km/h" : "m/s";
			std::string accelerationUnits = m_settings.displayKMH ? "km/h/h" : "m/s/s";

			// TODO: Remove the manual tweaks here and there... It's unreadable

			// Position
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPedID, TRUE);
			buffer << "Position (x, y, z): (";
			DrawTextToScreen(buffer.str().c_str(), startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			buffer.str("");
			buffer.clear();
			buffer << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(8) << pos.x << ",";
			DrawTextToScreen(buffer.str().c_str(), startX + valueStep * 1.9f, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);

			buffer.str("");
			buffer.clear();
			buffer << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(8) << pos.y << ", ";
			DrawTextToScreen(buffer.str().c_str(), startX + valueStep * 2.9f, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);

			buffer.str("");
			buffer.clear();
			buffer << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(8) << pos.z << ")";
			DrawTextToScreen(buffer.str().c_str(), startX + valueStep * 3.9f, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);

			startY += step;

			int health = ENTITY::GET_ENTITY_HEALTH(playerPedID);
			int maxHealth = ENTITY::GET_ENTITY_MAX_HEALTH(playerPedID);
			std::snprintf(buf, sizeof(buf), "Health: %d / %d", health, maxHealth);
			DrawTextToScreen(buf, startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			int armour = PED::GET_PED_ARMOUR(playerPedID);
			int maxArmour = PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_ID());
			std::snprintf(buf, sizeof(buf), "Armour: %d / %d", armour, maxArmour);
			DrawTextToScreen(buf, startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			float speed = ENTITY::GET_ENTITY_SPEED(playerPedID);
			if (m_settings.displayKMH)
				speed *= 3.6f;
			if (m_maxSpeed < speed)
				m_maxSpeed = speed;
			buffer.str("");
			buffer.clear();
			buffer << std::fixed << std::setprecision(2) << "Speed: " << std::setfill(' ') << std::setw(7) << speed << std::setfill(' ') << std::setw(5) << speedUnits;
			DrawTextToScreen(buffer.str().c_str(), startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			m_accelCumulTime += SYSTEM::TIMESTEP();
			if (m_accelCumulTime > 0.3f) {
				float accelTimestep = m_settings.displayKMH ? (m_accelCumulTime * 1000.0f / 3600.0f) : (m_accelCumulTime * 1000.0f);
				m_currentAcceleration = (speed - m_lastSpeed) / accelTimestep;
				m_accelCumulTime = 0.0f;
				m_lastSpeed = speed; // Store current speed for next update
			}
			if (m_maxAccel < m_currentAcceleration)
				m_maxAccel = m_currentAcceleration;
			buffer.str("");
			buffer.clear();
			buffer << std::fixed << std::setprecision(3) << "Acceleration: " << std::setfill(' ') << std::setw(8) << m_currentAcceleration << std::setfill(' ') << std::setw(7) << accelerationUnits;
			DrawTextToScreen(buffer.str().c_str(), startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			std::snprintf(buf, sizeof(buf), "Max speed: %.3f %s", m_maxSpeed, speedUnits.c_str());
			DrawTextToScreen(buf, startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			std::snprintf(buf, sizeof(buf), "Max acceleration: %.3f %s", m_maxAccel, accelerationUnits.c_str());
			DrawTextToScreen(buf, startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			Vector3 speed3;
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(playerPedID, FALSE);
			if (vehicle)
				speed3 = ENTITY::GET_ENTITY_SPEED_VECTOR(vehicle, TRUE);
			else
				speed3 = ENTITY::GET_ENTITY_SPEED_VECTOR(playerPedID, TRUE);
			if (m_settings.displayKMH)
			{
				speed3.x *= 3.6f;
				speed3.y *= 3.6f;
				speed3.z *= 3.6f;
			}
			buffer.str("");
			buffer.clear();
			buffer << "Speed vector (x, y, z): (";
			DrawTextToScreen(buffer.str().c_str(), startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			buffer.str("");
			buffer.clear();
			buffer << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(8) << speed3.x << ",";
			DrawTextToScreen(buffer.str().c_str(), startX + valueStep * 2.5f, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);

			buffer.str("");
			buffer.clear();
			buffer << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(8) << speed3.y << ", ";
			DrawTextToScreen(buffer.str().c_str(), startX + valueStep * 3.5f, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);

			buffer.str("");
			buffer.clear();
			buffer << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(8) << speed3.z << ")" << std::setw(5) << speedUnits;
			DrawTextToScreen(buffer.str().c_str(), startX + valueStep * 4.5f, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			float sprintTimeRemaining = PLAYER::GET_PLAYER_SPRINT_TIME_REMAINING(playerID);
			std::snprintf(buf, sizeof(buf), "Sprint time remaining: %.1f s", sprintTimeRemaining);
			DrawTextToScreen(buf, startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			float underwaterTimeRemaining = PLAYER::GET_PLAYER_UNDERWATER_TIME_REMAINING(playerID);
			std::snprintf(buf, sizeof(buf), "Underwater time remaining: %.1f s", underwaterTimeRemaining);
			DrawTextToScreen(buf, startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			bool invincible = PLAYER::GET_PLAYER_INVINCIBLE(playerID);
			std::snprintf(buf, sizeof(buf), "Invincible: %s", BoolToStr(invincible));
			DrawTextToScreen(buf, startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			bool ragdollPossible = PED::CAN_PED_RAGDOLL(playerPedID);
			std::snprintf(buf, sizeof(buf), "Can ragdoll: %s", BoolToStr(ragdollPossible));
			DrawTextToScreen(buf, startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			int streamingCount = STREAMING::GET_NUMBER_OF_STREAMING_REQUESTS();

			if (streamingCount >= m_largestStreaming)
			{
				m_largestStreaming = streamingCount;
				m_largestStreamingTime = MISC::GET_GAME_TIMER();

			}
			std::snprintf(buf, sizeof(buf), "Streaming: %d (%d)", streamingCount, m_largestStreaming);
			DrawTextToScreen(buf, startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			if (m_largestStreaming != 0 && MISC::GET_GAME_TIMER() >= m_largestStreamingTime + 3000)
				m_largestStreaming = 0;

			std::snprintf(buf, sizeof(buf), "Your Ped Handle: %d", playerPedID);
			DrawTextToScreen(buf, startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			std::snprintf(buf, sizeof(buf), "Game Time: %d", MISC::GET_GAME_TIMER());
			DrawTextToScreen(buf, startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			startY += step;

			std::snprintf(buf, sizeof(buf), "Date (D/M/Y) and time: (%d / %d / %d: %d h, %d min, %d sec)",
				CLOCK::GET_CLOCK_DAY_OF_MONTH(), CLOCK::GET_CLOCK_MONTH() + 1, CLOCK::GET_CLOCK_YEAR(),
				CLOCK::GET_CLOCK_HOURS(), CLOCK::GET_CLOCK_MINUTES(), CLOCK::GET_CLOCK_SECONDS());
			DrawTextToScreen(buf, startX, startY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
		}
		
		
		if (m_settings.showAvailableInputs)
		{
			float inputStartX = 0.5f;
			float inputStartY = 0.75f;
			const float step = 1.2f * TextFontHeight(m_settings.common.inGameFontSize, m_font);
			std::string inputs{ "Available inputs:" };
			DrawTextToScreen(inputs.c_str(), inputStartX, inputStartY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			inputStartY += step;
			bool skipCutscene = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SKIP_CUTSCENE);
			bool jump = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_JUMP);
			bool sprint = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SPRINT);
			bool cover = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_COVER);
			bool enter = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_ENTER);
			bool exit = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_VEH_EXIT);
			bool attack = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_ATTACK);
			bool attackLight = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_MELEE_ATTACK_LIGHT);
			bool attackHeavy = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_MELEE_ATTACK_HEAVY);
			bool attackAlternate = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_MELEE_ATTACK_ALTERNATE);
			bool up = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_MOVE_UP_ONLY);
			bool down = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_MOVE_DOWN_ONLY);
			bool right = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_MOVE_RIGHT_ONLY);
			bool left = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_MOVE_LEFT_ONLY);
			bool aim = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_AIM);
			bool reload = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_RELOAD);
			bool phone = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_PHONE);
			bool phoneUp = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_CELLPHONE_UP);
			bool phoneDown = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_CELLPHONE_DOWN);
			bool characterWheel = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_CHARACTER_WHEEL);
			bool selectWeapon = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SELECT_WEAPON);
			bool specialAbility = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SPECIAL_ABILITY);
			bool specialAbilityPc = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SPECIAL_ABILITY_PC);
			bool camera = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_NEXT_CAMERA);
			bool lookBehind = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_LOOK_BEHIND);
			bool michael = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SELECT_CHARACTER_MICHAEL);
			bool franklin = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SELECT_CHARACTER_FRANKLIN);
			bool trevor = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SELECT_CHARACTER_TREVOR);
			bool multiplayer = PAD::IS_CONTROL_ENABLED(CONTROL_TYPE::PLAYER_CONTROL, CONTROL::INPUT_SELECT_CHARACTER_MULTIPLAYER);

			std::vector<std::string> inputStrings;
			inputStrings.push_back(skipCutscene ? "SKIP_CUTSCENE" : "");
			inputStrings.push_back(jump ? "JUMP" : "");
			inputStrings.push_back(sprint ? "SPRINT" : "");
			inputStrings.push_back(cover ? "COVER" : "");
			inputStrings.push_back(enter ? "VEH_ENTER" : "");
			inputStrings.push_back(exit ? "VEH_EXIT" : "");
			inputStrings.push_back(attack ? "ATTACK" : "");
			inputStrings.push_back(attackLight ? "ATTACK_LIGHT" : "");
			inputStrings.push_back(attackHeavy ? "ATTACK_HEAVY" : "");
			inputStrings.push_back(attackAlternate ? "ATTACK_ALTERNATE" : "");
			inputStrings.push_back(up ? "UP" : "");
			inputStrings.push_back(down ? "DOWN" : "");
			inputStrings.push_back(right ? "RIGHT" : "");
			inputStrings.push_back(left ? "LEFT" : "");
			inputStrings.push_back(aim ? "AIM" : "");
			inputStrings.push_back(reload ? "RELOAD" : "");
			inputStrings.push_back(phone ? "PHONE" : "");
			inputStrings.push_back(phoneUp ? "PHONE UP" : "");
			inputStrings.push_back(phoneDown ? "PHONE DOWN" : "");
			inputStrings.push_back(camera ? "CAMERA" : "");
			inputStrings.push_back(lookBehind ? "LOOK_BEHIND" : "");
			inputStrings.push_back(selectWeapon ? "SELECT_WEAPON" : "");
			inputStrings.push_back(specialAbility ? "SPECIAL_ABILITY" : "");
			inputStrings.push_back(specialAbilityPc ? "SPECIAL_ABILITY_PC" : "");
			inputStrings.push_back(characterWheel ? "CHARACTER_WHEEL" : "");
			inputStrings.push_back(trevor ? "TREVOR" : "");
			inputStrings.push_back(michael ? "MICHAEL" : "");
			inputStrings.push_back(franklin ? "FRANKLIN" : "");
			inputStrings.push_back(multiplayer ? "MULTIPLAYER" : "");

			// Display three lines at a time to optimize the number of calls to DrawTextToScreen
			std::string bufferLines;
			const int bufferLinesCount = 5;
			int i = 0;
			inputStartY -= step * (bufferLinesCount - 1);
			for (const auto & inputString : inputStrings)
			{
				if (i % bufferLinesCount == 0)
					bufferLines = "";
				bufferLines += inputString + "\n";

				if (i % bufferLinesCount == (bufferLinesCount - 1))
					DrawTextToScreen(bufferLines.c_str(), inputStartX, inputStartY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);

				// Change column
				if (i % 10 == 9)
				{
					inputStartX += (m_settings.common.columnSpacing + step);
					inputStartY -= step * 10;
				}
				inputStartY += step;
				i++;
			}
			if (i % bufferLinesCount == (bufferLinesCount - 1))
				DrawTextToScreen(bufferLines.c_str(), inputStartX, inputStartY, m_settings.common.inGameFontSize, m_font, false, m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
		}
	}

	std::snprintf(buf, sizeof(buf), "Menu key: 'Insert'");
	DrawTextToScreen(buf, 0.5f, 0.98f, m_settings.common.inGameFontSize, m_font, false, 200, 0, 0);

	if (m_scriptVarNeedsUpdate)
	{
		m_dllObject.SetFloatingMenu(m_settings.floatingMenu);
		m_dllObject.SetEnableHUD(m_settings.enableInGameHUD);
		m_scriptVarNeedsUpdate = false;
	}
}

void CheatsMod::DrawPlayerMenu()
{
	if (ImGui::BeginMenu("Player"))
	{
		if (ImGui::MenuItem("Fill Health, Armour, Energy"))
		{
			m_dllObject.RunOnNativeThread([]
			{
				int p = PLAYER::PLAYER_PED_ID();
				ENTITY::SET_ENTITY_HEALTH(p, PED::GET_PED_MAX_HEALTH(p), FALSE);
				PED::SET_PED_ARMOUR(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_ID()));
				PLAYER::SPECIAL_ABILITY_FILL_METER(PLAYER::PLAYER_ID(), 1, 0);
			});
		}

		if (ImGui::MenuItem("Heal"))
		{
			m_dllObject.RunOnNativeThread([]
			{
				int p = PLAYER::PLAYER_PED_ID();
				ENTITY::SET_ENTITY_HEALTH(p, PED::GET_PED_MAX_HEALTH(p), FALSE);
			});
		}

		if (ImGui::MenuItem("Max armour"))
		{
			m_dllObject.RunOnNativeThread([]
			{
				PED::SET_PED_ARMOUR(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_ID()));
			});
		}

		if (ImGui::MenuItem("Charge special ability"))
		{
			m_dllObject.RunOnNativeThread([]
			{
				PLAYER::SPECIAL_ABILITY_FILL_METER(PLAYER::PLAYER_ID(), 1, 0);
			});
		}

		if (ImGui::MenuItem("Kill"))
		{
			m_dllObject.RunOnNativeThread([]
			{
				ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0, FALSE);
			});
		}

		if (ImGui::BeginMenu("Teleport"))
		{
			ImGuiExtras::InputVector3("TeleportPos", &m_teleportPos);
			ImGui::SameLine();
			if (ImGui::Button("Current"))
				m_teleportPos = m_currentPos;

			if (ImGui::Button("Teleport"))
			{
				m_dllObject.RunOnNativeThread([=]
				{
					if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID()))
						ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE), m_teleportPos.x, m_teleportPos.y, m_teleportPos.z, TRUE, TRUE, TRUE, FALSE);
					else
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
				m_dllObject.RunOnNativeThread([]
				{
					WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_PED_ID(), FALSE);
				});
			}

			if (ImGui::MenuItem("Give All"))
			{
				m_dllObject.RunOnNativeThread([]
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
						m_dllObject.RunOnNativeThread([i]
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
			m_dllObject.RunOnNativeThread([]
			{
				Vehicle v = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (v != NULL)
					VEHICLE::SET_VEHICLE_FIXED(v);
			});
		}

		if (ImGui::BeginMenu("Pimp my ride"))
		{
			ImGui::InputFloat("Power percent", &m_powerPercent);
			ClipFloat(m_powerPercent, 0.0f, 10000.0f);
			if (ImGui::Button("Pimp it!"))
			{
				m_dllObject.RunOnNativeThread([=]
				{
					if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID()))
						VEHICLE::MODIFY_VEHICLE_TOP_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE), m_powerPercent);
				});
			}
			if (ImGui::Button("Can't handle it? Reset!"))
			{
				m_dllObject.RunOnNativeThread([=]
				{
					if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID()))
						VEHICLE::MODIFY_VEHICLE_TOP_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE), 100.0f);
				});
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Destroy##Vehicle"))
		{
			if (ImGui::MenuItem("Kill"))
			{
				m_dllObject.RunOnNativeThread([]
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
				m_dllObject.RunOnNativeThread([]
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

void CheatsMod::SpawnVehicle(const std::string & name)
{
	m_dllObject.RunOnNativeThread([=]
	{
		Model vehModel(name.c_str());
		if (vehModel.IsValid() && vehModel.IsVehicle())
		{
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
			m_lastSpawned = VEHICLE::CREATE_VEHICLE(vehModel.GetHash(), pos.x, pos.y, pos.z, 0.0f,
												    TRUE, m_attachVehicleToScript, FALSE);
			if (m_spawnInVehicle)
				TASK::TASK_WARP_PED_INTO_VEHICLE(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), m_lastSpawned, -1); // -1: driver seat
		}
	});
}

void CheatsMod::DrawWorldMenu()
{
	if (ImGui::BeginMenu("World"))
	{
		if (ImGui::BeginMenu("Spawn Vehicle"))
		{
			if (ImGui::BeginMenu("Category"))
			{
				for (const auto & category : m_availableVehicles)
				{
					if (category.second.size() > 0)
					{
						if (ImGui::BeginMenu(category.first.c_str()))
						{
							for (int veh_i = 0; veh_i < category.second.size(); ++veh_i)
							{
								const std::string name = vehicle_names.at(category.first).at(category.second.at(veh_i));
								if (ImGui::MenuItem(name.c_str())) {
									SpawnVehicle(name);
									m_lastSpawnedName = name;
								}
							}
							ImGui::EndMenu();
						}
					}
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Name##SpawnVehicleMenu"))
			{
				if (ImGui::InputText("Name##SpawnVehicleInput", m_vehicleNameInput, sizeof(m_vehicleNameInput), ImGuiInputTextFlags_EnterReturnsTrue))
				{
					SpawnVehicle(std::string(m_vehicleNameInput));
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		ImGui::MenuItem("Spawn in vehicle", NULL, &m_spawnInVehicle);
		ImGui::MenuItem("Attach vehicle to script", NULL, &m_attachVehicleToScript);

		ImGui::Separator();

		if (m_lastSpawned != 0) {
			ImGui::Text("Last spawned vehicle: %s (handle: %d)", m_lastSpawnedName.c_str(), m_lastSpawned);
			
			if (ImGui::Button("Re-spawn"))
				SpawnVehicle(m_lastSpawnedName);
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
	ImGui::Separator();
	ImGui::Checkbox("##Enable HUD", &m_settings.common.showInGame);

	if (ImGui::BeginMenu("HUD"))
	{
		DrawCommonSettingsMenus(m_settings.common);

		ImGui::Separator();
		ImGui::MenuItem("Show general info", NULL, &m_settings.showGeneralInfo);
		ImGui::MenuItem("Show available inputs", NULL, &m_settings.showAvailableInputs);
		ImGui::MenuItem("Km/h", NULL, &m_settings.displayKMH);
		if (ImGui::Button("Reset max speed/acceleration"))
		{
			m_maxSpeed = 0.0f;
			m_maxAccel = 0.0f;
		}


		ImGui::EndMenu();
	}

	ImGui::Separator();

	if (ImGui::BeginMenu("All modules"))
	{
		if (ImGui::MenuItem("Show HUDs", NULL, &m_inputShowAllHUDs))
			m_dllObject.SetShowAllInGame(m_inputShowAllHUDs);

		if (ImGui::MenuItem("Collapse windows", NULL, &m_inputCollapseAllWindows))
			m_dllObject.SetAllWindowCollapsed(m_inputCollapseAllWindows);

		if (ImGui::BeginMenu("Font size"))
		{
			if (ImGui::InputFloat("Menu Font size", &m_settings.common.menuFontSize, 0.1f))
			{
				ClipFloat(m_settings.common.menuFontSize, 0.6f, 2.0f);
				m_dllObject.SetAllFontSize(m_settings.common.menuFontSize, m_settings.common.contentFontSize, m_settings.common.inGameFontSize);
			}

			if (ImGui::InputFloat("Content Font size", &m_settings.common.contentFontSize, 0.1f))
			{
				ClipFloat(m_settings.common.contentFontSize, 0.6f, 2.0f);
				m_dllObject.SetAllFontSize(m_settings.common.menuFontSize, m_settings.common.contentFontSize, m_settings.common.inGameFontSize);
			}

			if (ImGui::InputFloat("In-game Font size", &m_settings.common.inGameFontSize, 0.1f))
			{
				ClipFloat(m_settings.common.inGameFontSize, 0.1f, 2.0f);
				m_dllObject.SetAllFontSize(m_settings.common.menuFontSize, m_settings.common.contentFontSize, m_settings.common.inGameFontSize);
			}

			if (ImGui::Button("Reset"))
			{
				m_settings.common.menuFontSize = 1.0f;
				m_settings.common.contentFontSize = 1.0f;
				m_settings.common.inGameFontSize = 0.3f;
				m_dllObject.SetAllFontSize(m_settings.common.menuFontSize, m_settings.common.contentFontSize, m_settings.common.inGameFontSize);
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Font color"))
		{
			if (ImGui::InputInt("Red", &m_settings.common.inGameFontRed))
			{
				ClipInt(m_settings.common.inGameFontRed, 0, 255);
				m_dllObject.SetAllInGameFontColor(m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			}

			if (ImGui::InputInt("Green", &m_settings.common.inGameFontGreen))
			{
				ClipInt(m_settings.common.inGameFontGreen, 0, 255);
				m_dllObject.SetAllInGameFontColor(m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			}

			if (ImGui::InputInt("Blue", &m_settings.common.inGameFontBlue))
			{
				ClipInt(m_settings.common.inGameFontBlue, 0, 255);
				m_dllObject.SetAllInGameFontColor(m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			}

			if (ImGui::Button("Reset"))
			{
				m_settings.common.inGameFontRed = 255;
				m_settings.common.inGameFontGreen = 255;
				m_settings.common.inGameFontBlue = 255;
				m_dllObject.SetAllInGameFontColor(m_settings.common.inGameFontRed, m_settings.common.inGameFontGreen, m_settings.common.inGameFontBlue);
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}

bool CheatsMod::Draw()
{
	ImGui::SetWindowFontScale(m_settings.common.menuFontSize);
	if (ImGui::BeginMainMenuBar())
	{
		DrawPlayerMenu();
		DrawVehicleMenu();
		DrawWorldMenu();
		//DrawMissionMenu();
		DrawHUDMenu();


		if (!m_supportGlobals)
		{
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), " Your game version (%d) does not support specific memory access.", getGameVersion());
		}
		if (m_textDrawMaxWarning)
		{
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(0.3f, 1.0f, 0.3f, 1.0f), " Maximum (100) number of element displayed in-game reached (Some will not be displayed)!");
		}
		if (m_pauseMenuOn)
		{
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(0.3f, 0.3f, 1.0f, 1.0f), " Game paused. No updates!");
		}

		ImGui::SameLine(ImGui::GetWindowWidth() - 230);
		if (ImGui::Checkbox("Enable HUD", &m_settings.enableInGameHUD))
			m_scriptVarNeedsUpdate = true;
		if (ImGui::Checkbox("Floating menu", &m_settings.floatingMenu))
			m_scriptVarNeedsUpdate = true;

		ImGui::EndMainMenuBar();
	}
	
	return false;
}