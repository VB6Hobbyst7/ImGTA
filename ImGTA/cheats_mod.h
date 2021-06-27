/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "mod.h"
#include "types.h"
#include "user_settings.h"

#include <unordered_map>

class MissionHelper;

class CheatsMod : public Mod
{
public:
	CheatsMod(DLLObject & dllObject, bool supportGlobals) :
		Mod(dllObject, "Cheats", false, supportGlobals),
		m_availableVehicles(),
		m_lastSpawnedName("")
	{
		m_teleportPos.x = 0;
		m_teleportPos.y = 0;
		m_teleportPos.z = 0;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawPlayerMenu();
	void DrawVehicleMenu();
	void DrawWorldMenu();
	void DrawMissionMenu();
	void DrawHUDMenu();
	CommonSettings & GetCommonSettings() override { return m_settings.common; }
	void SpawnVehicle(const std::string & name);

	CheatsSettings m_settings;
	bool m_explosiveBullets = false;
	bool m_scriptVarNeedsUpdate = true;
	bool m_inputShowAllHUDs = false;
	bool m_inputCollapseAllWindows = false;

	std::unordered_map<std::string, std::vector<int>> m_availableVehicles;
	int m_largestStreaming = 0;
	int m_largestStreamingTime = 0;

	Vector3 m_teleportPos;
	Vector3 m_currentPos;

	char m_vehicleNameInput[256] = "";
	float m_powerPercent = 300.0f;
	float m_maxSpeed = 0.0f;
	float m_maxAccel = 0.0f;
	float m_lastSpeed = 0.0f;
	float m_currentAcceleration = 0.0f;
	float m_accelCumulTime = 0.0f;
	
	Entity m_lastSpawned = 0;
	std::string m_lastSpawnedName;
	bool m_spawnInVehicle = true;
	bool m_attachVehicleToScript = false;

	MissionHelper *m_helper = nullptr;
};