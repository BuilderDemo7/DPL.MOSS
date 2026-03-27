#include "CFontManager.h"
#include <iostream>
#include <Windows.h>

void CFontManager::Print(AutoPtr<CPCViewport, int> piView, FontSpecs &spec, char *szFormat, ...)
{
	va_list args;
	va_start(args, szFormat);

	char mav2_buffer[24];

	((void(__stdcall*)(CFontManager*, void*, AutoPtr<CPCViewport, int>, FontSpecs&, char*, ...))0x4738d5)(this, &mav2_buffer, piView, spec, szFormat, args);

	va_end(args);
}