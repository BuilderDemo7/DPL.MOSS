#pragma once
#include "CPlayerDriverBehaviour.h"

class CLifePlayer {
public:
	int field0;
	int field4;
	CPlayerDriverBehaviour* pDriverBehaviour;

	CPlayerDriverBehaviour* GetDriverBehaviour();
};