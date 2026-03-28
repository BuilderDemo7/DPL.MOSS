#include "CLifeActor_Prop.h"
#include "CGadgetHandler.h"

void CLifeActor_Prop::CustomInitalise(Matrix matrix, EGadgetType eGadget, bool canBeTargeted, CLifeEventData* pEventData)
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

	m_propModelHandle = CGadgetHandler::GetInstance()->GetGadgetModelHandle(eGadget);
	m_bCreated = false;
	m_bCanBeTargeted = canBeTargeted;
}

void CLifeActor_Prop::Move(Matrix matrix)
{
	((void(__thiscall*)(CLifeActor_Prop*, Matrix*))0x47978f)(this, &matrix);
}

void CLifeActor_Prop::AnimateProp(float speed, bool forwards)
{
	((void(__thiscall*)(CLifeActor_Prop*, float, bool))0x479665)(this, speed, forwards);
}