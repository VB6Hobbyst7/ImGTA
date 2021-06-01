/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "mod.h"
#include "script.h"
#include "user_settings.h"

Mod::Mod(DLLObject & dllObject, std::string name, bool hasWindow, bool supportGlobals) :
	m_dllObject(dllObject),
	m_windowName(name),
	m_hasWindow(hasWindow),
	m_supportGlobals(supportGlobals),
	m_textDrawMaxWarning(false)
{

}

void Mod::CommonLoad()
{
	m_commonSettings = m_dllObject.GetUserSettings().common;
}

void Mod::CommonUnload()
{
	m_dllObject.GetUserSettings().common = m_commonSettings;
}

bool Mod::HasWindow()
{
	return m_hasWindow;
}

const std::string Mod::GetName()
{
	return m_windowName;
}

void Mod::SetFontSize(float menuSize, float contentSize, float inGameSize)
{
	m_commonSettings.menuFontSize = menuSize;
	m_commonSettings.contentFontSize = contentSize;
	m_commonSettings.inGameFontSize = inGameSize;
}

void Mod::SetInGameFontColor(int red, int green, int blue)
{
	m_commonSettings.inGameFontRed = red;
	m_commonSettings.inGameFontGreen = green;
	m_commonSettings.inGameFontBlue = blue;
}

void Mod::SetShowInGame(bool show)
{
	m_commonSettings.showInGame = show;
}

void Mod::SetTextDrawMaxWarning(bool toggle)
{
	m_textDrawMaxWarning = toggle;
}
