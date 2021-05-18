#pragma once
#include "mod.h"
#include "lua_engine.h"
#include "types.h"

class SyncSceneMod : public Mod
{
public:
    SyncSceneMod() : Mod( "Synchronized Scene", true )
    {
        m_iWindowFlags = ImGuiWindowFlags_MenuBar;
    }

    bool Draw() override;
    void Think() override;
    void Load() override;
    void Unload() override;

private:
	void DrawMenuBar();
	void UpdateHandleData(bool once = false);
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
	bool m_bWantsUpdate = false;
	int m_iHandleInput = 0;
	bool m_bConstantUpdate = true;
	char m_szAnimDictInput[256] = "";
	char m_szAnimNameInput[256] = "";
	unsigned int m_iAnimFlags = 0;
	bool m_bAnimLoop = false;
};