#include "InGameMovie.h"

CInGameMovie* GetInGameMovie()
{
	return *(CInGameMovie**)0x70C790;
}

void CInGameMovie::PlayMovie(const char* szFileName, bool loop, bool pauseAtEnd)
{
	((void* (__thiscall*)(CInGameMovie*, const char*, bool, bool))0x4BCF65)(this, szFileName, loop, pauseAtEnd);
}