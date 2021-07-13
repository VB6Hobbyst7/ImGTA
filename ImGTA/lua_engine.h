/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "lua.hpp"

#include <sstream>
#include <string>
#include <vector>

class LuaEngine
{
public:
	LuaEngine(const std::string & scriptFolder);
	~LuaEngine();
	int DoLuaString(const char *line);
	int DoLuaFile(const char *path);
	bool IsLuaReady();
	const char *GetLastLuaError();
	void LoadLuaNatives();
	void ListAllCommands(std::vector<std::string> & commandList);

	static void lua_BaseInvoke(lua_State *L);
	static int lua_Invoke(lua_State *L);
	static int lua_InvokeString(lua_State *L);
	static int lua_InvokeInteger(lua_State *L);
	static int lua_InvokeFloat(lua_State *L);
	static int lua_Print(lua_State *L);
	static int lua_GetGlobalInt(lua_State *L);
	static int lua_SetGlobal(lua_State *L);

	// TODO: Don't really like luaStream being static here, it shouldn't be...
	static std::ostringstream luaStream;

private:
	std::string m_scriptFolder;
	std::string m_nativesFile;
	std::string m_nativeListerFile;
	lua_State * state = nullptr;
	lua_Debug ar = {};

	static const struct luaL_Reg baselib[];
	static const struct luaL_Reg gtalib[];
};

