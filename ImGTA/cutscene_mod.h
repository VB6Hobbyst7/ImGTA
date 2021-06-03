/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "mod.h"
#include "types.h"
#include "user_settings.h"

class CutsceneMod : public Mod
{
public:
	CutsceneMod(DLLObject & dllObject, bool supportGlobals) : Mod(dllObject, "Cutscene", true, supportGlobals)
	{
		m_windowFlags = ImGuiWindowFlags_MenuBar;
		m_startPos.x = 0;
		m_startPos.y = 0;
		m_startPos.z = 0;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawMenuBar();
	CommonSettings & GetCommonSettings() override { return m_settings.common; }

	CutsceneSettings m_settings;
	char m_requestedCutscene[256] = "";
	bool m_hasCutsceneLoaded = false;
	bool m_hasCutsceneFinished = false;
	bool m_wasCutsceneSkipped = false;
	bool m_isCutscenePlaying = false;
	bool m_isCutsceneActive = false;

	bool m_canRequestAssetsForCutsceneEntity = false;
	bool m_hasCutsceneCutThisFrame = false;

	int m_cutsceneId = 0;
	int m_cutsceneTime = 0;
	int m_cutsceneTotalDuration = 0;
	int m_cutsceneSectionPlaying = 0;
	int m_threadId = 0;
	int m_loadedCutsceneId = -1;

	char m_audioVariableName[256] = "INOUT";
	float m_audioVariableValue = 0;

	int m_param0 = 0;
	int m_param1 = 0;

	// ImGui inputs
	unsigned int m_cutsceneRequestFlags = 8;
	unsigned int m_cutsceneStartFlags = 0;
	char m_cutsceneInput[256] = "";

	Vector3 m_startPos;
};