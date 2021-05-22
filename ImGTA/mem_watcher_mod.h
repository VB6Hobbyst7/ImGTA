#pragma once
#include "mod.h"
#include "types.h"
#include "watch_entry.h"
#include <vector>
#include <mutex>

class MemWatcherMod : public Mod
{
public:
	MemWatcherMod(bool supportGlobals) : Mod("Memory watcher", true, supportGlobals)
	{
		m_windowFlags = ImGuiWindowFlags_MenuBar;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

protected:
	void ShowAddAddress(bool isGlobal);
	void DrawMenuBar();
	void ShowSelectedPopup();

	std::vector<WatchEntry> m_watches;
	std::mutex m_watchesMutex;

	WatchEntry *m_selectedEntry = nullptr;
	int m_inputAddressIndex = 0;
	int m_inputType = 0;
	bool m_inputHexIndex = false;

	float m_inGameOffsetX = 0.01f;
	float m_inGameOffsetY = 0.08f;

	bool m_askForThreadId = false;
	char m_scriptNameBuf[128] = { 0 };
	char m_watchInfoBuf[512] = { 0 };
	char m_watchInfoModifyBuf[512] = { 0 };
	std::string m_scriptName = "";
	std::string m_watchInfo = "";
	int m_scriptHash = 0;
	bool m_scriptRunning = false;
	bool m_selectedWatchScriptRunning = false;
	bool m_addressUnavailable = false;
};
