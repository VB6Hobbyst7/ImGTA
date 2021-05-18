#pragma once
#include <string>
#include "imgui.h"

class Mod
{
public:
    Mod( std::string name, bool hasWindow, bool supportGlobals);
    bool HasWindow();
    const std::string GetName();

    virtual void Load() = 0;
    virtual void Unload() = 0;
    virtual void Think() = 0;
    // Draws in an ImGui window, already created. Return false to NOT automatically end the window.
    virtual bool Draw() = 0;

	void SetFontSize(float menuSize, float contentSize, float ingameSize);
	void SetShowInGame(bool show);

    ImGuiWindowFlags m_iWindowFlags;
protected:
    std::string m_szName;
    bool m_bHasWindow;
	bool m_supportGlobals;

	bool m_showInGame = true;
	float m_menuFontSize = 1.0f;
	float m_contentFontSize = 1.0f;
	float m_inGameFontSize = 0.3f;
};