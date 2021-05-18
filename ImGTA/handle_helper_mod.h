#pragma once
#include <mutex>

#include "mod.h"
#include "types.h"

class HandleHelperMod : public Mod
{
public:
    HandleHelperMod() : Mod( "Handle Helper", true )
    {
        m_iWindowFlags = ImGuiWindowFlags_MenuBar;
    }

    bool Draw() override;
    void Think() override;
    void Load() override;
    void Unload() override;

private:
    void DrawMenuBar();
    void UpdateHandleData( bool once = false );
	void ResetData();
	void ListPeds();
	void ListVehs();

    int m_iType = 0;
    int m_iHealth = 0;
    int m_iMaxHealth = 0;
	bool m_bInjured = false;
    Hash m_modelHash = 0;
	Vector3 m_position = { 0, 0, 0 };
    bool m_bIsMissionEntity = false;
	std::mutex m_pedListMutex;
	std::mutex m_vehListMutex;
	std::string m_pedList = "";
	std::string m_vehList = "";

	int m_iNearbyObjectMax = 30;
	int m_iDrawOffsetZ = 0;
	bool m_drawEntityInfo = true;
	bool m_bDrawID = true;
	bool m_bDrawLife = true;

    // ImGui inputs / internals
    bool m_bWantsUpdate = false;
    int m_iHandleInput = 0;
    bool m_bConstantUpdate = true;
    char m_szAnimDictInput[256] = "";
    char m_szAnimNameInput[256] = "";
    unsigned int m_iAnimFlags = 0;
    bool m_bAnimLoop = false;
};