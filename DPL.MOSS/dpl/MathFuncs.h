#pragma once
#include "Matrix.h"
#include "Vector4.h"

Vector4 math_construct_quaternion(Matrix* mtx);
Matrix math_initFromQandV3(Vector4* q, Vector v);