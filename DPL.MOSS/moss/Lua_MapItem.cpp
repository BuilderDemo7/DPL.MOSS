#include "Lua_MapItem.h"
#include "..\dpl\GameOverlayManager.h"

const char* g_MapItemMetaName = "MapItem";

void Init_Lua_MetaTable_MapItem()
{
	luaL_newmetatable(L, g_MapItemMetaName);

	// set __index
	lua_pushcfunction(L, lua_MapItemIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_MapItemIndex(lua_State* L)
{
	SMapItem* mapitem = *(SMapItem**)luaL_checkudata(L, 1, g_MapItemMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetMapItemPosition);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetMapItemPosition);
		return 1;
	}
	else if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetMapItemPointer);
		return 1;
	}
	else if (strcmp(key, "SetHeading") == 0 || strcmp(key, "SetAngle") == 0) {
		lua_pushcfunction(L, lua_SetMapItemHeading);
		return 1;
	}
	else if (strcmp(key, "GetHeading") == 0 || strcmp(key, "GetAngle") == 0) {
		lua_pushcfunction(L, lua_GetMapItemHeading);
		return 1;
	}
	else if (strcmp(key, "SetType") == 0 || strcmp(key, "SetMapItemType") == 0) {
		lua_pushcfunction(L, lua_SetMapItemType);
		return 1;
	}
	else if (strcmp(key, "GetType") == 0 || strcmp(key, "GetMapItemType") == 0) {
		lua_pushcfunction(L, lua_SetMapItemType);
		return 1;
	}
	else if (strcmp(key, "SetShowArrow") == 0 || strcmp(key, "SetShowTargetArrow") == 0) {
		lua_pushcfunction(L, lua_SetMapItemShowArrow);
		return 1;
	}
	else if (strcmp(key, "GetShowArrow") == 0 || strcmp(key, "GetShowTargetArrow") == 0) {
		lua_pushcfunction(L, lua_GetMapItemShowArrow);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_AddMapItem(lua_State* L)
{
	COverheadMap* map = GetOverheadMap();

	float x, y, z, angle;
	int type = EMapIcon_Default;

	if (lua_isuserdata(L, 2) != 1) {
		// Three numbers
		type = (float)luaL_checkinteger(L, 1);
		x = (float)luaL_checknumber(L, 2);
		y = (float)luaL_checknumber(L, 3);
		z = (float)luaL_checknumber(L, 4);
		angle = (float)luaL_optnumber(L, 5, 0);
	}
	else if (lua_isuserdata(L, 2) == 1) {
		type = (int)luaL_optinteger(L, 1, 0);

		// Vector
		Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 2, g_LuaVectorMetaTable);
		x = vec->X;
		y = vec->Y;
		z = vec->Z;
		angle = (float)luaL_optnumber(L, 3, 0);
	}
	else {
		return luaL_error(L, "bad argument #2 - expected 1 Vector or 3 numbers");
	}

	if (map != NULL)
	{
		SMapItem mapItem = SMapItem();
		mapItem.position.X = x;
		mapItem.position.Y = y;
		mapItem.position.Z = z;
		mapItem.position.W = 1.0f;

		mapItem.orientation = angle;
		mapItem.type = (EMapItem)type;

		SMapItem** udata = (SMapItem**)lua_newuserdata(L, sizeof(void*));
		*udata = &mapItem;

		map->AddItem(&mapItem);

		luaL_getmetatable(L, g_MapItemMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		return 1;
	}

	lua_pushnil(L);

	return 1;
}

int lua_GetMapItems(lua_State* L)
{
	COverheadMap* map = GetOverheadMap();

	if (map == NULL)
	{
		lua_pushnil(L);
		return 1;
	}

	lua_newtable(L); // result table
	int count = 32;

	for (int i = 0; i < count; i++)
	{
		if (map->m_cMapMarkers.m_sItems[i].type != EMapItem_Uninitialised)
		{
			SMapItem** udata = (SMapItem**)lua_newuserdata(L, sizeof(void*));
			*udata = &map->m_cMapMarkers.m_sItems[i];

			// set metatable
			luaL_getmetatable(L, g_MapItemMetaName);
			lua_setmetatable(L, -2);

			// insert into array
			lua_rawseti(L, -2, i + 1);
		}
	}

	return 1; // return the table
}

int lua_SetMapItemPosition(lua_State* L) 
{ 
	SMapItem* mapitem = *(SMapItem**)luaL_checkudata(L, 1, g_MapItemMetaName);

	int nargs = lua_gettop(L) - 1; // number of arguments after 'self'

	float x, y, z;

	if (nargs == 1) {
		// Single argument: expect a Vector
		Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 2, g_LuaVectorMetaTable);
		x = vec->X;
		y = vec->Y;
		z = vec->Z;
	}
	else if (nargs == 3) {
		// Three numbers
		x = (float)luaL_checknumber(L, 2);
		y = (float)luaL_checknumber(L, 3);
		z = (float)luaL_checknumber(L, 4);
	}
	else {
		return luaL_error(L, "bad argument #1 - Expected 1 Vector or 3 numbers");
	}
	
	COverheadMap* map = GetOverheadMap();

	SMapItem* aproxItem = map->FindItem(mapitem);

	Vector4 pos = Vector4(x, y, z, 1);
	mapitem->position = pos;

	if (aproxItem != NULL)
		aproxItem->position = pos;

	return 0;  // number of return(s)
} 

