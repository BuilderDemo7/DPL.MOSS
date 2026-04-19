#include "CLifeActor_Marker.h"
#include "CLifeProgression.h"

void CLifeActor_Marker::CustomInitalise(Matrix matrix, CLifeEventData* pEventData)
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

	auto prog = GetLifeProgression();
	if (prog)
	{
		// for registering relocate position??
		// RegisterMarkerPosition(CLifeProgression *this,int eventID,MAm4 *mtx)
		((void(__thiscall*)(CLifeProgression*, int, Matrix*))0x470a3e)(prog, 0, &m_matrix);
	}
}