#pragma once
#include "Matrix.h"
#include "CLifeActor.h"
#include "EGadgetType.h"

#pragma pack(push, 1)
class CLifeActor_Train : CLifeActor
{
public:
	void CustomInitalise(Matrix matrix, int track, CLifeEventData* pEventData = NULL);

	char __padding0[0x20];

	Matrix m_matrix;
	CLifeEventData* m_pOwner;
	int field64;
	int m_propModelHandle; // 32 bits model handle

	char __padding0[0x24];

	float m_direction;
	int m_track;
};
#pragma pack(pop)