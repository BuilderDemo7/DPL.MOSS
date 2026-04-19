#pragma once
#include "Matrix.h"
#include "CLifeActor.h"
#include "ICamera.h"

#pragma pack(push, 1)
class CLifeActor_Camera : CLifeActor
{
public:
	void CustomInitalise(Matrix matrix, CLifeActor* attachTo = NULL, CLifeActor* lookAt = NULL, CLifeEventData* pEventData = NULL);

	char __padding[0x10];

	Matrix m_matrix;
	CLifeEventData* m_pOwner;
	int field54;
	int field58;
	CLifeActor* m_pAttachTo;
	CLifeActor* m_pLookAt;
	ICamera* m_pCamera;
};
#pragma pack(pop)