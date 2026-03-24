#pragma once

class CInGameMovie {
public:
	void PlayMovie(const char* szFileName, bool loop = false, bool pauseAtEnd = false);
};

CInGameMovie* GetInGameMovie();