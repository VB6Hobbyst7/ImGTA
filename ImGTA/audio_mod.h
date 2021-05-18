#pragma once
#include "mod.h"
#include "types.h"

class AudioMod : public Mod
{
public:
    AudioMod(bool supportGlobals) : Mod( "Audio", true, supportGlobals )
    {
        m_iWindowFlags = ImGuiWindowFlags_MenuBar;
    }

    bool Draw() override;
    void Think() override;
    void Load() override;
    void Unload() override;

private:
    void DrawMenuBar();

    bool m_bIsRingtonePlaying = false;
    bool m_bIsCallOngoing = false;

    bool m_bIsScriptedConversationLoaded = false;
    bool m_bIsScriptedConversationOngoing = false;
    bool m_bIsInCurrentConversation = false;
    int m_iCurrentScriptedConversationLine = 0;

    bool m_bIsStreamPlaying = false;
    int m_iStreamPlayTime = 0;

    bool m_bIsScriptedMusicPlaying = false;

    bool m_bIsAmbientSpeechPlaying = false;
    bool m_bIsScriptedSpeechPlaying = false;
    bool m_bIsAnySpeechPlaying = false;

	char m_audioSceneVarName[256] = "";
	float m_audioSceneVarValue = 0;

	std::string m_audioName = "";
	std::string m_audioSource = "";
	std::string m_audio1 = "";
	std::string m_audio2 = "";


    // ImGui inputs
    bool m_bStopConversationParam = false;
    bool m_bPauseConversationParam = false;
    char m_szAudioName[256] = "";
};