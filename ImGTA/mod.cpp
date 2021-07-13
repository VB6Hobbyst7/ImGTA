/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "mod.h"

#include "script.h"
#include "utils.h"
#include "user_settings.h"

Mod::Mod(DLLObject & dllObject, std::string name, bool hasWindow, bool supportGlobals) :
	m_dllObject(dllObject),
	m_windowName(name),
	m_hasWindow(hasWindow),
	m_supportGlobals(supportGlobals),
	m_textDrawMaxWarning(false)
{

}

bool Mod::HasWindow()
{
	return m_hasWindow;
}

const std::string Mod::GetName()
{
	return m_windowName;
}

void Mod::SetWindowCollapsed(bool collapse)
{
	ImGui::SetWindowCollapsed(m_windowName.c_str(), collapse, ImGuiCond_None);
}

void Mod::SetPauseMenuOn(bool on)
{
	m_pauseMenuOn = on;
}

void Mod::SetShowInGame(bool show)
{
	GetCommonSettings().showInGame = show;
}

void Mod::SetFontSize(float menuSize, float contentSize, float inGameSize)
{
	GetCommonSettings().menuFontSize = menuSize;
	GetCommonSettings().contentFontSize = contentSize;
	GetCommonSettings().inGameFontSize = inGameSize;
}

void Mod::SetInGameFontColor(int red, int green, int blue)
{
	GetCommonSettings().inGameFontRed = red;
	GetCommonSettings().inGameFontGreen = green;
	GetCommonSettings().inGameFontBlue = blue;
}

void Mod::SetInGameOffsets(float x, float y)
{
	GetCommonSettings().inGameOffsetX = x;
	GetCommonSettings().inGameOffsetY = y;
}

void Mod::SetTextDrawMaxWarning(bool toggle)
{
	m_textDrawMaxWarning = toggle;
}

void Mod::DrawCommonSettingsMenus(CommonSettings & common)
{
	if (ImGui::BeginMenu("Font size"))
	{
		if (ImGui::InputFloat("Menu Font size", &common.menuFontSize, 0.1f))
			ClipFloat(common.menuFontSize, 0.6f, 2.0f);

		if (ImGui::InputFloat("Content Font size", &common.contentFontSize, 0.1f))
			ClipFloat(common.contentFontSize, 0.3f, 3.0f);

		if (ImGui::InputFloat("In-game Font size", &common.inGameFontSize, 0.1f))
			ClipFloat(common.inGameFontSize, 0.1f, 3.0f);

		if (ImGui::InputFloat("Column spacing", &common.columnSpacing, 0.02f))
			ClipFloat(common.columnSpacing, 0.02f, 0.5f);

		if (ImGui::Button("Reset"))
		{
			common.menuFontSize = 1.0f;
			common.contentFontSize = 1.0f;
			common.inGameFontSize = 0.3f;
		}

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Font color"))
	{
		if (ImGui::InputInt("Red", &common.inGameFontRed))
			ClipInt(common.inGameFontRed, 0, 255);

		if (ImGui::InputInt("Green", &common.inGameFontGreen))
			ClipInt(common.inGameFontGreen, 0, 255);

		if (ImGui::InputInt("Blue", &common.inGameFontBlue))
			ClipInt(common.inGameFontBlue, 0, 255);

		if (ImGui::Button("Reset"))
		{
			common.inGameFontRed = 255;
			common.inGameFontGreen = 255;
			common.inGameFontBlue = 255;
		}

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Offsets"))
	{
		if (ImGui::InputFloat("X Offset", &common.inGameOffsetX, 0.01f))
			ClipFloat(common.inGameOffsetX, -0.2f, 1.2f);


		if (ImGui::InputFloat("Y Offset", &common.inGameOffsetY, 0.01f))
			ClipFloat(common.inGameOffsetY, -0.2f, 1.2f);

		ImGui::EndMenu();
	}
}