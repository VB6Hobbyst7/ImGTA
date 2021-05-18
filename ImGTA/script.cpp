#include "script.h"
#include "mod.h"
#include "main.h"
#include "utils.h"
#include "natives.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include <d3d11.h>
#include <vector>
#include <mutex>
#include <cstdio>
#include <iostream>

#include "global_watch_mod.h"
#include "cheats_mod.h"
#include "cutscene_mod.h"
#include "audio_mod.h"
#include "handle_helper_mod.h"
#include "scripts_mod.h"
#include "sync_scene_mod.h"
#include "player_switch_mod.h"
#include "mission_mod.h"
#include "area_mod.h"
#include "test_mod.h"
#include "lua_console_mod.h"
#include "lua_engine.h"

std::vector<Mod *> modsLoaded;
bool hasInitializedImgui;
LONG_PTR oldProc;
bool isOpen = false;
bool isFirstLoad = true;
bool floatingMenu = true;
bool checkFirstUpdate = false;
float menuFontSize;
float contentFontSize;
float inGameFontSize;

std::vector<std::function<void()>> toRun;
std::mutex toRun_mutex;

void InitMods() {
	InitLuaEngine();

	modsLoaded.push_back(new GlobalWatchMod());
	modsLoaded.push_back(new CheatsMod());
	modsLoaded.push_back(new CutsceneMod());
	modsLoaded.push_back(new AudioMod());
	modsLoaded.push_back(new ScriptsMod());
	modsLoaded.push_back(new HandleHelperMod());
	modsLoaded.push_back(new SyncSceneMod());
	modsLoaded.push_back(new PlayerSwitchMod());
	modsLoaded.push_back(new MissionMod());
	modsLoaded.push_back(new AreaMod());
	//modsLoaded.push_back(new TestMod());
	modsLoaded.push_back(new LuaConsoleMod());
}
void Update()
{
	/*if (isOpen) {
		if (floatingMenu)
			PAD::ENABLE_ALL_CONTROL_ACTIONS(0);
		else
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
	}
	else
			PAD::ENABLE_ALL_CONTROL_ACTIONS(0);*/

    toRun_mutex.lock();
    for ( auto &f : toRun )
        f();
    toRun.clear();
    toRun_mutex.unlock();

    for ( auto &m : modsLoaded )
        m->Think();
}

void UpdateWindows()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for ( auto &m : modsLoaded )
    {
        if ( m->HasWindow() )
            ImGui::Begin( m->GetName().c_str(), nullptr, m->m_iWindowFlags );
        if ( m->Draw() && m->HasWindow() )
            ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData() );
	if (!checkFirstUpdate)
		checkFirstUpdate = true;
}

void Load()
{
	if (isFirstLoad)
	{
		InitMods();
		for (auto &m : modsLoaded)
			m->Load();
		MISC::SET_THIS_SCRIPT_CAN_BE_PAUSED( false );
		isFirstLoad = false;
	}

    while ( true )
    {
        Update();
        WAIT( 0 );
    }
   
}

void Unload()
{
	isOpen = false;
    for ( auto &m : modsLoaded )
    {
        m->Unload();
        delete m;
    }

    modsLoaded.clear();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    if ( oldProc )
        SetWindowLongPtr( find_main_window( GetCurrentProcessId() ), GWLP_WNDPROC, oldProc );
}

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
LRESULT __stdcall WndProc(HWND hand, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
	{
		if (wParam == VK_INSERT)
		{
			isOpen = !isOpen;
			ImGui::GetIO().MouseDrawCursor = isOpen;
		}
	}

	if (isOpen)
		ImGui_ImplWin32_WndProcHandler(hand, msg, wParam, lParam);
	
    return CallWindowProcW( ( WNDPROC )oldProc, hand, msg, wParam, lParam );
}

void OnPresent( IDXGISwapChain *swap )
{
    if ( !hasInitializedImgui )
    {
        hasInitializedImgui = true;
        ID3D11Device *device;
        ID3D11DeviceContext *context;

        swap->GetDevice( __uuidof( ID3D11Device ), ( void ** )&device );
        device->GetImmediateContext( &context );

        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        HWND window = find_main_window( GetCurrentProcessId() );
        ImGui_ImplWin32_Init( window );
        ImGui_ImplDX11_Init( device, context );

        ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_NavEnableGamepad;

        oldProc = SetWindowLongPtr( window, GWLP_WNDPROC, ( LONG_PTR )WndProc );
    }

    if ( isOpen )
        UpdateWindows();
}

void RunOnNativeThread( std::function<void()> func )
{
    toRun.push_back( func );
}

void SetFloatingMenu(bool isFloating)
{
	floatingMenu = isFloating;
}

bool GetFloatingMenu()
{
	return floatingMenu;
}

void SetShowAllInGame(bool show)
{
	for (auto &m : modsLoaded)
		m->SetShowInGame(show);
}


void SetAllFontSize(float menuSize, float contentSize, float inGameSize)
{
	menuFontSize = menuSize;
	contentFontSize = contentSize;
	inGameFontSize = inGameSize;
	for (auto &m : modsLoaded)
		m->SetFontSize(menuSize, contentSize, inGameSize);
}
