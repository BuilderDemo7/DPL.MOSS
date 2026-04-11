#include "CLifeNode.h"

int CLifeNode::GetVTableAddress()
{
	return *(int*)(this);
}

void CLifeNode::OnEnable(bool* enabled, eNodeFireWire* wireToFire)
{
	((void(__thiscall*)(CLifeNode*, bool*, eNodeFireWire*))*(int*)(GetVTableAddress() + 0x34))(this, enabled, wireToFire);
}

void CLifeNode::OnDisable()
{
	((void(__thiscall*)(CLifeNode*))*(int*)(GetVTableAddress() + 0x38))(this);
}