/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "watch_entry.h"
#include "types.h"
#include "main.h"
#include "utils.h"
#include <bitset>

void WatchEntry::UpdateValue()
{
	if (IsGlobal())
		m_value = GetDisplayForType(m_addressIndex, m_type);
	else if(m_scriptRunning)
		m_value = GetDisplayForType(m_addressIndex, m_scriptHash, m_type);
}

void WatchEntry::UpdateValue(int scriptHash)
{
	m_value = GetDisplayForType(scriptHash, m_addressIndex, m_type);
}

std::string GetDisplayForType(uint64_t *globalAddr, WatchType type)
{
	if (globalAddr == nullptr)
		return std::string("NULL");

	char buf[256] = "";

	switch (type)
	{
	case WatchType::kInt:
		sprintf_s(buf, "%d", *(int *)globalAddr);
		break;
	case WatchType::kFloat:
		sprintf_s(buf, "%.4f", *(float *)globalAddr);
		break;
	case WatchType::kVector3:
		Vector3 vec = *(Vector3 *)globalAddr;
		sprintf_s(buf, "(%.4f, %.4f, %.4f)", vec.x, vec.y, vec.z);
		break;
	case WatchType::kString:
		sprintf_s(buf, "\"%s\"", (char *)globalAddr);
		break;
	case WatchType::kBitfield:
		sprintf_s(buf, "%s", std::bitset<32>(*globalAddr).to_string().c_str());
	}

	return std::string(buf);
}

std::string GetDisplayForType(int addrId, WatchType type)
{
	return GetDisplayForType(GetGlobalPtr(addrId), type);
}

std::string GetDisplayForType(int addrId, int scriptHash, WatchType type)
{
	return GetDisplayForType(GetThreadAddress(addrId, scriptHash), type);
}
