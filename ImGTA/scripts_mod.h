#pragma once
#include "mod.h"
#include <vector>
#include <string>
#include <mutex>

class ScriptObject
{
public:
	ScriptObject(std::string name, int handle) : m_windowName(name), m_handle(handle) {}
	std::string m_windowName;
	int m_handle;
};

class ScriptsMod : public Mod
{
public:
	ScriptsMod(bool supportGlobals) : Mod("Scripts", true, supportGlobals)
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

	std::vector<ScriptObject> m_scripts;
	std::mutex m_scriptsMutex; // needed because it's accessed between native thread and render thread.

	bool m_wantsUpdate = false;
	ScriptObject *m_selected;
	unsigned int m_startFlags = 1024;
	char m_startScriptName[128] = "";
};