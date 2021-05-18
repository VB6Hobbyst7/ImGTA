#include "mod.h"

Mod::Mod( std::string name, bool hasWindow, bool supportGlobals) : m_szName( name ), m_bHasWindow( hasWindow ), m_supportGlobals(supportGlobals)
{

}

bool Mod::HasWindow()
{
    return m_bHasWindow;
}

const std::string Mod::GetName()
{
    return m_szName;
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