#pragma once
#include "Matrix.h"
#include "CLifeActor.h"
#include "SPrimitiveData.h"

#pragma pack(push, 1)
class CLifeActor_TestVolume : CLifeActor
{
public:
	void CustomInitalise(Matrix matrix, SPrimitiveData data, CLifeActor* actorRef = NULL, CLifeEventData* pEventData = NULL);

	void* vtable;
	
	void* m_piZone;
	CLifeActor* m_pActorRef;
	int fieldC;

	CLifeEventData* m_pOwner;
};
#pragma pack(pop)