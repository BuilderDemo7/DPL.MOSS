#pragma once
#include "CLifePlayer.h"
#include "CLifeActor.h"

class CLifeSystem {
public:
	int field0;
	int field4;
	CLifePlayer* pPlayer;
	int m_iPlayerIsDeadTimer;

	// SPingRadii m_radii
	float fIn;
	float fOut;

	int m_lifeTimeClicks;
	CLifeActor* m_pPlayerActor;

	CLifePlayer* GetPlayer();
	void RegisterPlayerActor(CLifeActor* pActor);
	void SetSpoolCentre(float x, float z);

	void SetPopulationDensity(int type, float value);

	static CLifeSystem* GetInstance();
};