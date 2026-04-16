#include "Lua_LifeActor.h"

int lua_AddObjectiveIconToLifeActor(lua_State* L)
{
	CLifeActor* actor = *(CLifeActor**)lua_touserdata(L, 1);

	int nargs = lua_gettop(L);

	int displayType = luaL_checkinteger(L, 2);
	int visibility = luaL_optinteger(L, 3, 2);
	bool displayMinimapArrow = false;
	if (nargs > 3)
		displayMinimapArrow = lua_toboolean(L, 4);
	bool displayAsCop = false;
	if (nargs > 4)
		displayAsCop = lua_toboolean(L, 5);

	float heightOffset = luaL_optnumber(L, 6, 0.0f);
	int eventType = luaL_optinteger(L, 7, 0);

	SObjectiveIcon objective = SObjectiveIcon();
	objective.m_bParticleEffect = false;
	objective.m_pTarget = actor;

	objective.m_activity = 1; // 1 = add, 2 = remove

	SetupObjectiveIcon(&objective, displayType, eventType, eventType == 4);

	objective.m_minimapDisplayArrow = displayMinimapArrow;
	objective.m_displayAsCop = displayAsCop;
	objective.m_heightOffset = objective.m_heightOffset + heightOffset;
	objective.m_visibility = visibility;

	auto tm = CTargetManager::GetInstance();
	if (tm)
	{
		tm->AddObjectiveIcon(&objective, objective.m_bParticleEffect);
	}

	return 0;
}

int lua_RemoveObjectiveIconFromLifeActor(lua_State* L)
{
	// NOTE: pretty much similar to lua_AddObjectiveIconToLifeActor, except that objective.m_activity = 2
	CLifeActor* actor = *(CLifeActor**)lua_touserdata(L, 1);

	int nargs = lua_gettop(L);

	int displayType = luaL_checkinteger(L, 2);
	bool displayMinimapArrow = false;
	if (nargs > 2)
		displayMinimapArrow = lua_toboolean(L, 3);
	bool displayAsCop = false;
	if (nargs > 3)
		displayAsCop = lua_toboolean(L, 4);

	float heightOffset = luaL_optnumber(L, 5, 0.0f);
	int eventType = luaL_optinteger(L, 6, 0);

	SObjectiveIcon objective = SObjectiveIcon();
	objective.m_bParticleEffect = false;
	objective.m_pTarget = actor;

	objective.m_activity = 2; // 1 = add, 2 = remove

	SetupObjectiveIcon(&objective, displayType, eventType, eventType == 4);

	objective.m_minimapDisplayArrow = displayMinimapArrow;
	objective.m_displayAsCop = displayAsCop;
	objective.m_heightOffset = objective.m_heightOffset + heightOffset;

	auto tm = CTargetManager::GetInstance();
	if (tm)
	{
		tm->AddObjectiveIcon(&objective, objective.m_bParticleEffect);
	}

	return 0;
}