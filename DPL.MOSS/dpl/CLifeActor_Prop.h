#pragma once
#include "Matrix.h"
#include "CLifeActor.h"

class CLifeActor_Prop : CLifeActor
{
	virtual ~CLifeActor_Prop() = default;

	char __padding0[0x9];

	Matrix m_matrix;
	int m_propModelHandle;
};