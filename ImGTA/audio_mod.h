/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "mod.h"
#include "user_settings.h"

class AudioMod : public Mod
{
public:
	AudioMod(DLLObject & dllObject, bool supportGlobals) : Mod(dllObject, "Audio", true, supportGlobals)
	{
		m_windowFlags = ImGuiWindowFlags_MenuBar;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawMenuBar();
	CommonSettings & GetCommonSettings() override { return m_settings.common; }

	AudioSettings m_settings;
	bool m_isRingtonePlaying = false;
	bool m_isCallOngoing = false;

	bool m_isScriptedConversationLoaded = false;
	bool m_isScriptedConversationOngoing = false;
	bool m_isInCurrentConversation = false;
	int m_currentScriptedConversationLine = 0;

	bool m_isStreamPlaying = false;
	int m_streamPlayTime = 0;

	bool m_isScriptedMusicPlaying = false;

	bool m_isAmbientSpeechPlaying = false;
	bool m_isScriptedSpeechPlaying = false;
	bool m_isAnySpeechPlaying = false;

	char m_audioSceneVarName[256] = "";
	float m_audioSceneVarValue = 0;

	std::string m_audioName = "";
	std::string m_audioSource = "";
	std::string m_audio1 = "";
	std::string m_audio2 = "";

	// ImGui inputs
	bool m_stopConversationParam = false;
	bool m_pauseConversationParam = false;
};