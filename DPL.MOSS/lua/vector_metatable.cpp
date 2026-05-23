#include "vector_metatable.h"
#include <math.h>

extern const char* g_LuaVectorMetaTable = "Vector";

void Init_Lua_MetaTable_Vector(lua_State* LST)
{
	luaL_newmetatable(LST, g_LuaVectorMetaTable);

	// set __index
	lua_pushcfunction(LST, lua_VectorIndex);
	lua_setfield(LST, -2, "__index");

	// set __newindex
	lua_pushcfunction(LST, lua_VectorNewIndex);
	lua_setfield(LST, -2, "__newindex");

	// set somate/add
	lua_pushcfunction(LST, lua_VectorAdd);
	lua_setfield(LST, -2, "__add");

	// set subtract
	lua_pushcfunction(LST, lua_VectorSub);
	lua_setfield(LST, -2, "__sub");

	// set multiply
	lua_pushcfunction(LST, lua_VectorMul);
	lua_setfield(LST, -2, "__mul");

	// set divide
	lua_pushcfunction(LST, lua_VectorDiv);
	lua_setfield(LST, -2, "__div");

	lua_pop(LST, 1);

	// Create a table
	lua_newtable(LST);

	// Create a metatable
	lua_newtable(LST);
	lua_pushcfunction(LST, lua_GlobalVectorModuleIndex);
	lua_setfield(LST, -2, "__index");

	// Set the metatable for the table
	lua_setmetatable(LST, -2);

	// Push the table to the global scope
	lua_setglobal(LST, "Vector");
}

int lua_VectorAdd(lua_State* L)
{
#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "lua_VectorAdd" << std::endl;
#endif

	Lua_Vector* vecA = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable); // Vector A
	Lua_Vector* vecB = *(Lua_Vector**)luaL_checkudata(L, 2, g_LuaVectorMetaTable); // Vector B

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("vecA -> %p\n", vecA);
	printf("vecB -> %p\n", vecB);
#endif

	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	vecRes->X = vecA->X + vecB->X;
	vecRes->Y = vecA->Y + vecB->Y;
	vecRes->Z = vecA->Z + vecB->Z;

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("vecRes -> %p\n", vecRes);
#endif

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("[return] -> %p (userdata)\n", udata);
#endif

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "== == ==" << std::endl;
#endif

	return 1;
}


int lua_VectorSub(lua_State* L)
{
#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "lua_VectorSub" << std::endl;
#endif

	Lua_Vector* vecA = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable); // Vector A
	Lua_Vector* vecB = *(Lua_Vector**)luaL_checkudata(L, 2, g_LuaVectorMetaTable); // Vector B

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("vecA -> %p\n", vecA);
	printf("vecB -> %p\n", vecB);
#endif

	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	vecRes->X = vecA->X - vecB->X;
	vecRes->Y = vecA->Y - vecB->Y;
	vecRes->Z = vecA->Z - vecB->Z;

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("vecRes -> %p\n", vecRes);
#endif

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("[return] -> %p (userdata)\n", udata);
#endif

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "== == ==" << std::endl;
#endif

	return 1;
}

int lua_VectorMul(lua_State* L)
{
#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "lua_VectorMul" << std::endl;
#endif

	Lua_Vector* vecA = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable); // Vector A
	Lua_Vector* vecB = *(Lua_Vector**)luaL_checkudata(L, 2, g_LuaVectorMetaTable); // Vector B

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("vecA -> %p\n", vecA);
	printf("vecB -> %p\n", vecB);
#endif

	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	vecRes->X = vecA->X * vecB->X;
	vecRes->Y = vecA->Y * vecB->Y;
	vecRes->Z = vecA->Z * vecB->Z;

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("vecRes -> %p\n", vecRes);
#endif

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("[return] -> %p (userdata)\n", udata);
#endif

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "== == ==" << std::endl;
#endif

	return 1;
}

int lua_VectorDiv(lua_State* L)
{
#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "lua_VectorMul" << std::endl;
#endif

	Lua_Vector* vecA = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable); // Vector A
	Lua_Vector* vecB = *(Lua_Vector**)luaL_checkudata(L, 2, g_LuaVectorMetaTable); // Vector B

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("vecA -> %p\n", vecA);
	printf("vecB -> %p\n", vecB);
