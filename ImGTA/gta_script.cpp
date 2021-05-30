/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "gta_script.h"
#include "natives.h"

GTAScript::GTAScript(const char *scriptName, bool block)
{
	strcpy_s(m_scriptName, scriptName);
	m_isValid = SCRIPT::DOES_SCRIPT_EXIST(m_scriptName);

	if (IsValid())
	{
		SCRIPT::REQUEST_SCRIPT(m_scriptName);
		if (block)
			WaitForLoad();
	}
}

GTAScript::~GTAScript()
{
	if (!m_marked)
		Unload();
}

void GTAScript::WaitForLoad()
{
	while (!SCRIPT::HAS_SCRIPT_LOADED(m_scriptName))
		WAIT(0);
}

bool GTAScript::IsValid()
{
	return m_isValid;
}

void GTAScript::Unload()
{
	if (IsValid())
	{
		SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED(m_scriptName);
		m_marked = true;
	}
}

const char *GTAScript::GetScriptName()
{
	return m_scriptName;
}
