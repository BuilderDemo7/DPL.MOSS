#include "MathFuncs.h"

// MAq construct__3MAqRC4MAm4 (MAm4 * mtx)
Vector4 math_construct_quaternion(Matrix* mtx)
{
	Vector4 rtStorage = Vector4();

	return *((Vector4*(__thiscall*)(Vector4*, Matrix*))0x405a54)(&rtStorage, mtx);
}

// void __thiscall initFromQandV3__4MAm4RC3MAqG4MAv3(MAm4 *this,MAq *q,MAv3 v)
Matrix math_initFromQandV3(Vector4* q, Vector v)
{
	Matrix rtStorage = Matrix();

	((void(__thiscall*)(Matrix*, Vector4*, Vector, float))0x4098ca)(&rtStorage, q, v, 0);

	return rtStorage;
}