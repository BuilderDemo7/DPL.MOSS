#include "Lua_LifeInstance.h"

#include "Lua_CharacterInstance.h"
#include "Lua_VehicleInstance.h"

const char* g_LifeInstanceMetaName = "LifeInstance";

void Init_Lua_MetaTable_LifeInstance()
{
	luaL_newmetatable(L, g_LifeInstanceMetaName);

	// set __index
	lua_pushcfunction(L, lua_LifeInstanceIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_LifeInstanceIndex(lua_State* L)
{
	CLifeInstance* instance = *(CLifeInstance**)lua_touserdata(L, 1);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetLifeInstancePointer);
		return 1;
	}
	else if (strcmp(key, "GetInstance") == 0) {
		lua_pushcfunction(L, lua_GetLifeInstanceInstance);
		return 1;
	}
	else if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetLifeInstancePosition);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetLifeInstancePosition);
		return 1;
	}
	else if (strcmp(key, "UnregisterSpoolHandler") == 0) {
		lua_pushcfunction(L, lua_UnregisterLifeInstanceSpoolHandler);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_UnregisterLifeInstanceSpoolHandler(lua_State* L)
{
	// not available for unknown life instances

	return 0;
}

int lua_GetLifeInstancePosition(lua_State* L)
{
	// returns 0,0,0!

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = Vector4(0, 0, 0, 1);
	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1;
}

int lua_SetLifeInstancePosition(lua_State* L)
{
	return 0;
}

int lua_GetLifeInstanceInstance(lua_State* L)
{
	// no instance assumed so returning nil
	lua_pushnil(L);
	return 1;
}

int lua_GetLifeInstancePointer(lua_State* L)
{
	CLifeInstance* instance = *(CLifeInstance**)lua_touserdata(L, 1);

	lua_pushinteger(L, (int)instance);

	return 1;
}

void* lua_checklifeinstance(lua_State* L, int ud, bool shouldError)
{
	CLifeInstance** targetInst = (CLifeInstance**)luaL_testudata(L, ud, g_VehicleInstanceMetaName);
	if (!targetInst)
		targetInst = (CLifeInstance**)luaL_testudata(L, ud, g_CharacterInstanceMetaName);
	if (!targetInst)
		targetInst = (CLifeInstance**)luaL_testudata(L, ud, g_LifeInstanceMetaName);

	if (!targetInst && shouldError)
	{
		luaL_error(L, "invalid userdata, expected a LifeInstance, do not use actors types");
		return NULL;
	}

	return (void*)targetInst;
}

const char* GetLifeInstanceMetaTableName(CLifeInstance* instance)
{
	const char* name = NULL;

	if (instance != NULL)
	{
		int vt = *(int*)instance;

		switch (vt)
		{
		case 0x6451b8: // _vt$23CLifeInstance_Character
		{
			name = g_CharacterInstanceMetaName;
			break;
		}
		case 0x6458a8: // _vt$21CLifeInstance_Vehicle
		{
			name = g_VehicleInstanceMetaName;
			break;
		}
		case 0x6459fc: // _vt$20CLifeInstance_Volume
		{
			// TODO: change placeholder later
			name = g_LifeInstanceMetaName; // placeholder
			break;
		}
		}
	}

	return name;
}

Lua_LifeInstanceInfo GetLuaLifeInstance(CLifeInstance* instance)
{
	Lua_LifeInstanceInfo info = Lua_LifeInstanceInfo();

	if (instance != NULL)
	{
		CLifeInstance** udata = (CLifeInstance**)lua_newuserdata(L, sizeof(void*));
		*udata = instance;

		info.m_pszMetaTableName = GetLifeInstanceMetaTableName(instance);

		info.m_pUserData = (void*)udata;
	}

	return info;
}

// generic funcs
int lua_DestroyLifeInstance(lua_State* L)
{
	CLifeInstance* instance = *(CLifeInstance**)lua_touserdata(L, 1);

	unsigned int createFuncAddr = NULL;
	unsigned int vt = *(unsigned int*)instance;

	if (vt == 0x6451b8 || vt == 0x6458a8) // character or vehicle
		createFuncAddr = *(int*)(vt + 0x8);

	if (createFuncAddr != NULL)
		((bool(__thiscall*)(CLifeInstance*))createFuncAddr)(instance);
	return 0;
}

int lua_InstantiateLifeInstance(lua_State* L)
{
	CLifeInstance* instance = *(CLifeInstance**)lua_touserdata(L, 1);

	unsigned int createFuncAddr = NULL;
	unsigned int vt = *(unsigned int*)instance;

	if (vt == 0x6451b8 || vt == 0x6458a8) // character or vehicle
		createFuncAddr = *(int*)(vt + 0x4);

	if (createFuncAddr != NULL)
		((bool(__thiscall*)(CLifeInstance*))createFuncAddr)(instance);
	return 0;
}

int lua_GetLifeInstances(lua_State* L)
{
	CLifeInstances* linstances = GetLifeInstances();

	lua_newtable(L); // result table

	if (linstances != NULL)
	{

		int count = 132;

		for (int i = 0; i < count; i++)
		{
			LifeInstanceItem item = linstances->m_itemsHolder.m_items[i];
			if (item.m_pItem != NULL)
			{
				CLifeInstance** udata = (CLifeInstance**)lua_newuserdata(L, sizeof(void*));
				*udata = item.m_pItem;

				// set metatable

				const char* mName = GetLifeInstanceMetaTableName(item.m_pItem);
				if (mName == NULL)
					mName = g_LifeInstanceMetaName; // default

				luaL_getmetatable(L, mName);
				lua_setmetatable(L, -2);

				// insert into array
				lua_rawseti(L, -2, i + 1);
			}
		}
	}

	return 1;
}