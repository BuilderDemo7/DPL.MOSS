#pragma once

enum SpooledPackageType
{
	SpooledPackageType_Vehicles = 0,
	SpooledPackageType_Missions = 1,
	SpooledPackageType_CharacterSkins = 2,
	SpooledPackageType_CharacterAnimations = 3,
	SpooledPackageType_Audio = 4,
	SpooledPackageType_Localisation = 5,
	SpooledPackageType_Subtitles = 6,
	SpooledPackageType_numSpooledPackageTypes = 7,
	SpooledPackageType_Uninitialised = 8
};

enum ESpoolPriority
{
	ESpoolPriority_Uninitialised = 0,
	ESpoolPriority_Required = 1,
	ESpoolPriority_Preferred = 2,
};

class SpoolableResourceManager {
public:
	void SetEntityPriority(SpooledPackageType packageType, int ID, ESpoolPriority priority);
	void RequestEntity(SpooledPackageType packageType, int ID, int unk1, ESpoolPriority priority);
	bool IsEntityLoaded(SpooledPackageType packageType, int ID);
	bool IsEntityPresent(SpooledPackageType packageType, int ID);
	int GetStatus();
	static SpoolableResourceManager* GetInstance();
};