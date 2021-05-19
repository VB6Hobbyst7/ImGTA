#include "anim_dict.h"
#include "main.h"
#include "natives.h"

AnimDict::AnimDict(const char *dict, bool block)
{
	strcpy_s(m_animDict, dict);

	m_isValid = STREAMING::DOES_ANIM_DICT_EXIST((char *)dict);

	if (IsValid())
	{
		STREAMING::REQUEST_ANIM_DICT((char *)dict);
		if (block)
			WaitForLoad();
	}
}

AnimDict::~AnimDict()
{
	//if ( !m_bMarked )
	//    Unload();
}

void AnimDict::WaitForLoad()
{
	while (!STREAMING::HAS_ANIM_DICT_LOADED(m_animDict))
		WAIT(0);
}

bool AnimDict::IsValid()
{
	return m_isValid;
}

void AnimDict::Unload()
{
	if (m_isValid)
	{
		STREAMING::REMOVE_ANIM_DICT(m_animDict);
		m_marked = true;
	}
}

const char *AnimDict::GetDict()
{
	return m_animDict;
}