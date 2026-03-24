#include "quaternion_metatable.h"

const char* g_LuaQuaternionMetaTable = "Quaternion";

extern void Init_Lua_MetaTable_Quaternion(lua_State* LST)
{
	luaL_newmetatable(LST, g_LuaQuaternionMetaTable);

	// set __index
	lua_pushcfunction(LST, lua_QuaternionIndex);
	lua_setfield(LST, -2, "__index");

	// set __newindex
	lua_pushcfunction(LST, lua_QuaternionNewIndex);
	lua_setfield(LST, -2, "__newindex");

	lua_pop(LST, 1);

	// Create a table
	lua_newtable(LST);

	// Create a metatable
	lua_newtable(LST);
	lua_pushcfunction(LST, lua_GlobalQuaternionModuleIndex);
	lua_setfield(LST, -2, "__index");

	// Set the metatable for the table
	lua_setmetatable(LST, -2);

	// Push the table to the global scope
	lua_setglobal(LST, "Quaternion");
}

int lua_QuaternionDestroy(lua_State* L)
{
	Lua_Quaternion* vec = *(Lua_Quaternion**)luaL_checkudata(L, 1, g_LuaQuaternionMetaTable);

	// Mark it as destroyed
	vec->X = vec->Y = vec->Z = vec->W = 0.0f;

	// Optionally set its metatable to nil so no methods work
	lua_pushnil(L);
	lua_setmetatable(L, 1);

	return 1;
}

int lua_QuaternionNew(lua_State* L)
{
	double x = luaL_optnumber(L, 1, 0.0); // default 0
	double y = luaL_optnumber(L, 2, 0.0); // default 0
	double z = luaL_optnumber(L, 3, 0.0); // default 0
	double w = luaL_optnumber(L, 4, 0.0); // default 0

	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Quaternion();

	Lua_Quaternion* quaRes = *(Lua_Quaternion**)udata;
	quaRes->X = x;
	quaRes->Y = y;
	quaRes->Z = z;
	quaRes->W = w;

	luaL_getmetatable(L, g_LuaQuaternionMetaTable);
	lua_setmetatable(L, -2);

	return 1;
}

int lua_QuaternionIndex(lua_State* L)
{
	Lua_Quaternion* qua = *(Lua_Quaternion**)luaL_checkudata(L, 1, g_LuaQuaternionMetaTable); // self
	const char* key = luaL_checkstring(L, 2);

	if (strcmp(key, "X") == 0) {
		lua_pushnumber(L, qua->X);
		return 1;
	}
	else if (strcmp(key, "Y") == 0) {
		lua_pushnumber(L, qua->Y);
		return 1;
	}
	else if (strcmp(key, "Z") == 0) {
		lua_pushnumber(L, qua->Z);
		return 1;
	}
	else if (strcmp(key, "W") == 0) {
		lua_pushnumber(L, qua->Z);
		return 1;
	}
	else if (strcmp(key, "Destroy") == 0) {
		lua_pushcfunction(L, lua_QuaternionDestroy);
		return 1;
	}
	else if (strcmp(key, "ToEuler") == 0 || strcmp(key, "ToEulerAngles") == 0) {
		lua_pushcfunction(L, lua_QuaternionToEulerAngles);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_QuaternionNewIndex(lua_State* L)
{
	Lua_Quaternion* qua = *(Lua_Quaternion**)luaL_checkudata(L, 1, g_LuaQuaternionMetaTable); // self
	const char* key = lua_tostring(L, 2);
	float value = (float)luaL_checknumber(L, 3);
	
	if (strcmp(key, "X") == 0) {
		qua->X = value;
	}
	else if (strcmp(key, "Y") == 0) {
		qua->Y = value;
	}
	else if (strcmp(key, "Z") == 0) {
		qua->Z = value;
	}
	else if (strcmp(key, "W") == 0) {
		qua->W = value;
	}

	return 0;
}

int lua_QuaternionFromEulerAngles(lua_State* L)
{
	double yaw = luaL_checknumber(L, 1); // default 0
	double pitch = luaL_checknumber(L, 2); // default 0
	double roll = luaL_checknumber(L, 3); // default 0

	roll = roll * (MATH_PI / 180.0);
	pitch = pitch * (MATH_PI / 180.0);
	yaw = yaw * (MATH_PI / 180.0);

	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);

	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Quaternion();

	Lua_Quaternion* q = *(Lua_Quaternion**)udata;
	//q->X = cy * cp * cr + sy * sp * sr;
	//q->Y = cy * sp * cr + sy * cp * sr;
	//q->Z = sy * cp * cr - cy * sp * sr;
	//q->W = cy * cp * sr - sy * sp * cr;

	q->W = cy * cp * cr + sy * sp * sr;
	q->X = cy * sp * cr + sy * cp * sr;
	q->Y = sy * cp * cr - cy * sp * sr;
	q->Z = cy * cp * sr - sy * sp * cr;

	// normalise
	double magnitude = sqrt(q->W*q->W + q->X*q->X + q->Y*q->Y + q->Z*q->Z);
	q->W /= magnitude;
	q->X /= magnitude;
	q->Y /= magnitude;
	q->Z /= magnitude;

	luaL_getmetatable(L, g_LuaQuaternionMetaTable);
	lua_setmetatable(L, -2);

	return 1;
}

int lua_QuaternionToEulerAngles(lua_State* L)
{
	Lua_Quaternion* q = *(Lua_Quaternion**)luaL_checkudata(L, 1, g_LuaQuaternionMetaTable); // param 1

	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* v = *(Lua_Vector**)udata;

	// Pitch (X axis)
	double sinp = 2.0 * (q->W * q->X + q->Y * q->Z);
	double cosp = 1.0 - 2.0 * (q->X * q->X + q->Y * q->Y);
	v->Y = atan2(sinp, cosp);

	// Yaw (Y axis)
	double siny = 2.0 * (q->W * q->Y - q->Z * q->X);
	if (fabs(siny) >= 1.0)
		v->X = copysign(MATH_PI / 2.0, siny); // clamp out of range
	else
		v->X = asin(siny);

	// Roll (Z axis)
	double sinr = 2.0 * (q->W * q->Z + q->X * q->Y);
	double cosr = 1.0 - 2.0 * (q->Y * q->Y + q->Z * q->Z);
	v->Z = atan2(sinr, cosr);

	// Convert back to degrees if you want
	v->X *= 180.0 / MATH_PI; // yaw
	v->Y *= 180.0 / MATH_PI; // pitch
	v->Z *= 180.0 / MATH_PI; // roll

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1;
}

int lua_GlobalQuaternionModuleIndex(lua_State* L)
{
	const char* key = lua_tostring(L, 2);

	if (strcmp(key, "new") == 0) {
		lua_pushcfunction(L, lua_QuaternionNew);
	}
	else if (strcmp(key, "FromEuler") == 0  || strcmp(key, "FromEulerAngles") == 0) {
		lua_pushcfunction(L, lua_QuaternionFromEulerAngles);
	}

	return 1;
}