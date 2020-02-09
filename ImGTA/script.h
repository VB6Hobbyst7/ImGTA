#pragma once
#include <functional>

struct IDXGISwapChain;

void Load();
void Unload();
void OnPresent( IDXGISwapChain *swap );

// Relying on this function is not recommended!
void RunOnNativeThread( std::function<void()> func );