#pragma once
#include "mod.h"
#include "types.h"
#include "utils.h"

class AreaMod : public Mod
{
public:
	AreaMod(bool supportGlobals) : Mod("Area", true, supportGlobals)
	{
		m_iWindowFlags = ImGuiWindowFlags_MenuBar;
	}

	bool Draw() override;
	void Think() override;
	void Load() override;
	void Unload() override;

private:
	void DrawMenuBar();

	Vector3 m_currentPos = InitVector3(0);
	bool m_drawInGame = true;
	float m_drawOffsetZ = 0;

	// Box
	bool m_drawBox = false;
	Vector3 m_startBoxPoint = InitVector3(0);
	Vector3 m_endBoxPoint = InitVector3(0);

	// Angled area
	bool m_angledAreaSameBox = true;
	bool m_isInAngledArea = false;
	Vector3 m_angledAreaStartPoint = InitVector3(0);
	Vector3 m_angledAreaEndPoint = InitVector3(0);
	float m_angledAreaWidth = 10;
	bool m_angledAreaDebug = false;
	bool m_angledAreaIncludeZ = true;
	int m_angledAreaUnk0 = 0;

	// Area
	bool m_areaSameBox = true;
	bool m_isInArea = false;
	Vector3 m_areaStartPoint = InitVector3(0);
	Vector3 m_areaEndPoint = InitVector3(0);
	bool m_areaUnk0 = false;
	bool m_areaUnk1 = false;
	int m_areaUnk2 = 0;

	// Coord
	bool m_isAtCoord = false;
	Vector3 m_coordPoint = InitVector3(0);
	Vector3 m_coordSize = InitVector3(1);
	bool m_coordUnk0 = false;
	bool m_coordUnk1 = true;
	int m_coordUnk2 = 0;

	// ImGui inputs / internals
	bool m_bWantsUpdate = false;
	int m_iHandleInput = 0;
	bool m_bConstantUpdate = true;
	char m_szAnimDictInput[256] = "";
	char m_szAnimNameInput[256] = "";
	unsigned int m_iAnimFlags = 0;
	bool m_bAnimLoop = false;
};

