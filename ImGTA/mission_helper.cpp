#include "mission_helper.h"
#include "utils.h"
#include <stdexcept>
#include <map>



MissionHelper::MissionHelper( eGameVersion ver ) : m_version( ver )
{
    if ( !IsVersionSupportedForGlobals( ver ) )
        throw new std::logic_error( "Unsupported version supplied for MissionHelper" );
}

void MissionHelper::Fail()
{
    *getGlobalPtr( 0x15F6A ) = 0;
}

void MissionHelper::Skip()
{
    *getGlobalPtr( 0x14A40 ) = 1;
    *getGlobalPtr( 0xD5DC ) = 1;
    *getGlobalPtr( 0x15F6A ) = 9;
}