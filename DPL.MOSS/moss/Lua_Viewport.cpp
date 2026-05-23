#include "Lua_Viewport.h"
#include "..\dpl\MathFuncs.h"

const char* g_ViewportMetaName = "Viewport";

void Init_Lua_MetaTable_Viewport()
{
	luaL_newmetatable(L, g_ViewportMetaName);

	// set __index
	lua_pushcfunction(L, lua_ViewportIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_ViewportIndex(lua_State* L)
{
	CPCViewport* vp = *(CPCViewport**)luaL_checkudata(L, 1, g_ViewportMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetViewportPointer);
		return 1;
	}
	else if (strcmp(key, "SetAspectRatio") == 0) {
		lua_pushcfunction(L, lua_SetViewportAspectRatio);
		return 1;
	}
	else if (strcmp(key, "GetAspectRatio") == 0) {
		lua_pushcfunction(L, lua_GetViewportAspectRatio);
		return 1;
	}
	else if (strcmp(key, "SetWidth") == 0) {
		lua_pushcfunction(L, lua_SetViewportWidth);
		return 1;
	}
	else if (strcmp(key, "GetWidth") == 0) {
		lua_pushcfunction(L, lua_GetViewportWidth);
		return 1;
	}
	else if (strcmp(key, "SetHeight") == 0) {
		lua_pushcfunction(L, lua_SetViewportHeight);
		return 1;
	}
	else if (strcmp(key, "GetHeight") == 0) {
		lua_pushcfunction(L, lua_GetViewportHeight);
		return 1;
	}
	else if (strcmp(key, "AddSpriteInstance") == 0) {
		lua_pushcfunction(L, lua_AddSpriteInstance);
		return 1;
	}
	else if (strcmp(key, "AddStaticInstance") == 0) {
		lua_pushcfunction(L, lua_ViewportAddStaticInstance);
		return 1;
	}
	else if (strcmp(key, "SetPosition") == 0 || strcmp(key, "SetViewportPosition") == 0) {
		lua_pushcfunction(L, lua_SetViewportPosition);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_GetViewportPointer(lua_State* L)
{
	CPCViewport* vp = *(CPCViewport**)luaL_checkudata(L, 1, g_ViewportMetaName);

	lua_pushinteger(L, (int)vp);

	return 1;
}

int lua_SetViewportAspectRatio(lua_State* L)
{
	CPCViewport* vp = *(CPCViewport**)luaL_checkudata(L, 1, g_ViewportMetaName);
	float newARatio = luaL_checknumber(L, 2);

	vp->SetAspectRatio(newARatio);

	return 0;
}

int lua_GetViewportAspectRatio(lua_State* L)
{
	CPCViewport* vp = *(CPCViewport**)luaL_checkudata(L, 1, g_ViewportMetaName);
	float asRatio = vp->GetAspectRatio();

	lua_pushnumber(L, asRatio);

	return 1;
}

int lua_SetViewportWidth(lua_State* L)
{
	CPCViewport* vp = *(CPCViewport**)luaL_checkudata(L, 1, g_ViewportMetaName);
	float newWidth = luaL_checknumber(L, 2);

	vp->SetWidth(newWidth);

	return 0;
}

int lua_GetViewportWidth(lua_State* L)
{
	CPCViewport* vp = *(CPCViewport**)luaL_checkudata(L, 1, g_ViewportMetaName);
	float width = vp->GetWidth();

	lua_pushnumber(L, width);

	return 1;
}

int lua_SetViewportHeight(lua_State* L)
{
	CPCViewport* vp = *(CPCViewport**)luaL_checkudata(L, 1, g_ViewportMetaName);
	float newHeight = luaL_checknumber(L, 2);

	vp->SetHeight(newHeight);

	return 0;
}

int lua_GetViewportHeight(lua_State* L)
{
	CPCViewport* vp = *(CPCViewport**)luaL_checkudata(L, 1, g_ViewportMetaName);
	float height = vp->GetHeight();

	lua_pushnumber(L, height);

	return 1;
}

int lua_SetViewportPosition(lua_State* L)
{
	CPCViewport* vp = *(CPCViewport**)luaL_checkudata(L, 1, g_ViewportMetaName);
	float fX = luaL_checknumber(L, 2);
	float fY = luaL_checknumber(L, 3);

	vp->SetViewportPosition(fX, fY);

	return 0;
}

int lua_AddSpriteInstance(lua_State* L)
{
	CPCViewport* vp = *(CPCViewport**)luaL_checkudata(L, 1, g_ViewportMetaName);
	int materialId = luaL_checkinteger(L, 2);

	float fX = luaL_checknumber(L, 3);
	float fY = luaL_checknumber(L, 4);
	float fSX = luaL_checknumber(L, 5);
	float fSY = luaL_checknumber(L, 6);

	int whichSubstance = luaL_optinteger(L, 7, 0);

	float tlU = luaL_optnumber(L, 8, 0.0f);
	float tlV = luaL_optnumber(L, 9, 0.0f);
	float brU = luaL_optnumber(L, 10, 1.0f);
	float brV = luaL_optnumber(L, 11, 1.0f);

	float r = luaL_optnumber(L, 12, 1.0f);
	float g = luaL_optnumber(L, 13, 1.0f);
	float b = luaL_optnumber(L, 14, 1.0f);
	float a = luaL_optnumber(L, 15, 1.0f);

	Sprite sprite = Sprite();

	sprite.positionX = fX;
	sprite.positionY = fY;
	sprite.sizeX = fSX;
	sprite.sizeY = fSY;
	sprite.topLeftU = tlU;
	sprite.topLeftV = tlV;
	sprite.bottomRightU = brU;
	sprite.bottomRightV = brV;

	SSpriteInstance instance = SSpriteInstance();
	instance.numSprites = 1;
	instance.sprites = &sprite;
	instance.materialID.handle_m = materialId;
	instance.whichSubstance = whichSubstance;

	vp->AddSpriteInstance(&instance);

	return 0;
}

int lua_ViewportAddStaticInstance(lua_State* L)
{
	CPCViewport* vp = *(CPCViewport**)luaL_checkudata(L, 1, g_ViewportMetaName);
	int modelHandle = luaL_checkinteger(L, 2);
	int modelLOD = luaL_checkinteger(L, 3);

	Matrix theMtx = Matrix();

	int paramsRestIdStart = 8;
	bool hasScaleParam = false;

	Lua_Quaternion** rotation = (Lua_Quaternion**)luaL_testudata(L, 4, g_LuaQuaternionMetaTable);

	if (rotation == NULL)
	{
		Lua_Vector* matrix1 = *(Lua_Vector**)luaL_checkudata(L, 4, g_LuaVectorMetaTable);
		Lua_Vector* matrix2 = *(Lua_Vector**)luaL_checkudata(L, 5, g_LuaVectorMetaTable);
		Lua_Vector* matrix3 = *(Lua_Vector**)luaL_checkudata(L, 6, g_LuaVectorMetaTable);

		theMtx.right.X = matrix1->X;
		theMtx.right.Y = matrix1->Y;
		theMtx.right.Z = matrix1->Z;

		theMtx.up.X = matrix2->X;
		theMtx.up.Y = matrix2->Y;
		theMtx.up.Z = matrix2->Z;

		theMtx.forward.X = matrix3->X;
		theMtx.forward.Y = matrix3->Y;
		theMtx.forward.Z = matrix3->Z;

		paramsRestIdStart = 7;
	}
	else
	{
		paramsRestIdStart = 6;
		hasScaleParam = true;

		Lua_Quaternion* rot = *rotation;
		theMtx = math_initFromQandV3((Vector4*)rot, Vector(0, 0, 0));
	
		
	}
	float scale = 1.0f;
		if (hasScaleParam)
			luaL_optnumber(L, paramsRestIdStart - 1, 1.0f);

	Lua_Vector* matrix4 = *(Lua_Vector**)luaL_checkudata(L, paramsRestIdStart, g_LuaVectorMetaTable);

	if (hasScaleParam)
	{
		//if (scale != 1.0f)
		{
			theMtx.forward.X *= scale;
			theMtx.forward.Y *= scale;
			theMtx.forward.Z *= scale;
			theMtx.up.X *= scale;
			theMtx.up.Y *= scale;
			theMtx.up.Z *= scale;
			theMtx.right.X *= scale;
			theMtx.right.Y *= scale;
			theMtx.right.Z *= scale;
		}
	}

	theMtx.pos.X = matrix4->X;
	theMtx.pos.Y = matrix4->Y;
	theMtx.pos.Z = matrix4->Z;
	theMtx.___pad = 1.0f;

	float alpha = luaL_optnumber(L, paramsRestIdStart+1, 1.0f);

	int whichSubstance = luaL_optinteger(L, paramsRestIdStart+2, 0);
	int roomMask = luaL_optinteger(L, paramsRestIdStart+3, 1);

	float r = luaL_optnumber(L, paramsRestIdStart+4, 1.0f);
	float g = luaL_optnumber(L, paramsRestIdStart+5, 1.0f);
	float b = luaL_optnumber(L, paramsRestIdStart+6, 1.0f);

	SStaticInstance instance = SStaticInstance();
	instance.distanceFromCamera = 0.0f;
	instance.whichSubstance = whichSubstance;
	instance.roomMask = roomMask;
	instance.mtxWorldTransform = Matrix();
	instance.hModel = modelHandle;
	instance.eLOD = (ELodType)modelLOD;

	instance.colour.X = r;
	instance.colour.Y = g;
	instance.colour.Z = b;

	instance.mtxWorldTransform = theMtx;

	vp->AddStaticInstance(&instance);

	return 0;
}