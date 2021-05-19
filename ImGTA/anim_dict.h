#pragma once
#include "types.h"

class AnimDict
{
public:
	AnimDict(const char *model, bool block = true);
	~AnimDict();

	void Unload();
	const char *GetDict();
	bool IsValid();
	void WaitForLoad();

private:
	bool m_isValid = false;
	bool m_marked = false;
	char m_animDict[256] = "";
};