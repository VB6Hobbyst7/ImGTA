/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "enums.h"

#include "imgui.h"

#include <string>

class DLLObject;
struct CommonSettings;

class Mod
{
public:
	Mod(DLLObject & dllObject, std::string name, bool hasWindow, bool supportGlobals);
	virtual ~Mod(){}
	bool HasWindow();
	const std::string GetName();

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Think() = 0;
	// Draws in an ImGui window, already created. Return false to NOT automatically end the window.
	virtual bool Draw() = 0;

	void SetWindowCollapsed(bool collapse);
	void SetPauseMenuOn(bool on);
	void SetShowInGame(bool show);
	void SetFontSize(float menuSize, float contentSize, float ingameSize);
	void SetInGameFontColor(int red, int green, int blue);
	void SetInGameOffsets(float x, float y);
	void SetTextDrawMaxWarning(bool toggle);

	ImGuiWindowFlags m_windowFlags;

protected:
	virtual CommonSettings & GetCommonSettings() = 0;
	void DrawCommonSettingsMenus(CommonSettings & common);

	DLLObject & m_dllObject;
	std::string m_windowName;
	bool m_enableHUD;
	bool m_hasWindow;
	bool m_pauseMenuOn;
	bool m_supportGlobals;
	bool m_textDrawMaxWarning;

	const eFont m_font = eFont::FontChaletLondon;
	const float m_inputIDWidgetWidth = 150.0f;
};