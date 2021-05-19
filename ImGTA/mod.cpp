#include "mod.h"

Mod::Mod(std::string name, bool hasWindow, bool supportGlobals) : m_windowName(name), m_hasWindow(hasWindow), m_supportGlobals(supportGlobals)
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

void Mod::SetFontSize(float menuSize, float contentSize, float inGameSize)
{
	m_menuFontSize = menuSize;
	m_contentFontSize = contentSize;
	m_inGameFontSize = inGameSize;
}

void Mod::SetShowInGame(bool show)
{
	m_showInGame = show;
}