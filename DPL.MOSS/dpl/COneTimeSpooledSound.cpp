#pragma once
#include "COneTimeSpooledSound.h"

void COneTimeSpooledSound::Step()
{
	((void(__thiscall*)(COneTimeSpooledSound*))0x4e3bda)(this);
}

void COneTimeSpooledSound::Release()
{
	((void(__thiscall*)(COneTimeSpooledSound*))0x4e3c5c)(this);
}

void COneTimeSpooledSound::Stop()
{
	((void(__thiscall*)(COneTimeSpooledSound*))0x4e399a)(this);
}

void COneTimeSpooledSound::RequestBank(int bank)
{
	((void(__thiscall*)(COneTimeSpooledSound*, int bank))0x4e3b6e)(this, bank);
}

void COneTimeSpooledSound::Trigger2D(int sample, float volume)
{
	((void(__thiscall*)(COneTimeSpooledSound*, int sample, float volume))0x4e3e0c)(this, sample, volume);
}