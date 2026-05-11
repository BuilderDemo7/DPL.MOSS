#include "Lua_Viewport.h"

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