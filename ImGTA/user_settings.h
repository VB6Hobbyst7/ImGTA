/*
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


struct CommonSettings {
	bool showInGame = true;
	float menuFontSize = 1.0f;
	float contentFontSize = 1.0f;
	float inGameFontSize = 0.3f;
	int inGameFontRed = 255;
	int inGameFontGreen = 255;
	int inGameFontBlue = 255;
	float inGameOffsetX = 0.0f;
	float inGameOffsetY = 0.0f;
};

struct AreaSettings {
	CommonSettings common;
	//bool drawInGame = true;
	float drawOffsetZ = 0;
	bool drawBox = false;
};

struct AudioSettings {
	CommonSettings common;
};

struct CheatsSettings {
	CommonSettings common;
	bool showAvailableInputs = true;
	bool showDebug = true;
	bool floatingMenu = true;
	bool displayKMH = true;
};

struct CommsSettings {
	CommonSettings common;
};

struct CutsceneSettings {
	CommonSettings common;
};

struct HandleHelperSettings {
	CommonSettings common;
	int nearbyObjectMax = 30;
	float drawOffsetZ = 0;
	bool drawEntityInfo = true;
	bool drawOnScreenEntityOnly = true;
	bool drawId = true;
	bool drawLife = true;
};

struct LuaConsoleSettings {
	CommonSettings common;
	bool showInfo = true;
};

struct MemWatcherSettings {
	CommonSettings common;
	bool sortByName = true;
	bool inputHexIndex = false;
	bool displayHudInfo = true;
	/*float inGameOffsetX = 0.01f;
	float inGameOffsetY = 0.08f;*/
};

struct MissionSettings {
	CommonSettings common;
};

struct ScriptsSettings {
	CommonSettings common;
	bool sortByName = true;
	/*bool drawInGame = false;
	float inGameOffsetX = 0.84f;
	float inGameOffsetY = 0.01f;*/
};

struct PlayerSwitchSettings {
	CommonSettings common;
};

struct SyncSceneSettings {
	CommonSettings common;
};

struct UserSettings {
	AreaSettings area;
	AudioSettings audio;
	CheatsSettings cheats;
	CommsSettings comms;
	CutsceneSettings cutscene;
	HandleHelperSettings handleHelper;
	LuaConsoleSettings luaConsole;
	MemWatcherSettings memWatcher;
	MissionSettings mission;
	ScriptsSettings scripts;
	PlayerSwitchSettings playerSwitch;
	SyncSceneSettings syncScene;
};

class UserSettingsManager {
public:
	void Load(const std::string & filename);
	void Save(const std::string & filename);
	
	UserSettings & Get() { return s; }

private:
	void LoadCommon(std::string & line, std::istringstream & stream, CommonSettings & common, const std::string & prefix);
	void SaveCommon(std::ofstream & file, CommonSettings & common, const std::string & prefix);

	UserSettings s;
};
