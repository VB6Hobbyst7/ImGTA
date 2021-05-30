/*
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "user_settings.h"

void UserSettingsManager::Load(const std::string & filename) {
	std::ifstream file(filename);
	std::string line;

	while (std::getline(file, line)) {
		std::istringstream current(line.substr(line.find("=") + 1));

		// Common
		if (line.find("common.menuFontSize") != -1)
			current >> s.common.menuFontSize;
		else if (line.find("common.contentFontSize") != -1)
			current >> s.common.contentFontSize;
		else if (line.find("common.inGameFontSize") != -1)
			current >> s.common.inGameFontSize;
		else if (line.find("common.inGameFontRed") != -1)
			current >> s.common.inGameFontRed;
		else if (line.find("common.inGameFontGreen") != -1)
			current >> s.common.inGameFontGreen;
		else if (line.find("common.inGameFontBlue") != -1)
			current >> s.common.inGameFontBlue;
		else if (line.find("common.showInGame") != -1)
			current >> s.common.showInGame;
		// Area
		else if (line.find("area.drawInGame") != -1)
			current >> s.area.drawInGame;
		else if (line.find("area.drawOffsetZ") != -1)
			current >> s.area.drawOffsetZ;
		else if (line.find("area.drawBox") != -1)
			current >> s.area.drawBox;
		// Audio
		// Cheats
		else if (line.find("cheats.showAvailableInputs") != -1)
			current >> s.cheats.showAvailableInputs;
		else if (line.find("cheats.showDebug") != -1)
			current >> s.cheats.showDebug;
		else if (line.find("cheats.floatingMenu") != -1)
			current >> s.cheats.floatingMenu;
		else if (line.find("cheats.displayKMH") != -1)
			current >> s.cheats.displayKMH;
		// Comms
		// Cutscene
		// HandleHelper
		else if (line.find("handleHelper.nearbyObjectMax") != -1)
			current >> s.handleHelper.nearbyObjectMax;
		else if (line.find("handleHelper.drawOffsetZ") != -1)
			current >> s.handleHelper.drawOffsetZ;
		else if (line.find("handleHelper.drawEntityInfo") != -1)
			current >> s.handleHelper.drawEntityInfo;
		else if (line.find("handleHelper.drawOnScreenEntityOnly") != -1)
			current >> s.handleHelper.drawOnScreenEntityOnly;
		else if (line.find("handleHelper.drawId") != -1)
			current >> s.handleHelper.drawId;
		else if (line.find("handleHelper.drawLife") != -1)
			current >> s.handleHelper.drawLife;
		// LuaConsole
		else if (line.find("luaConsole.showInfo") != -1)
			current >> s.luaConsole.showInfo;
		// MemWatcher
		else if (line.find("memWatcher.sortByName") != -1)
			current >> s.memWatcher.sortByName;
		else if (line.find("memWatcher.inputHexIndex") != -1)
			current >> s.memWatcher.inputHexIndex;
		else if (line.find("memWatcher.displayHudInfo") != -1)
			current >> s.memWatcher.displayHudInfo;
		else if (line.find("memWatcher.inGameOffsetX") != -1)
			current >> s.memWatcher.inGameOffsetX;
		else if (line.find("memWatcher.inGameOffsetY") != -1)
			current >> s.memWatcher.inGameOffsetY;
		// Mission
		// Scripts
		else if (line.find("scripts.sortByName") != -1)
			current >> s.scripts.sortByName;
		else if (line.find("scripts.drawInGame") != -1)
			current >> s.scripts.drawInGame;
		else if (line.find("scripts.inGameOffsetX") != -1)
			current >> s.scripts.inGameOffsetX;
		else if (line.find("scripts.inGameOffsetY") != -1)
			current >> s.scripts.inGameOffsetY;
		// PlayerSwitch
		// SyncScene
	}
}

void UserSettingsManager::Save(const std::string & filename) {
	std::ofstream file(filename);
	std::string line;


	std::istringstream current(line.substr(line.find("=") + 1));

	// Common
	file << "common.menuFontSize = " << s.common.menuFontSize << std::endl;
	file << "common.contentFontSize = " << s.common.contentFontSize << std::endl;
	file << "common.inGameFontSize = " << s.common.inGameFontSize << std::endl;
	file << "common.inGameFontRed = " << s.common.inGameFontRed << std::endl;
	file << "common.inGameFontGreen = " << s.common.inGameFontGreen << std::endl;
	file << "common.inGameFontBlue = " << s.common.inGameFontBlue << std::endl;
	file << "common.showInGame = " << s.common.showInGame << std::endl;
	// Area
	file << "area.drawInGame = " << s.area.drawInGame << std::endl;
	file << "area.drawOffsetZ = " << s.area.drawOffsetZ << std::endl;
	file << "area.drawBox = " << s.area.drawBox << std::endl;
	// Audio
	// Cheats
	file << "cheats.showAvailableInputs = " << s.cheats.showAvailableInputs << std::endl;
	file << "cheats.showDebug = " << s.cheats.showDebug << std::endl;
	file << "cheats.floatingMenu = " << s.cheats.floatingMenu << std::endl;
	file << "cheats.displayKMH = " << s.cheats.displayKMH << std::endl;
	// Comms
	// Cutscene
	// HandleHelper
	file << "handleHelper.nearbyObjectMax = " << s.handleHelper.nearbyObjectMax << std::endl;
	file << "handleHelper.drawOffsetZ = " << s.handleHelper.drawOffsetZ << std::endl;
	file << "handleHelper.drawEntityInfo = " << s.handleHelper.drawEntityInfo << std::endl;
	file << "handleHelper.drawOnScreenEntityOnly = " << s.handleHelper.drawOnScreenEntityOnly << std::endl;
	file << "handleHelper.drawId = " << s.handleHelper.drawId << std::endl;
	file << "handleHelper.drawLife = " << s.handleHelper.drawLife << std::endl;
	// LuaConsole
	file << "luaConsole.showInfo = " << s.luaConsole.showInfo << std::endl;
	// MemWatcher
	file << "memWatcher.sortByName = " << s.memWatcher.sortByName << std::endl;
	file << "memWatcher.inputHexIndex = " << s.memWatcher.inputHexIndex << std::endl;
	file << "memWatcher.displayHudInfo = " << s.memWatcher.displayHudInfo << std::endl;
	file << "memWatcher.inGameOffsetX = " << s.memWatcher.inGameOffsetX << std::endl;
	file << "memWatcher.inGameOffsetY = " << s.memWatcher.inGameOffsetY << std::endl;
	// Mission
	// Scripts
	file << "scripts.sortByName = " << s.scripts.sortByName << std::endl;
	file << "scripts.drawInGame = " << s.scripts.drawInGame << std::endl;
	file << "scripts.inGameOffsetX = " << s.scripts.inGameOffsetX << std::endl;
	file << "scripts.inGameOffsetY = " << s.scripts.inGameOffsetY << std::endl;
	// PlayerSwitch
	// SyncScene


}