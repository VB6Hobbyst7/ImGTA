#pragma once
#include "mod.h"
#include "lua_engine.h"
#include "types.h"

class SyncSceneMod : public Mod
{
public:
	SyncSceneMod(bool supportGlobals) : Mod("Synchronized Scene", true, supportGlobals)
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
	void ListRunning();

	float m_phase = 0;
	float m_rate = 0;
	int m_looped = 0;
	bool m_running = 0;
	bool m_holdLastFrame = false;
	std::string m_runningList = "";

	float m_phaseInput = 0;
	float m_rateInput = 0;

	// ImGui inputs / internals
	bool m_wantsUpdate = false;
	int m_handleInput = 0;
	bool m_constantUpdate = true;
	char m_animDictInput[256] = "";
	char m_animNameInput[256] = "";
	unsigned int m_animFlags = 0;
	bool m_animLoop = false;
};