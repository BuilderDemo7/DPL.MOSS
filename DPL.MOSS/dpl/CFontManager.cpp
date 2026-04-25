#include "CFontManager.h"
#include <iostream>
#include <Windows.h>

CFontManager* CFontManager::GetInstance()
{
	return *(CFontManager**)0x70c540;
}

// signature speculation, which was f@#$ed up by Visual Studio 2005 or something...
// __stdcall MAv2 Print__12CFontManagerGQ27hamstert8CAutoPtr2Z9IViewportZiRC9FontSpecsPCUse(CFontManager *manager, MAv2 *retStorage, CPCViewport *piView, FontSpecs *spec, char *szFormat, va_list args, ...)
void __cdecl CFontManager::Print(AutoPtr<CPCViewport, int> piView, FontSpecs &spec, char *szFormat, ...)
{
	//char args_buffer[24];
	//memset(&args_buffer, 0, 24);

	va_list args; //= (char*)&args_buffer;
	va_start(args, szFormat);

	char mav2_buffer[24];
	memset(&mav2_buffer, 0, 24);

	((void(__cdecl*)(CFontManager*, void*, AutoPtr<CPCViewport, int>, FontSpecs*, char*, va_list))0x56ddef)(this, &mav2_buffer, piView, &spec, szFormat, args);

	/*
	_asm
	{
		  mov         eax, dword ptr[args]
		  push        eax
		  mov         ecx, dword ptr[szFormat]
		  push        ecx
		  mov         edx, dword ptr[spec]
		  push        edx
		  mov         eax, dword ptr[piView]
		  push        eax
		  lea         ecx, [mav2_buffer]
		  push        ecx
		  mov         edx, dword ptr[this]
		  push        edx
		  mov         eax, 0x56DDEF
		  call        eax
		  add         esp, 0x18
	}
	*/

	va_end(args);
}