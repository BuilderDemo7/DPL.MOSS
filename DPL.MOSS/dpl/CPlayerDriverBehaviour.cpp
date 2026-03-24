#include "CPlayerDriverBehaviour.h"

CCharacter* CPlayerDriverBehaviour::GetCharacter()
{
    return *(CCharacter**)((int)this + 0x2C4);
}

void CPlayerDriverBehaviour::AquaticCollisionCheck() {
    ((void(__thiscall*)(CPlayerDriverBehaviour*))0x4a25ab)(this);
}

bool CPlayerDriverBehaviour::HasShotRecently()
{
	return ((bool(__thiscall*)(CPlayerDriverBehaviour*))0x4A2AD6)(this);
}

void CPlayerDriverBehaviour::AddAllWeapons()
{
	((void(__thiscall*)(CPlayerDriverBehaviour*))0x49F419)(this);
}

bool CPlayerDriverBehaviour::IsFreeAiming()
{
	return ((bool(__thiscall*)(CPlayerDriverBehaviour*))0x4A2B57)(this);
}

void CPlayerDriverBehaviour::PlayerIsStuck()
{
	((void(__thiscall*)(CPlayerDriverBehaviour*))0x4A2B2C)(this);
}