#include "watch_entry.h"
#include "types.h"
#include <bitset>

std::string GetDisplayForType( uint64_t *addr, WatchType type )
{
    char buf[256] = "";

    switch ( type )
    {
        case WatchType::kInt:
            sprintf_s( buf, "%d", *( int * )addr );
            break;
        case WatchType::kFloat:
            sprintf_s( buf, "%.4f", *( float * )addr );
            break;
        case WatchType::kVector:
            Vector3 vec = *( Vector3 * )addr;
            sprintf_s( buf, "(%.4f, %.4f, %.4f)", vec.x, vec.y, vec.z );
            break;
        case WatchType::kString:
            sprintf_s( buf, "\"%s\"", ( char * )addr );
            break;
        case WatchType::kBitfield:
            sprintf_s( buf, "%s", std::bitset<32>( *addr ).to_string().c_str() );
    }

    return std::string( buf );
}