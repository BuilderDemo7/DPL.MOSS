#pragma once
#include "Matrix.h"
#include "CLifeActor.h"
#include "EGadgetType.h"

#pragma pack(push, 1)
class CLifeActor_Prop : CLifeActor
{
public:
	void CustomInitalise(Matrix matrix, EGadgetType eGadget, bool canBeTargeted = false, CLifeEventData* pEventData = NULL);

	void Move(Matrix matrix);
	void AnimateProp(float speed, bool forwards);

	char __padding0[0x10];

	Matrix m_matrix;
	int m_propModelHandle; // 16 bits model handle

	char __padding1[0x10];

	CLifeEventData* m_pOwner;
	long m_uid;
	int field70;
	bool m_bCanBeTargeted;
	bool field75;
	bool m_bCreated;
};
#pragma pack(pop)