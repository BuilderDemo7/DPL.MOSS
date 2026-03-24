#pragma once
#include "Matrix.h"

class GameCamera {
public:
	Matrix m_Matrix;
	static GameCamera* GetInstance();
};