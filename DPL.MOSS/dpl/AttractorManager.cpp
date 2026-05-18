#include "AttractorManager.h"

Vector4 attractor::Base::GetPosition()
{
	Vector4 returnStr = Vector4();

	((void(__thiscall*)(attractor::Base*, Vector4*))0x44df5d)(this, &returnStr);
	return returnStr;
}

AttractorManager* AttractorManager::GetInstance()
{
	return *(AttractorManager**)0x70c5dc;
}

void AttractorManager::FindAttractors(attractor::Search & searchSpec, attractor::AccessorObjectBase & result)
{
	((void(__thiscall*)(AttractorManager*, attractor::Search & searchSpec, attractor::AccessorObjectBase & result))0x413adf)(this, searchSpec, result);
}