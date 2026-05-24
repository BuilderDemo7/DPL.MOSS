#include <iostream>
#include "CLifeProgression.h"

CLifeProgression* GetLifeProgression()
{
    return ((CLifeProgression* (__cdecl*)())0x4700B3)();
}

// If not in a mission?
bool CLifeProgression::IsShowingIcons()
{
	return *(int*)(this + 0x14) != 0 ? true : false;
}

void CLifeProgression::RepeatMission(int EventID)
{
    ((void(__thiscall*)(CLifeProgression*, int))0x47125A)(this, EventID);
}

void CLifeProgression::AutoSave()
{
	((void(__thiscall*)(CLifeProgression*))0x470b88)(this);
}

void CLifeProgression::DisableIncidentalSpooling(bool killAll)
{
	((void(__thiscall*)(CLifeProgression*, bool))0x470ab7)(this, killAll);
}

void CLifeProgression::EnableIncidentalSpooling()
{
	((void(__thiscall*)(CLifeProgression*))0x470a64)(this);
}

bool CLifeProgression::SetLifeEventStatus(int eID, int eStatus, bool fromStatusControl)
{
	return ((bool(__thiscall*)(CLifeProgression*, int, int, bool))0x47148c)(this, eID, eStatus, fromStatusControl);
}
