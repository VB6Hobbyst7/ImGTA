#pragma once
#include "types.h"

class GTAScript
{
public:
	GTAScript(const char *scriptName, bool block = true);
	~GTAScript();

	void Unload();
	const char *GetScriptName();
	bool IsValid();
	void WaitForLoad();

private:
	bool m_isValid = false;
	bool m_marked = false;
	char m_scriptName[128] = "";
};