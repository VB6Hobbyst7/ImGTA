/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "mod.h"
#include "user_settings.h"

#include "types.h"

#include <mutex>

struct PaddedEntity
{
	DWORD _padding;
	int id;
};

const int maxEntCount = 100;
struct nearbyEnts
{
	int size = maxEntCount;
	PaddedEntity entities[maxEntCount] = { 0, 0 };
};

class HandleHelperMod : public Mod
{
public:
	HandleHelperMod(DLLObject & dllObject, bool supportGlobals) : Mod(dllObject, "Handle Helper", true, supportGlobals)
	{
		m_windowFlags = ImGuiWindowFlags_MenuBar;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawMenuBar();
	void UpdateHandleData();
	void ResetData();
	void ListPeds();
	void ListVehs();
	CommonSettings & GetCommonSettings() override { return m_settings.common; }

	HandleHelperSettings m_settings;

	int m_type = 0;
	int m_health = 0;
	int m_maxHealth = 0;
	bool m_injured = false;
	Hash m_modelHash = 0;
	Vector3 m_position = {};
	bool m_isMissionEntity = false;
	std::mutex m_pedListMutex;
	std::mutex m_vehListMutex;
	std::string m_pedList = "";
	std::string m_vehList = "";

	// ImGui inputs / internals
	bool m_wantsUpdate = false;
	int m_handleInput = 0;
	bool m_constantUpdate = true;
	char m_animDictInput[256] = "";
	char m_animNameInput[256] = "";
	unsigned int m_animFlags = 0;
	bool m_animLoop = false;
};