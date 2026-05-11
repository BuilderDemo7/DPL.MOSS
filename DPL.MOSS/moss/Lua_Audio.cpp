#include "Lua_Audio.h"
#include "..\dpl\Factory.h"
#include "Lua_LifeActor.h"

const char* g_AudioMetaName = "Audio";
CLifeNode_PlayAudio* g_aCustomPlayAudios[102] = {};

void Init_Lua_MetaTable_Audio()
{
	luaL_newmetatable(L, g_AudioMetaName);

	// set __index
	lua_pushcfunction(L, lua_AudioIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_AudioIndex(lua_State* L)
{
	CLifeNode_PlayAudio* plAudio = *(CLifeNode_PlayAudio**)luaL_checkudata(L, 1, g_AudioMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetAudioPointer);
		return 1;
	}
	else if (strcmp(key, "Play") == 0 || strcmp(key, "Enable") == 0) {
		lua_pushcfunction(L, lua_PlayAudio);
		return 1;
	}
	else if (strcmp(key, "Stop") == 0 || strcmp(key, "Disable") == 0) {
		lua_pushcfunction(L, lua_StopAudio);
		return 1;
	}
	else if (strcmp(key, "GetAttachedActor") == 0) {
		lua_pushcfunction(L, lua_GetAudioAttachedActor);
		return 1;
	}
	else if (strcmp(key, "GetAttachedActorPointer") == 0) {
		lua_pushcfunction(L, lua_GetAudioAttachedActorPointer);
		return 1;
	}
	else if (strcmp(key, "SetBankID") == 0) {
		lua_pushcfunction(L, lua_SetAudioBankID);
		return 1;
	}
	else if (strcmp(key, "GetBankID") == 0) {
		lua_pushcfunction(L, lua_GetAudioBankID);
		return 1;
	}
	else if (strcmp(key, "SetSampleID") == 0) {
		lua_pushcfunction(L, lua_SetAudioSampleID);
		return 1;
	}
	else if (strcmp(key, "GetSampleID") == 0) {
		lua_pushcfunction(L, lua_GetAudioSampleID);
		return 1;
	}
	else if (strcmp(key, "SetVolume") == 0) {
		lua_pushcfunction(L, lua_SetAudioVolume);
		return 1;
	}
	else if (strcmp(key, "GetVolume") == 0) {
		lua_pushcfunction(L, lua_GetAudioVolume);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

void Add_AudioPlay(CLifeNode_PlayAudio* item)
{
	for (int i = 0; i < 102; i++)
	{
		if (g_aCustomPlayAudios[i] == NULL)
		{
			g_aCustomPlayAudios[i] = item;
			break;
		}
	}
}

void Remove_AudioPlay(CLifeNode_PlayAudio* item)
{
	for (int i = 0; i < 102; i++)
	{
		if (g_aCustomPlayAudios[i] == item)
		{
			g_aCustomPlayAudios[i] = NULL;
			break;
		}
	}
}

int lua_SetAudioVolume(lua_State* L)
{
	CLifeNode_PlayAudio* plAudio = *(CLifeNode_PlayAudio**)luaL_checkudata(L, 1, g_AudioMetaName);

	float newVol = luaL_checknumber(L, 2);
	plAudio->m_fVolume = newVol;

	return 0;
}

int lua_GetAudioVolume(lua_State* L)
{
	CLifeNode_PlayAudio* plAudio = *(CLifeNode_PlayAudio**)luaL_checkudata(L, 1, g_AudioMetaName);

	float Vol = plAudio->m_fVolume;
	lua_pushnumber(L, Vol);

	return 1;
}

int lua_SetAudioBankID(lua_State* L)
{
	CLifeNode_PlayAudio* plAudio = *(CLifeNode_PlayAudio**)luaL_checkudata(L, 1, g_AudioMetaName);

	int newBankId = luaL_checkinteger(L, 2);
	plAudio->m_audioClip.iBankID = newBankId;

	return 0;
}

int lua_GetAudioBankID(lua_State* L)
{
	CLifeNode_PlayAudio* plAudio = *(CLifeNode_PlayAudio**)luaL_checkudata(L, 1, g_AudioMetaName);

	int BankId = plAudio->m_audioClip.iBankID;
	lua_pushinteger(L, BankId);

	return 1;
}

int lua_SetAudioSampleID(lua_State* L)
{
	CLifeNode_PlayAudio* plAudio = *(CLifeNode_PlayAudio**)luaL_checkudata(L, 1, g_AudioMetaName);

	int newSampleId = luaL_checkinteger(L, 2);
	plAudio->m_audioClip.iSampleID = newSampleId;

	return 0;
}

int lua_GetAudioSampleID(lua_State* L)
{
	CLifeNode_PlayAudio* plAudio = *(CLifeNode_PlayAudio**)luaL_checkudata(L, 1, g_AudioMetaName);

	int SampleId = plAudio->m_audioClip.iSampleID;
	lua_pushinteger(L, SampleId);

	return 1;
}

int lua_GetAudioAttachedActor(lua_State* L)
{
	CLifeNode_PlayAudio* plAudio = *(CLifeNode_PlayAudio**)luaL_checkudata(L, 1, g_AudioMetaName);
	CLifeActor* actor = plAudio->m_pActor;
	if (actor != NULL)
	{
		Lua_LifeActorInfo info = GetLuaLifeActor(actor);

		luaL_getmetatable(L, info.m_pszMetaTableName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_GetAudioAttachedActorPointer(lua_State* L)
{
	CLifeNode_PlayAudio* plAudio = *(CLifeNode_PlayAudio**)luaL_checkudata(L, 1, g_AudioMetaName);
	CLifeActor* actor = plAudio->m_pActor;

	lua_pushinteger(L, (int)actor);

	return 1;
}

int lua_GetAudioPointer(lua_State* L)
{
	CLifeNode_PlayAudio* plAudio = *(CLifeNode_PlayAudio**)luaL_checkudata(L, 1, g_AudioMetaName);

	lua_pushinteger(L, (int)plAudio);

	return 1;
}

int lua_PlayAudio(lua_State* L)
{
	CLifeNode_PlayAudio* plAudio = *(CLifeNode_PlayAudio**)luaL_checkudata(L, 1, g_AudioMetaName);

	bool enabled;
	eNodeFireWire fw;

	((CLifeNode*)plAudio)->OnEnable(&enabled, &fw);

	return 0;
}

int lua_StopAudio(lua_State* L)
{
	CLifeNode_PlayAudio* plAudio = *(CLifeNode_PlayAudio**)luaL_checkudata(L, 1, g_AudioMetaName);

	((CLifeNode*)plAudio)->OnDisable();

	return 0;
}

int lua_CreateAudio(lua_State* L)
{
	int nargs = lua_gettop(L);

	int bankId = luaL_checkinteger(L, 1);
	int sampleId = luaL_checkinteger(L, 2);
	float volume = luaL_optnumber(L, 3, 1.0f);

	bool vocal = false;

	int flags = 0;
	if (nargs > 3)
		vocal = lua_toboolean(L, 4);

	if (vocal)
		flags |= 0x20000;

	CLifeActor** actor = (CLifeActor**)lua_checklifeactor(L, 5, false);

	CLifeActor* pActor = NULL;
	if (actor != NULL)
		pActor = *actor;

	CLifeNode_PlayAudio* plAudio = (CLifeNode_PlayAudio*)hamster::CreateObject(EFactoryType::EFactoryType_LifeNode_PlayAudio);

	if (plAudio != NULL)
	{
		plAudio->CustomInitalise(bankId, sampleId, volume, flags, pActor);

		CLifeNode_PlayAudio** udata = (CLifeNode_PlayAudio**)lua_newuserdata(L, sizeof(void*));
		*udata = plAudio;

		Add_AudioPlay(plAudio);

		luaL_getmetatable(L, g_AudioMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		return 1;
	}

	lua_pushnil(L);
	return 1;
}