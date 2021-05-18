#pragma once
#include "mod.h"
#include "watch_entry.h"
#include <vector>
#include <mutex>

class GlobalWatchMod : public Mod
{
public:
    GlobalWatchMod(bool supportGlobals) : Mod( "Global Watch", true, supportGlobals)
    {
        m_iWindowFlags = ImGuiWindowFlags_MenuBar;
    }

    bool Draw() override;
    void Think() override;
    void Load() override;
    void Unload() override;

private:
    void ShowAddAddress();
    void DrawMenuBar();
    void ShowSelectedPopup();
	void LoadAllDebug();

    std::vector<WatchEntry> m_watches;
    std::mutex m_watchesMutex;

    WatchEntry *m_pSelectedEntry = nullptr;
    int m_iInputAddr = 0;
    int m_iInputType = 0;

	float m_inGameOffsetX = 0.01f;
	float m_inGameOffsetY = 0.08f;
};