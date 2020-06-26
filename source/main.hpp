#pragma once

#include <string>
#include <vector>
#include <GarrysMod/FactoryLoader.hpp>

#if defined DEBUG

#include <dbg.h>

#define _DebugMsg( ... ) Msg( __VA_ARGS__ )
#define _DebugWarning( ... ) ConColorMsg( 1, global::__yellow, __VA_ARGS__ )

#else

#define _DebugMsg( ... )
#define _DebugWarning( ... )

#endif

class IServer;

namespace global
{

}
