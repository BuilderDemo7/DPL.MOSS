#include "Factory.h"

namespace hamster
{
	void* CreateObject(EFactoryType eType)
	{
		return ((void*(__fastcall*)(EFactoryType))0x483a3d)(eType);
	}
}