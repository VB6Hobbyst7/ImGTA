/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "mod.h"
#include "types.h"

class MissionHelper;
struct CheatsSettings;

class CheatsMod : public Mod
{
public:
	CheatsMod(DLLObject & dllObject, bool supportGlobals) : Mod(dllObject, "Cheats", false, supportGlobals)
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

	CheatsSettings m_settings;
	bool m_explosiveBullets = false;
	bool m_scriptVarNeedsUpdate = false;

	bool m_pauseMenuOn = false;

	int m_largestStreaming = 0;
	int m_largestStreamingTime = 0;

	Vector3 m_teleportPos;

	char m_vehicleHashInput[256] = "";

	// TODO: create spawn history, allow more stuff.
	Entity m_lastSpawned = 0;

	MissionHelper *m_helper = nullptr;
};