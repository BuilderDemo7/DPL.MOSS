#include "LifeEnvironment.h"

void CLifeEnvironment::SetLifeTime(float NewTime)
{
    ((void(__thiscall*)(CLifeEnvironment*, float))0x46C327)(this, NewTime);
}

// SLifeTime->seconds
float* CLifeEnvironment::GetLifeTime()
{
	return (float*)((int)this + 272);
}

float* CLifeEnvironment::GetTimeRate()
{
	return (float*)((int)this + 0x118);
}

CLifeEnvironment* GetEnvironment()
{
    return *(CLifeEnvironment**)0x70C7E0;
}
