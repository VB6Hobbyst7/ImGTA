/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "mod.h"
#include <vector>
#include <string>
#include <mutex>

struct ScriptsSettings;

class ScriptObject
{
public:
	ScriptObject(std::string name = "", int handle = 0) : m_scriptName(name), m_handle(handle) {}
	std::string m_scriptName;
	int m_handle;
};

class ScriptsMod : public Mod
{
public:
	ScriptsMod(DLLObject & dllObject, bool supportGlobals) : Mod(dllObject, "Scripts", true, supportGlobals)
	{
		m_windowFlags = ImGuiWindowFlags_MenuBar;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawMenuBar();
	void ShowSelectedPopup();

	ScriptsSettings m_settings;
	std::vector<ScriptObject> m_scripts;
	std::mutex m_scriptsMutex; // needed because it's accessed between native thread and render thread.
	bool m_enablePinnedScript = false;
	ScriptObject m_pinnedScript;
	std::string m_pinnedScriptName;

	bool m_noLoadingScreenOption = false;
	bool m_noLoadingScreen = false;

	// ImGui inputs / internals
	bool m_wantsUpdate = false;
	bool m_constantUpdate = true;
	ScriptObject *m_selected;
	unsigned int m_startFlags = 1024;
	char m_startScriptName[128] = "";
	bool m_initColumnWidth = true; // Weird hack, set the column two consecutive frames and it works
};

bool CompareScriptByHandle(ScriptObject a, ScriptObject b);
bool CompareScriptByName(ScriptObject a, ScriptObject b);
