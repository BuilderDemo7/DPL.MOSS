#pragma once
#include "LocalisedString.h"

class CLifeSystemCommentLog
{
public:
	void AddMissionComment(LocalisedString localisedString, float fTime, bool fadeOut = true);
	void AddMissionComment(char* comment, float fTime, bool fadeOut = true);
	void AddMissionComment(const char* comment, float fTime, bool fadeOut = true);
};

CLifeSystemCommentLog* GetLifeSystemCommentLog();