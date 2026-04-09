#include "MathFuncs.h"

// MAq construct__3MAqRC4MAm4 (MAm4 * mtx)
Vector4 math_construct_quaternion(Matrix* mtx)
{
	Vector4 rtStorage = Vector4();

	return *((Vector4*(__thiscall*)(Vector4*, Matrix*))0x405a54)(&rtStorage, mtx);
}