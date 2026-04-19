#pragma once
#include "CPCViewport.h"
#include "AutoPtr.h"

enum EJustify {
	EJustify_Left = 0,
	EJustify_Right = 1,
	EJustify_Centered = 2,
	EJustify_SizeOf = 2147483647
};

struct FontSpecs {
	struct Vector4 colour { 1, 1, 1, 1 };
	int fontType;
	int textType;
	float x;
	float y;
	float w = 1.0f;
	float xScale = 1.0f;
	float yScale = 1.0f;
	float spacing;
	enum EJustify justify;
	unsigned int flags;
	char field11_0x38;
	char field12_0x39;
	char field13_0x3a;
	char field14_0x3b;
	char field15_0x3c;
	char field16_0x3d;
	char field17_0x3e;
	char field18_0x3f;

	FontSpecs()
	{
		colour = Vector4(1, 1, 1, 1);
		w = 1.0f;
		xScale = 1.0f;
		yScale = 1.0f;
		justify = EJustify_Left;
	}
};

class CFontManager
{
	void Print(AutoPtr<CPCViewport, int> piView, FontSpecs &spec, char *szFormat, ...);
};