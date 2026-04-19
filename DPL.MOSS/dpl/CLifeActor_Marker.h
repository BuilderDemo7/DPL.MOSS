#pragma once
#include "Matrix.h"
#include "CLifeActor.h"

#pragma pack(push, 1)
class CLifeActor_Marker : CLifeActor
{
public:
	void CustomInitalise(Matrix matrix, CLifeEventData* pEventData = NULL);

	void* vtable;
	int field4;

	CLifeEventData* m_pOwner;

	int fieldC;

	Matrix m_matrix;
};
#pragma pack(pop)