#pragma once
#include <functional>

struct IDXGISwapChain;

void InitMods();
void Load();
void Unload();
void OnPresent( IDXGISwapChain *swap );

// Relying on this function is not recommended!
void RunOnNativeThread( std::function<void()> func );
void SetFloatingMenu(bool isFloating);
bool GetFloatingMenu();
void SetShowAllInGame(bool show);
void SetAllFontSize(float menuSize, float contentSize, float ingameSize);
const char * BoolToStr(bool value);