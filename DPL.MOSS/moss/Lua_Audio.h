#pragma once
#include "Lua_Main.h"
#include "..\dpl\CLifeNode_PlayAudio.h"

extern const char* g_AudioMetaName;

void Add_AudioPlay(CLifeNode_PlayAudio* item);
void Remove_AudioPlay(CLifeNode_PlayAudio* item);

extern CLifeNode_PlayAudio* g_aCustomPlayAudios[102];

void Init_Lua_MetaTable_Audio();

int lua_AudioIndex(lua_State* L);

int lua_GetAudioPointer(lua_State* L);

int lua_PlayAudio(lua_State* L);
int lua_StopAudio(lua_State* L);

int lua_CreateAudio(lua_State* L);

int lua_SetAudioBankID(lua_State* L);
int lua_GetAudioBankID(lua_State* L);
int lua_SetAudioSampleID(lua_State* L);
int lua_GetAudioSampleID(lua_State* L);

int lua_SetAudioVolume(lua_State* L);
int lua_GetAudioVolume(lua_State* L);

int lua_GetAudioAttachedActor(lua_State* L);
int lua_GetAudioAttachedActorPointer(lua_State* L);