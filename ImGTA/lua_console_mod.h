/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "mod.h"
#include "lua_engine.h"
#include <sstream>
#include <vector>
#include <string>

struct LuaConsoleSettings;

class LuaConsoleMod : public Mod
{
public:
	LuaConsoleMod(DLLObject & dllObject, bool supportGlobals, LuaEngine & luaEngine);

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

	static int InputTextCallbackStub(ImGuiInputTextCallbackData* data)
	{
		LuaConsoleMod* console = (LuaConsoleMod*)data->UserData;
		return console->InputTextCallback(data);
	}

	static const int commandHistorySize = 200;
	static const int commandCount = 7000;

private:
	void DrawMenuBar();
	int InputTextCallback(ImGuiInputTextCallbackData * data);
	void IncrementCurrentHistoryId();
	void DecrementCurrentHistoryId();

	LuaConsoleSettings m_settings;
	LuaEngine & m_luaEngine;

	char m_input[1024] = "";
	char m_luaInput[1024] = "";
	bool m_inHistory = false;
	bool m_confirmedOutOfHistory = false;
	int m_currentHistoryId = -1;
	int m_lastInputHistoryId = -1;
	std::string m_savedCommand = "";
	std::vector<std::string> m_commandHistory;
	std::vector<std::string> m_commands;
	
	bool m_tabbingCandidates = false;
	std::vector<std::string> m_lastCandidates;
	int m_lastCandidatesId = 0;
	std::string m_lastInputBuffer = "";
	bool m_scrollDown = false;
};