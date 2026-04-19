#include "CLifeActor_Camera.h"

void CLifeActor_Camera::CustomInitalise(Matrix matrix, CLifeActor* attachTo, CLifeActor* lookAt, CLifeEventData* pEventData)
{
	CLifeEventData* pActualEventData = pEventData;

	if (pActualEventData == NULL)
	{
		AutoPtr<CLifeEventData, int> data = CLifeEventDataManager::GetInstance()->GetLifeEventData(0);

		// 'data' only stored once in the stack, also we have to do this 
		pActualEventData = data.m_pPointer;
	}

	m_pOwner = pActualEventData;
	m_matrix = matrix;

	m_pAttachTo = attachTo;
	m_pLookAt = lookAt;
}