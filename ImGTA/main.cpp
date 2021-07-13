/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "script.h"

#include "main.h"

#include "imgui_impl_win32.h"

#include <Windows.h>

DLLObject object{};

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Load();
void OnPresent(IDXGISwapChain *swap);

BOOL APIENTRY DllMain(HMODULE inst, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(inst);
		scriptRegister(inst, Load);
		presentCallbackRegister((PresentCallback)OnPresent);
		break;

	case DLL_PROCESS_DETACH:
		// If unloaded dynamically
		if (lpReserved == NULL)
		{
			presentCallbackUnregister((PresentCallback)OnPresent);
			object.Unload();
			scriptUnregister(inst);
		}
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}

void Load()
{
	object.Load();
}

LRESULT __stdcall WndProc(HWND hand, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
	{
		if (wParam == VK_INSERT)
			object.ToggleOpen();
	}

	if (object.GetIsOpen())
		ImGui_ImplWin32_WndProcHandler(hand, msg, wParam, lParam);

	return CallWindowProcW((WNDPROC)object.GetOldProc(), hand, msg, wParam, lParam);
}

void OnPresent(IDXGISwapChain *swap)
{
	object.OnPresent(swap);
}
