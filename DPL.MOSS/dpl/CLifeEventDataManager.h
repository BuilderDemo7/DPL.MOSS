#pragma once
#include "AutoPtr.h"

struct CLifeEventData
{

};

class CLifeEventDataManager {
public:
	void EndAllLifeEvents();
	static CLifeEventDataManager* GetInstance();
	AutoPtr<CLifeEventData, int> GetLifeEventData(int id);
};