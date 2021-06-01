/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "mod.h"
#include "watch_entry.h"
#include <vector>
#include <mutex>

struct MemWatcherSettings;

class MemWatcherMod : public Mod
{
public:
	MemWatcherMod(DLLObject & dllObject, bool supportGlobals) : Mod(dllObject, "Memory watcher", true, supportGlobals)
	{
		m_windowFlags = ImGuiWindowFlags_MenuBar;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

protected:
	void SortWatches();
	void ShowAddAddress(bool isGlobal);
	void ShowSelectedPopup();
	void DrawMenuBar();

	MemWatcherSettings m_settings;
	std::vector<WatchEntry> m_watches;
	std::mutex m_watchesMutex;

	WatchEntry *m_selectedEntry = nullptr;
	int m_inputAddressIndex = 0;
	int m_inputType = 0;
	int m_indexRange = 1;

	char m_scriptNameBuf[128] = { 0 };
	char m_watchInfoBuf[512] = { 0 };
	char m_watchInfoModifyBuf[512] = { 0 };
	std::string m_scriptName = "";
	std::string m_watchInfo = "";
	bool m_autoScrollDown = false;
	int m_scriptHash = 0;
	bool m_scriptRunning = false;
	bool m_selectedWatchScriptRunning = false;
	bool m_addressAvailable = true;
	bool m_inputsUpdated = false;
	bool m_variableAlreadyWatched = false;
	std::string m_onlineVersion = "";
};

bool CompareWatch(WatchEntry a, WatchEntry b);