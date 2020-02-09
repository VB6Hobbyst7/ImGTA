#pragma once
#include "types.h"

class AnimDict
{
public:
    AnimDict( const char *model, bool block = true );
    ~AnimDict();

    void Unload();
    const char *GetDict();
    bool IsValid();
    void WaitForLoad();

private:
    bool m_bIsValid = false;
    bool m_bMarked = false;
    char m_szAnimDict[256] = "";
};