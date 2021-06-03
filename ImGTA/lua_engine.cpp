/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * Copyright (c) 2021, Rayope
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "lua_engine.h"

#include "utils.h"

#include "nativeCaller.h"


const struct luaL_Reg LuaEngine::baselib[] =
{
	{ "print", LuaEngine::lua_Print }, // override print with our print
	{ NULL, NULL }
};

const struct luaL_Reg LuaEngine::gtalib[] =
{
	{ "invoke", LuaEngine::lua_Invoke },
	{ "invokeString", LuaEngine::lua_InvokeString },
	{ "invokeInteger", LuaEngine::lua_InvokeInteger },
	{ "invokeFloat", LuaEngine::lua_InvokeFloat },
	{ "getGlobalInt", LuaEngine::lua_GetGlobalInt },
	{ "setGlobal", LuaEngine::lua_SetGlobal },
	{ NULL, NULL }
};

std::ostringstream LuaEngine::luaStream{};

// TODO: can we combine these somehow?
void LuaEngine::lua_BaseInvoke(lua_State *L)
{
	UINT64 addr = luaL_checkinteger(L, 1);
	nativeInit(addr);

	for (int i = 2; i <= lua_gettop(L); i++)
	{
		if (lua_isinteger(L, i))
			nativePush(static_cast<int>(lua_tointeger(L, i)));
		else if (lua_isnumber(L, i))
			nativePush(static_cast<float>(lua_tonumber(L, i)));
		else if (lua_isstring(L, i))
			nativePush(lua_tostring(L, i));
		else
			luaL_error(L, "not an integer, number, or string");
		lua_pop(L, 1);
	}
}

int LuaEngine::lua_Invoke(lua_State *L)
{
	lua_BaseInvoke(L);

	nativeCall();

	return 1;
}

int LuaEngine::lua_InvokeString(lua_State *L)
{
	lua_BaseInvoke(L);

	lua_pushstring(L, *reinterpret_cast<char **>(nativeCall()));

	return 1;
}

int LuaEngine::lua_InvokeInteger(lua_State *L)
{
	lua_BaseInvoke(L);

	lua_pushinteger(L, *reinterpret_cast<int *>(nativeCall()));

	return 1;
}

int LuaEngine::lua_InvokeFloat(lua_State *L)
{
	lua_BaseInvoke(L);

	lua_pushnumber(L,  *reinterpret_cast<float *>(nativeCall()));
	
	return 1;
}

int LuaEngine::lua_Print(lua_State *L)
{
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	for (i = 1; i <= n; i++)
	{
		/* for each argument */
		const char *s = luaL_tolstring(L, i, nullptr);  /* convert it to string */
		if (i > 1)  /* not the first element? */
			luaStream << "\t";  /* add a tab before it */
		luaStream << s;
		lua_pop(L, 1);  /* pop result */
	}
	luaStream << std::endl;
	return 0;
}

int LuaEngine::lua_GetGlobalInt(lua_State *L)
{
	int addr = static_cast<int>(luaL_checkinteger(L, 1));

	if (addr < 0)
		luaL_error(L, "invalid global address");

	UINT64 *realAddr = GetGlobalPtr(addr);

	if (!realAddr)
		luaL_error(L, "invalid global address");

	lua_pushinteger(L, *reinterpret_cast<int *>(realAddr));

	return 1;
}

int LuaEngine::lua_SetGlobal(lua_State *L)
{
	int addr = static_cast<int>(luaL_checkinteger(L, 1));

	if (addr < 0)
		luaL_error(L, "invalid global address");

	UINT64 *realAddr = GetGlobalPtr(addr);

	if (!realAddr)
		luaL_error(L, "invalid global address");

	if (lua_isinteger(L, 2))
		(*reinterpret_cast<int *>(realAddr)) = static_cast<int>(lua_tointeger(L, 2));
	else if (lua_isnumber(L, 2))
		(*reinterpret_cast<float *>(realAddr)) = static_cast<float>(lua_tonumber(L, 2));
	else // TODO: allow string copy. (dangerous, technically)
		luaL_error(L, "not an integer or number.");

	lua_pop(L, 1);

	return 0;
}

LuaEngine::LuaEngine(const std::string & scriptFolder) :
	m_scriptFolder(scriptFolder),
	m_nativesFile(scriptFolder + "natives.lua"),
	m_nativeListerFile(scriptFolder + "nativesLister.lua")
{
	state = luaL_newstate();
	luaL_openlibs(state);
	lua_pushglobaltable(state);
	luaL_setfuncs(state, baselib, 0);
	luaL_setfuncs(state, gtalib, 0);
	LoadLuaNatives();
}

LuaEngine::~LuaEngine()
{
	if (!state)
		return;
	lua_close(state);
}

void LuaEngine::LoadLuaNatives()
{
	if (luaL_dofile(state, m_nativesFile.c_str()) != LUA_OK)
	{
		luaStream << "WARN: Unable to dofile for the file '"
			<< m_nativesFile << "'!" << std::endl;
		luaStream << "\t" << GetLastLuaError() << std::endl;
	}
}

int LuaEngine::DoLuaString(const char *line)
{
	return luaL_dostring(state, line);
}

int LuaEngine::DoLuaFile(const char *path)
{
	return luaL_dofile(state, path);
}

bool LuaEngine::IsLuaReady()
{
	return state != nullptr;
}

const char * LuaEngine::GetLastLuaError()
{
	return lua_tostring(state, -1);
}

// Thanks Zack Lee: https://stackoverflow.com/questions/51063716/how-to-get-returned-table-from-lua-function-in-c
void LuaEngine::ListAllCommands(std::vector<std::string> & commandList)
{
	if (!state)
		return;

	int iErr = 0;
	if ((iErr = luaL_loadfile(state, m_nativeListerFile.c_str())) == 0)
	{
		// Call main...
		if ((iErr = lua_pcall(state, 0, LUA_MULTRET, 0)) == 0)
		{
			// Push the function name onto the stack
			lua_getglobal(state, "list_all_functions");
			if (lua_pcall(state, 0, 1, 0))
			{
				std::string error_str = lua_tostring(state, -1);
			}

			if (lua_istable(state, -1))
			{
				lua_pushvalue(state, -1);
				lua_pushnil(state);
				while (lua_next(state, -2))
				{
					if (lua_isstring(state, -1))
					{
						commandList.emplace_back(lua_tostring(state, -1));
					}
					lua_pop(state, 1);
				}
				lua_pop(state, -1);
			}
		}
	}
}
