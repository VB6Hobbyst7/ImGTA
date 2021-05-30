/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include <string>
#include "imgui.h"
#include "user_settings.h"

class DLLObject;

class Mod
{
public:
	Mod(DLLObject & dllObject, std::string name, bool hasWindow, bool supportGlobals);
	virtual ~Mod(){}
	bool HasWindow();
	const std::string GetName();

	void CommonLoad();
	void CommonUnload();
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Think() = 0;
	// Draws in an ImGui window, already created. Return false to NOT automatically end the window.
	virtual bool Draw() = 0;

	void SetFontSize(float menuSize, float contentSize, float ingameSize);
	void SetInGameFontColor(int red, int green, int blue);
	void SetShowInGame(bool show);

	ImGuiWindowFlags m_windowFlags;

protected:
	CommonSettings m_commonSettings;
	DLLObject & m_dllObject;
	std::string m_windowName;
	bool m_hasWindow;
	bool m_supportGlobals;

	const float m_inputIDWidgetWidth = 150.0f;
};