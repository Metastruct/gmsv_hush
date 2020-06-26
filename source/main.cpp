#include "main.hpp"

#include <unistd.h>
#include <sys/mman.h>
#include <GarrysMod/Lua/Interface.h>
#include <scanning/symbolfinder.hpp>
#include <string.h>
namespace global
{


	static const std::string bad_message_1 = "CreateFragmentsFromFile: '%s' doesn't exist.";


	SourceSDK::ModuleLoader engine( "engine" );
	IServer *server = nullptr;

	static void Initialize( GarrysMod::Lua::ILuaBase *LUA )
	{
		SymbolFinder symfinder;
		if (!engine.IsValid( )) return;


		void *patt = symfinder.FindPattern(
			engine.GetModule( ),
			reinterpret_cast<const uint8_t *>(bad_message_1.c_str( )),
			bad_message_1.length()
		);
		if( patt == nullptr ) return;

		
		size_t pagesize = sysconf(_SC_PAGESIZE);
		
		uintptr_t start = (uintptr_t) patt;
		uintptr_t end = start + bad_message_1.length();
		

		uintptr_t pagestart = start & -pagesize;

		if (mprotect((void *) pagestart, end - pagestart,
            PROT_READ | PROT_WRITE | PROT_EXEC)) {
			perror("mprotect");
			return;
		}
		
		char *buff = (char*)patt;
		buff[0] = '\0';
		printf("HUSH Patched!\n");
	}

	static void Deinitialize( GarrysMod::Lua::ILuaBase *LUA )
	{
	}
}

GMOD_MODULE_OPEN( )
{
	global::Initialize( LUA );
	return 0;
}

GMOD_MODULE_CLOSE( )
{
	global::Deinitialize( LUA );
	return 0;
}
