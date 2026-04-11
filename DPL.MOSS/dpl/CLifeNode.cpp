#include "CLifeNode.h"

int CLifeNode::GetVTableAddress()
{
	return *(int*)(this);
}

void CLifeNode::OnEnable(bool* enabled, eNodeFireWire* wireToFire)
{
	// DEBUG
	int addr1 = GetVTableAddress();
	int fptr = *(int*)(addr1 + 0x34);
	((void(__thiscall*)(CLifeNode*, bool*, eNodeFireWire*))fptr)(this, enabled, wireToFire);
}

void CLifeNode::OnDisable()
{
	((void(__thiscall*)(CLifeNode*))*(int*)(GetVTableAddress() + 0x38))(this);
}