#include "CLifeNode_PlayAudio.h"

void CLifeNode_PlayAudio::CustomInitalise(int bankID, int sampleID, float volume, int flags, CLifeActor* actor, float timeOut)
{
	
	//if (CLifeEventDataManager::GetInstance() != NULL)
	//{
	//	AutoPtr<CLifeEventData, int> data = CLifeEventDataManager::GetInstance()->GetLifeEventData(0);
	//	*(CLifeEventData**)(this + 0x8) = data.m_pPointer;
	//}

	m_b3DSound = false;

	m_pActor = actor;
	m_fVolume = volume;

	m_audioClip.iBankID = bankID;
	m_audioClip.iSampleID = sampleID;

	m_fTimeout = timeOut;
	m_flags = flags;

	if (m_pActor != NULL)
		m_b3DSound = true;
}