int lua_GetMapItemPosition(lua_State* L) 
{ 
	SMapItem* mapitem = *(SMapItem**)luaL_checkudata(L, 1, g_MapItemMetaName);

		// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = mapitem->position;

	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
} 

int lua_GetMapItemPointer(lua_State* L) 
{ 
	SMapItem* mapitem = *(SMapItem**)luaL_checkudata(L, 1, g_MapItemMetaName);

	lua_pushinteger(L, (int)mapitem);

	return 1;
}

int lua_SetMapItemHeading(lua_State* L) 
{ 
	SMapItem* mapitem = *(SMapItem**)luaL_checkudata(L, 1, g_MapItemMetaName);

	double angle = luaL_checknumber(L, 2);

	// D:PL doesn't work with degrees all the time
	//angle = (angle * 180) / MATH_PI; // convert to degrees

	COverheadMap* map = GetOverheadMap();

	SMapItem* aproxItem = map->FindItem(mapitem);

	mapitem->orientation = angle;

	if (aproxItem != NULL)
		aproxItem->orientation = angle;

	return 0;
} 

int lua_GetMapMarkerActive(lua_State* L)
{
	COverheadMap* map = GetOverheadMap();

	if (map != NULL)
	{
		lua_pushboolean(L, map->m_cMapMarkers.m_MapMarkerActive);

		return 1;
	}

	lua_pushboolean(L, false);
	return 1;
}

int lua_SetMapMarkerActive(lua_State* L)
{
	COverheadMap* map = GetOverheadMap();
	bool active = lua_toboolean(L, 1);

	if (map != NULL)
	{
		map->m_cMapMarkers.m_MapMarkerActive = active;
	}

	return 0;
}

int lua_GetPlayerMapItem(lua_State* L)
{
	COverheadMap* map = GetOverheadMap();

	if (map != NULL)
	{
		SMapItem** udata = (SMapItem**)lua_newuserdata(L, sizeof(void*));
		*udata = &map->m_cMapMarkers.m_player;

		luaL_getmetatable(L, g_MapItemMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_GetMapMarkerItem(lua_State* L)
{
	COverheadMap* map = GetOverheadMap();

	if (map != NULL)
	{
		SMapItem** udata = (SMapItem**)lua_newuserdata(L, sizeof(void*));
		*udata = &map->m_cMapMarkers.m_MapMarker;

		luaL_getmetatable(L, g_MapItemMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_GetCameraMapItem(lua_State* L)
{
	COverheadMap* map = GetOverheadMap();

	if (map != NULL)
	{
		SMapItem** udata = (SMapItem**)lua_newuserdata(L, sizeof(void*));
		*udata = &map->m_cMapMarkers.m_camera;

		luaL_getmetatable(L, g_MapItemMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_GetMapItemHeading(lua_State* L) 
{ 
	SMapItem* mapitem = *(SMapItem**)luaL_checkudata(L, 1, g_MapItemMetaName);

	double angle = (double)mapitem->orientation;

	// D:PL doesn't work with degrees all the time
	//angle = (angle * 180) / MATH_PI; // convert to degrees

	lua_pushnumber(L, angle);

	return 1;
}

int lua_SetMapItemType(lua_State* L)
{
	SMapItem* mapitem = *(SMapItem**)luaL_checkudata(L, 1, g_MapItemMetaName);

	EMapItem mi = (EMapItem)luaL_checkinteger(L, 2);

	mapitem->type = mi;

	return 0;
}

int lua_GetMapItemType(lua_State* L) 
{ 
	SMapItem* mapitem = *(SMapItem**)luaL_checkudata(L, 1, g_MapItemMetaName);

	EMapItem mi = mapitem->type;

	lua_pushinteger(L, (int)mi);

	return 1;
} 

int lua_SetMapItemShowArrow(lua_State* L) 
{ 
	SMapItem* mapitem = *(SMapItem**)luaL_checkudata(L, 1, g_MapItemMetaName);

	bool status = lua_toboolean(L, 2);

	mapitem->subItem.character.bShowArrow = status;
	mapitem->subItem.network.bShowArrow = status;
	mapitem->subItem.target.bShowArrow = status;
	mapitem->subItem.vehicle.bShowArrow = status;

	return 0; 
}

int lua_GetMapItemShowArrow(lua_State* L)
{ 
	SMapItem* mapitem = *(SMapItem**)luaL_checkudata(L, 1, g_MapItemMetaName);

	bool status = mapitem->subItem.character.bShowArrow || mapitem->subItem.network.bShowArrow || mapitem->subItem.target.bShowArrow || mapitem->subItem.vehicle.bShowArrow;

	lua_pushboolean(L, status);

	return 1; 
}