#endif

	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	vecRes->X = vecA->X / vecB->X;
	vecRes->Y = vecA->Y / vecB->Y;
	vecRes->Z = vecA->Z / vecB->Z;

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("vecRes -> %p\n", vecRes);
#endif

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("[return] -> %p (userdata)\n", udata);
#endif

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "== == ==" << std::endl;
#endif

	return 1;
}

int lua_VectorNewIndex(lua_State* L)
{
#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "lua_VectorNewIndex" << std::endl;
#endif

	Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable); // self
	const char* key = lua_tostring(L, 2);

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("vec -> %p\n", vec);
	std::cout << "key -> " << key << std::endl;
#endif

	float value = (float)luaL_checknumber(L, 3);

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("set_value -> %f\n", value);
#endif

	if (strcmp(key, "X") == 0) {
		vec->X = value;
	}
	else if (strcmp(key, "Y") == 0) {
		vec->Y = value;
	}
	else if (strcmp(key, "Z") == 0) {
		vec->Z = value;
	}

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "== == ==" << std::endl;
#endif

	return 0;
}

int lua_VectorIndex(lua_State* L)
{
#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "lua_VectorIndex" << std::endl;
#endif

	Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable); // self

	const char* key = luaL_checkstring(L, 2);
#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("vec -> %p\n", vec);
	std::cout << "key -> " << key << std::endl;
#endif

	if (strcmp(key, "X") == 0) {
		lua_pushnumber(L, vec->X);
		return 1;
	}
	else if (strcmp(key, "Y") == 0) {
		lua_pushnumber(L, vec->Y);
		return 1;
	}
	else if (strcmp(key, "Z") == 0) {
		lua_pushnumber(L, vec->Z);
		return 1;
	}
	else if (strcmp(key, "Magnitude") == 0) {
		lua_pushnumber(L, sqrt(vec->X * vec->X + vec->Y * vec->Y + vec->Z * vec->Z));
		return 1;
	}
	else if (strcmp(key, "MagnitudeSqr") == 0) {
		lua_pushnumber(L, vec->X * vec->X + vec->Y * vec->Y + vec->Z * vec->Z);
		return 1;
	}
	else if (strcmp(key, "Heading") == 0) {
		lua_pushnumber(L, atan2(vec->X, vec->Z));
		return 1;
	}
	else if (strcmp(key, "Destroy") == 0) {
		lua_pushcfunction(L, lua_VectorDestroy);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "== == ==" << std::endl;
#endif

	return 1;
}

int lua_GlobalVectorModuleIndex(lua_State* L)
{
#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "lua_GlobalVectorModuleIndex" << std::endl;
#endif

	const char* key = lua_tostring(L, 2);

	if (strcmp(key, "new") == 0) {
		lua_pushcfunction(L, lua_VectorNew);
	}

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "== == ==" << std::endl;
#endif

	return 1;
}

int lua_VectorNew(lua_State* L)
{
#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "lua_VectorNew" << std::endl;
#endif

	double x = luaL_optnumber(L, 1, 0.0); // default 0
	double y = luaL_optnumber(L, 2, 0.0); // default 0
	double z = luaL_optnumber(L, 3, 0.0); // default 0

	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;
	vecRes->X = x;
	vecRes->Y = y;
	vecRes->Z = z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	printf("[return] -> %p (userdata)\n", udata);
#endif

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "== == ==" << std::endl;
#endif

	return 1;
}

int lua_VectorDestroy(lua_State* L) 
{
#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "lua_VectorDestroy" << std::endl;
#endif
	Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable);

	// Mark it as destroyed
	vec->X = vec->Y = vec->Z = 0.0f;

	// Optionally set its metatable to nil so no methods work
	lua_pushnil(L);
	lua_setmetatable(L, 1);

#ifdef LUA_VECTOR_DEBUGLOG_CALLS
	std::cout << "== == ==" << std::endl;
#endif

	return 0;
}