#pragma once
#include "CLifeNode.h"
#include "CLifeActor.h"

namespace Life
{
	namespace Node
	{
		namespace Character
		{
			namespace Attack
			{
				class Class : CLifeNode
				{
				public:
					void CustomInitialise(CLifeActor* attackeeCharacter, CLifeActor* attackerCharacter = NULL, float accuracy = 1.0f, int attackeeIndex = 0);
				
					char __padding0[0x48];

					CLifeActor* m_attackerActorCharacterPtr;
					CLifeActor* m_attackeeCharacterActorPtr;
					int m_attackeeActorSet;

					char __padding1[0xB0];

					float m_inaccuracy;
				};
			}
		}
	}
}