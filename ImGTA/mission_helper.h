#pragma once
#include "main.h"

// TOOD: actually support other versions
class MissionHelper
{
public:
    static bool IsVersionSupported( eGameVersion ver );

    MissionHelper( eGameVersion ver );

    void Fail();
    void Skip();

private:
    eGameVersion m_version;
};