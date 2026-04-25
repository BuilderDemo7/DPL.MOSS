#include "CLifeActor_Character.h"
#include "CLifeSystem.h"
#include "LifeInstances.h"
#include "SpoolableResourceManager.h"

void CLifeActor_Character::CustomInitialise(ECharacterType skin, Matrix matrix, EWeapons weapon, float initialHealth, float felony, CLifeActor_Vehicle* initialVehicle, int initialVehicleSeat, bool createFromStart, bool addToFelonyManager, bool doNotUseIdleAnims, bool isPlayer, bool ignorePlayerRegister, bool keepSkin, int playerNumber, CLifeEventData* pEventData)
{
	CLifeEventData* pActualEventData = pEventData;

	if (pActualEventData == NULL)
	{
		AutoPtr<CLifeEventData, int> data = CLifeEventDataManager::GetInstance()->GetLifeEventData(0);

		// 'data' only stored once in the stack, also we have to do this 
		pActualEventData = data.m_pPointer;
	}

	m_pOwner = pActualEventData;

	m_fFelony = felony;
	m_health = initialHealth;
	if (m_health < 0.0f) // < 0 hp
		m_health = 0.0f;
	if (m_health > 1.5f) // > 150 hp
		m_health = 1.5f;

	m_matrix = matrix;
	m_initialPosition = Vector4(matrix.pos.X, matrix.pos.Y, matrix.pos.Z, 1.0f);
	m_initialHeading = atan2(matrix.forward.X, matrix.forward.Z);

	m_skin = skin;

	m_bAddToFelonyManager = addToFelonyManager;
	m_bCreateFromStart = createFromStart;
	m_bDoNotUseIdleAnims = doNotUseIdleAnims;

	// custom automatic stuff
	if (felony > 0.001f)
	{
		m_bAddToFelonyManager = true;
	}

	// initial vehicle stuff
	m_vehiclePtr = initialVehicle;
	m_originalSeat = initialVehicleSeat;

	m_bPlayer = isPlayer;
	if (!m_bPlayer)
		m_ePlayerNumber = 0xefcdab0;
	else
		m_ePlayerNumber = playerNumber;

	if (!ignorePlayerRegister)
	{
		if (m_bPlayer)
		{
			auto ls = CLifeSystem::GetInstance();
			if (ls)
			{
				ls->RegisterPlayerActor(this); // register player

				// set spool centre
				ls->SetSpoolCentre(m_initialPosition.X, m_initialPosition.Z);
			}

			// player can do crime and go to jail!
			m_bAddToFelonyManager = true;
		}
	}

	if (!keepSkin)
	{
		auto srm = SpoolableResourceManager::GetInstance();
		if (srm != NULL)
		{
			// default skin if the target skin isn't loaded/present
			if (!srm->IsEntityPresent(SpooledPackageType_CharacterSkins, m_skin))
			{
				if (srm->IsEntityLoaded(SpooledPackageType_CharacterSkins, TheKid_Then))
					m_skin = TheKid_Then;
				if (srm->IsEntityLoaded(SpooledPackageType_CharacterSkins, TheDriver_Now))
					m_skin = TheDriver_Now;
			}

			Vector v2Pos; // MAv2
			v2Pos.X = m_initialPosition.X;
			v2Pos.Y = m_initialPosition.Z;
			srm->RequestEntity(SpooledPackageType_CharacterSkins, m_skin, (int)&v2Pos, ESpoolPriority_Required);
		}
	}

	if (createFromStart)
	{
		auto instances = GetLifeInstances();
		if (instances)
		{
			instances->AskForInstance(this, m_bCreateFromStart);
		}
	}

	m_positionChangePerGameStep = Vector4(0, 0, 0, 0);
	m_headingChangePerGameStep = 0;
	m_constrainPositionChange = false;

	m_crouch = false;
	m_cowerIfCrouched = false;
	m_strafeAndWeaponDrawn = false;

	auto ws = CWeaponsStore::GetInstance();
	if (ws)
	{
		CWeaponData* data = ws->weaponData(weapon);
		if (data != NULL)
		{
			m_weapon = CWeapon();
			m_weapon.Initialise(data, 999, true, 0);

			// this was when I was wrong about the CLifeActor_Character structure
			//m_weaponData.WeaponType = data->WeaponType;
			//m_weaponData.ModelID = data->ModelID;
			//m_weaponData.AmmoSize[0] = data->AmmoSize[0];
			//m_weaponData.AmmoSize[1] = data->AmmoSize[1];
			//m_weaponData.field16 = data->field16;
			//m_weaponData.field20 = data->field20;
			//m_weaponData.Range = data->Range;
			//m_weaponData.RateOfFire = data->RateOfFire;
			//m_weaponData.Automatic = data->Automatic;
			//m_weaponData.field36 = data->field36;
			//m_weaponData.Spread = data->Spread;
			//m_weaponData.MaxAmmo = data->MaxAmmo;
		}
	}

	m_shootIfWeaponDrawn = false;
	m_melee = false;
	m_weaponDrawn = false;
	m_targetInaccuracy = 0.0f;
	m_arrested = false;

	m_targetPosition = Vector4(0, 0, 0, 1);

	// unknown
	field0x5b0 = 4;
	field0x5b4 = 2;

	if (this == NULL)
	{
		m_pEntity = NULL;
	}

	// CLifeEntityManager->RegisterUpdate()
	((void(__thiscall*)(void*, void**))0x483bc8)(*(void**)(0x70c7bc), &m_pEntity);
}

Vector4 CLifeActor_Character::position(unsigned int gameStepIndex)
{
	Vector4 returnStorage = Vector4();

	((Vector4*(__thiscall*)(CLifeActor_Character*, Vector4*, unsigned int))0x474fd1)(this, &returnStorage, gameStepIndex);
	return returnStorage;
}

Vector4 CLifeActor_Character::GetPosition()
{
	void* Singleton_Time = *(void**)(0x70c5b0); // CGameTime *
	unsigned int gameStepIndex = *(int*)Singleton_Time + 0x4; // Singleton_Time->m_nGameFrame

	return position(gameStepIndex);
}