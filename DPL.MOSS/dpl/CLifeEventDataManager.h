#pragma once
#include "AutoPtr.h"

class CLifeEventData
{
public:
	char __padding0[0x4c];
	unsigned short m_missionID;
};

class CLifeEventDataManager {
public:
	void EndAllLifeEvents();
	static CLifeEventDataManager* GetInstance();
	AutoPtr<CLifeEventData, int> GetLifeEventData(int id);
};