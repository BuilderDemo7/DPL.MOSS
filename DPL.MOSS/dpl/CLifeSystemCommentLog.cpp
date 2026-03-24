#include "CLifeSystemCommentLog.h"

void CLifeSystemCommentLog::AddMissionComment(LocalisedString localisedString, float fTime, bool fadeOut)
{
	((void(__thiscall*)(CLifeSystemCommentLog*, LocalisedString, float, bool))0x472c34)(this, localisedString, fTime, fadeOut);
}

void CLifeSystemCommentLog::AddMissionComment(char* comment, float fTime, bool fadeOut)
{
	LocalisedString lstr;
	lstr.m_Index = -1;
	lstr.m_nonLocalisedText = comment;
	lstr.m_missionID = -1;

	AddMissionComment(lstr, fTime, fadeOut);
}

void CLifeSystemCommentLog::AddMissionComment(const char* comment, float fTime, bool fadeOut)
{
	LocalisedString lstr;
	lstr.m_Index = -1;
	lstr.m_nonLocalisedText = const_cast<char*>(comment);
	lstr.m_missionID = -1;

	AddMissionComment(lstr, fTime, fadeOut);
}

CLifeSystemCommentLog* GetLifeSystemCommentLog()
{
	return *(CLifeSystemCommentLog**)0x70c7f8;
}