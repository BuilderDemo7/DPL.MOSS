#include "LifeNode_AI_CharacterAttack.h"

using namespace Life::Node;

void Character::Attack::Class::CustomInitialise(CLifeActor* attackeeCharacter, CLifeActor* attackerCharacter, float accuracy, int attackeeIndex)
{
	if (attackerCharacter != NULL)
		m_attackerActorCharacterPtr = attackerCharacter;

	m_attackeeCharacterActorPtr = attackeeCharacter;

	float inaccuracy = (accuracy * 0.017452778f);
	if (inaccuracy*inaccuracy > 9.869605f) {
		floor((inaccuracy + 3.1415927) * 0.15915494f);
	}

	m_inaccuracy = accuracy;
}