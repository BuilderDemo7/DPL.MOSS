#pragma once
#include "CLifeNode.h"
#include "CLifeActor.h"
#include "COneTimeSpooledSound.h"
#include "SAudioClipProperty.h"
#include "Vector4.h"

#pragma pack(push, 1)
class CLifeNode_PlayAudio : CLifeNode
{
public:
	void CustomInitalise(int bankID, int sampleID, float volume = 1.0f, int flags = 0, CLifeActor* actor = NULL, float timeOut = 3.0f);

	char __padding0[0x20];

	Vector4 m_v4Position;
	Vector4 m_v4Velocity;
	COneTimeSpooledSound m_cChannel;

	CLifeActor* m_pActor;
	SAudioClipProperty m_audioClip;
	float m_fTimeout;
	float m_fVolume;

	int unknown1;

	int m_flags;
	bool m_b3DSound;
};
#pragma pack(pop)