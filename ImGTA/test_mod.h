#pragma once
#include "mod.h"
#include "lua_engine.h"
#include "types.h"

class TestMod : public Mod
{
public:
	TestMod(bool supportGlobals) : Mod("Test", true, supportGlobals)
	{
		m_windowFlags = ImGuiWindowFlags_MenuBar;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawMenuBar();
};

