#pragma once
#include "mod.h"
#include <sstream>
#include <vector>
#include <string>

class LuaConsoleMod : public Mod
{
public:
	LuaConsoleMod(bool supportGlobals) : Mod("Lua Console", true, supportGlobals)
	{
		m_windowFlags = ImGuiWindowFlags_MenuBar;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawMenuBar();

	char m_input[1024] = "";
	char m_luaInput[1024] = "";
	int m_currentHistory = 0;
	std::vector<std::string> m_commandHistory;
};