#include "CLifeEventDataManager.h"

void CLifeEventDataManager::EndAllLifeEvents() {
	((void(__thiscall*)(CLifeEventDataManager*))0x0046e288)(this);
}

CLifeEventDataManager* CLifeEventDataManager::GetInstance() {
	return *(CLifeEventDataManager**)0x0070C7C8;
}

AutoPtr<CLifeEventData, int> CLifeEventDataManager::GetLifeEventData(int id)
{
	AutoPtr<CLifeEventData, int> pData;

	((void(__thiscall*)(CLifeEventDataManager*, AutoPtr<CLifeEventData, int>*, int))0x46e3de)(this, &pData, id);
	return pData;
}