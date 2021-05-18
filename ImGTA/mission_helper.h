#pragma once
#include "main.h"

// TOOD: actually support other versions
class MissionHelper
{
public:
    MissionHelper( eGameVersion ver );

    void Fail();
    void Skip();

private:
    eGameVersion m_version;
};