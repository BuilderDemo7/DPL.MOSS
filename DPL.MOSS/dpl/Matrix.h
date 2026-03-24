#pragma once
#include "Vector.h"

class Matrix {
public:
	union {
		struct {
			Vector right;
			float pad;
			Vector up;
			float _pad;
			Vector forward;
			float __pad;
			Vector pos;
			float ___pad;
		};
		struct
		{
			float M[4][4];
		};
	};
	Matrix();
};

//#pragma once
//#include "Vector4.h"
//
//class Matrix {
//public:
//	union {
//		struct {
//			Vector4 right;
//			Vector4 up;
//			Vector4 forward;
//			Vector4 pos;
//		};
//		struct
//		{
//			float M[4][4];
//		};
//	};
//	Matrix();
//	Matrix(Vector4 setright, Vector4 setup, Vector4 setforward, Vector4 setpos) {
//		right = setright;
//		up = setup;
//		forward = setforward;
//		pos = setpos;
//	}
//};