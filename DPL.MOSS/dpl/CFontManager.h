#pragma once
#include "CPCViewport.h"
#include "AutoPtr.h"

enum EJustify {
	EJustify_Left = 0,
	EJustify_Right = 1,
	EJustify_Centered = 2,
	EJustify_SizeOf = 2147483647
};

#pragma pack(push, 1)
struct FontSpecs { // size: 0x38
	Vector4 colour;
	//int fontType; // only exists in PS2 prototype, why did they remove it?
	int textType; // 2 = ANSI(UTF16), gotta find out the rest ...
	int unknown1;
	float x; // offset: 0x18
	float y;
	float w;
	float xScale;
	float yScale;
	float spacing;
	enum EJustify justify; // offset: 0x2C
	unsigned int flags; // 2 = custom string

	FontSpecs()
	{
		colour = Vector4(1, 1, 1, 1);
		//fontType = 0;
		textType = 0;
		x = 0;
		y = 0;
		w = -1.0f;
		xScale = -1.0f;
		yScale = 1.0f;
		spacing = 1.0f;
		justify = EJustify_Centered;
		flags = 0;
		unknown1 = 0;
	}
};
#pragma pack(pop)

class CFontManager
{
public:
	static CFontManager* GetInstance();

	void Print(AutoPtr<CPCViewport, int> piView, FontSpecs &spec, wchar_t *szFormat, ...);
};