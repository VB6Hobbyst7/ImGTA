#include "watch_entry.h"
#include "types.h"
#include "main.h"
#include <bitset>

void WatchEntry::UpdateValue()
{
	m_value = GetDisplayForType(m_iGlobalAddress, m_type);
}

std::string GetDisplayForType(uint64_t *globalAddr, WatchType type)
{
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
	return GetDisplayForType(getGlobalPtr(addrId), type);
}
