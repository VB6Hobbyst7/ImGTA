/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <Windows.h>

#include <functional>
#include <mutex>
#include "lua_engine.h"
#include "user_settings.h"

struct IDXGISwapChain;
class Mod;

class DLLObject
{
public:
	DLLObject();
	~DLLObject();

	void InitMods();
	void Update();
	void UpdateWindows();

	// Relying on this function is not recommended!
	void RunOnNativeThread(std::function<void()> func);

	void SetShowAllInGame(bool show);
	void SetAllFontSize(float menuSize, float contentSize, float ingameSize);
	void SetAllInGameFontColor(int red, int green, int blue);
	void Load();
	void Unload();
	void ToggleOpen();
	void OnPresent(IDXGISwapChain *swap);
	
	std::string GetSettingsFolder() { return settingsFolder; }
	bool HasInitializedImGui() { return hasInitializedImgui; }
	LONG_PTR GetOldProc() { return oldProc; }
	void SetOldProc(LONG_PTR proc) { oldProc = proc; }
	UserSettings & GetUserSettings() { return userSettings.Get(); }
	bool GetIsOpen() { return isOpen; }
	void SetIsOpen(bool open) { isOpen = open; }
	bool GetFloatingMenu() { return floatingMenu; }
	void SetFloatingMenu(bool isFloating) { floatingMenu = isFloating; }

private:
	std::string settingsFolder = "ImGTA/";
	std::string fileImGuiIni = settingsFolder + "Settings_imgui.ini";
	std::string fileImGuiLog = settingsFolder + "Log_imgui.txt";
	std::string userSettingsFile = settingsFolder + "Settings_HUD.ini";
	UserSettingsManager userSettings;
	std::vector<Mod *> modsLoaded;
	bool hasInitializedImgui;
	LONG_PTR oldProc = 0;
	bool isOpen = false;
	bool isLoaded = false;
	bool floatingMenu = false;

	std::vector<std::function<void()>> toRun;
	std::mutex toRun_mutex;
	LuaEngine luaEngine{settingsFolder};
};
