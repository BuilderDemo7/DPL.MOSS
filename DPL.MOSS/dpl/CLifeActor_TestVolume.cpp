#include "CLifeActor_TestVolume.h"
#include "Factory.h"

void CLifeActor_TestVolume::CustomInitalise(Matrix matrix, SPrimitiveData data, CLifeActor* actorRef, CLifeEventData* pEventData)
{
	CLifeEventData* pActualEventData = pEventData;

	if (pActualEventData == NULL)
	{
		AutoPtr<CLifeEventData, int> data = CLifeEventDataManager::GetInstance()->GetLifeEventData(0);

		// 'data' only stored once in the stack, also we have to do this 
		pActualEventData = data.m_pPointer;
	}

	m_pOwner = pActualEventData;
	m_pActorRef = NULL; // default

	m_pActorRef = actorRef;
	void* zone = hamster::CreateObject(EFactoryType_LifeInstance_Volume);

	float rotation = 0.0f;

	// 8 params
	// Initialise__20CLifeInstance_VolumeRC4MAm4ffffUiGQ27hamstert8CAutoPtr2Z10ILifeActorZi(CLifeInstance_Volume *this,MAm4* matrix,float widthOrRadius, float height, float length, float rotation, uint32 type, CAutoPtr<> pAttachedTo)
	int vaddr = *(int*)zone;
	int addr = *(int*)(vaddr + 0x14);

	void* m_pReturnStorage = NULL;

	((void*(__thiscall*)(void*, void**, Matrix*, float, float, float, float, unsigned int, CLifeActor*))addr)(zone, &m_pReturnStorage, &matrix, data.fWidthOrRadius, data.fHeight, data.fLength, rotation, data.eType, m_pActorRef);

	m_piZone = zone;
}