/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "script.h"
#include "mod.h"
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

#include "mem_watcher_mod.h"
#include "cheats_mod.h"
#include "cutscene_mod.h"
#include "audio_mod.h"
#include "handle_helper_mod.h"
#include "scripts_mod.h"
#include "sync_scene_mod.h"
#include "player_switch_mod.h"
#include "comms_mod.h"
#include "mission_mod.h"
#include "area_mod.h"
#include "test_mod.h"
#include "lua_console_mod.h"

LRESULT __stdcall WndProc(HWND hand, UINT msg, WPARAM wParam, LPARAM lParam);

DLLObject::DLLObject()
{
	
}

DLLObject::~DLLObject()
{
	// Make sure it's unloaded
	Unload();
}

void DLLObject::InitMods()
{
	bool supportGlobals = IsVersionSupportedForGlobals(getGameVersion());

	modsLoaded.push_back(new MemWatcherMod(*this, supportGlobals));
	modsLoaded.push_back(new CheatsMod(*this, supportGlobals));
	modsLoaded.push_back(new CutsceneMod(*this, supportGlobals));
	modsLoaded.push_back(new AudioMod(*this, supportGlobals));
	modsLoaded.push_back(new ScriptsMod(*this, supportGlobals));
	modsLoaded.push_back(new HandleHelperMod(*this, supportGlobals));
	modsLoaded.push_back(new SyncSceneMod(*this, supportGlobals));
	modsLoaded.push_back(new PlayerSwitchMod(*this, supportGlobals));
	modsLoaded.push_back(new AreaMod(*this, supportGlobals));
	modsLoaded.push_back(new LuaConsoleMod(*this, supportGlobals, luaEngine));
	if (supportGlobals)
	{
		modsLoaded.push_back(new CommsMod(*this, supportGlobals));
		modsLoaded.push_back(new MissionMod(*this, supportGlobals));
	}
	//modsLoaded.push_back(new TestMod(supportGlobals));
}

void DLLObject::Update()
{
	if (isOpen)
	{
		if (floatingMenu)
			PAD::ENABLE_ALL_CONTROL_ACTIONS(0);
		else
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
	}

	toRun_mutex.lock();
	for (auto &f : toRun)
		f();
	toRun.clear();
	toRun_mutex.unlock();

	for (Mod * m : modsLoaded)
		m->Think();
}

void DLLObject::UpdateWindows()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (auto &m : modsLoaded)
	{
		if (m->HasWindow())
			ImGui::Begin(m->GetName().c_str(), nullptr, m->m_windowFlags);
		if (m->Draw() && m->HasWindow())
			ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void DLLObject::RunOnNativeThread(std::function<void()> func)
{
	toRun.push_back(func);
}

void DLLObject::SetShowAllInGame(bool show)
{
	for (auto &m : modsLoaded)
		m->SetShowInGame(show);
}

void DLLObject::SetAllFontSize(float menuSize, float contentSize, float inGameSize)
{
	for (auto &m : modsLoaded)
		m->SetFontSize(menuSize, contentSize, inGameSize);
}

void DLLObject::SetAllInGameFontColor(int red, int green, int blue)
{
	for (auto &m : modsLoaded)
		m->SetInGameFontColor(red, green, blue);
}

void DLLObject::Load()
{
	if (!isLoaded)
	{
		userSettings.Load(userSettingsFile);
		InitMods();
		for (auto &m : modsLoaded)
			m->Load();
		MISC::SET_THIS_SCRIPT_CAN_BE_PAUSED(false);
		isLoaded = true;
	}
		
	// After loading a save, ScriptHookV does not call ProcessDetach,
	// but ProcessAttach again
	while (true)
	{
		Update();
		WAIT(0);
	}
}

void DLLObject::Unload()
{
	if (isLoaded)
	{
		isOpen = false;
		for (auto &m : modsLoaded)
		{
			m->Unload();
			delete m;
		}
		modsLoaded.clear();

		// Save settings
		userSettings.Save(userSettingsFile);

		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		if (oldProc)
			SetWindowLongPtr(FindMainWindow(GetCurrentProcessId()), GWLP_WNDPROC, oldProc);
		isLoaded = false;
	}
}

void DLLObject::ToggleOpen()
{
	isOpen = !isOpen;
	ImGui::GetIO().MouseDrawCursor = isOpen;
}

void DLLObject::OnPresent(IDXGISwapChain *swap)
{
	if (!hasInitializedImgui)
	{
		hasInitializedImgui = true;
		ID3D11Device *device;
		ID3D11DeviceContext *context;

		swap->GetDevice(__uuidof(ID3D11Device), (void **)&device);
		device->GetImmediateContext(&context);

		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_NavEnableGamepad;
		ImGui::GetIO().IniFilename = fileImGuiIni.c_str();
		ImGui::GetIO().LogFilename = fileImGuiLog.c_str();

		HWND window = FindMainWindow(GetCurrentProcessId());
		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(device, context);


		oldProc = SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
	}

	if (isOpen)
		UpdateWindows();
}
