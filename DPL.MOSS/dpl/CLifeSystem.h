#pragma once
#include "CLifePlayer.h"

class CLifeSystem {
public:
	int field0;
	int field4;
	CLifePlayer* pPlayer;

	CLifePlayer* GetPlayer();

	void SetPopulationDensity(int type, float value);

	static CLifeSystem* GetInstance();
};