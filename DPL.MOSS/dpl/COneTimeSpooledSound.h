#pragma once
#include "Vector4.h"

#pragma pack(push, 1)
class COneTimeSpooledSound // size: 0x44
{
public:
	Vector4 m_position;
	Vector4 m_velocity;

	char __padding0[0x1F];

	bool m_bPresent;
	bool m_bPlaying;
	
	char __padding1[0x3];

	void Step();
	void Release();

	void Stop();

	void RequestBank(int bank);
	void Trigger2D(int sample, float volume = 1.0f);
};
#pragma pack(pop)