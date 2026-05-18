#pragma once
#include "Vector4.h"

enum EAttractorType
{
	EAttractorType_None = 0,
	EAttractorType_ParkedVehicle,
	EAttractorType_AntiParking,
	EAttractorType_Tree,
	EAttractorType_StreetLight,
	EAttractorType_TrafficLight,
	EAttractorType_Sound,
	EAttractorType_ParticleEffect,
	EAttractorType_VolumeParticleEffect,
	EAttractorType_Collectable,
	EAttractorType_CharacterSnapToLocation,
	EAttractorType_GunEffect,
	EAttractorType_GarageDisplayPosition,
	EAttractorType_SoundVolume,
	EAttractorType_EnvironmentLight,
	EAttractorType_ParkedPed,
	EAttractorType_NumberOf
};

namespace attractor
{
	struct Search
	{
		Vector4 m_where;
		EAttractorType m_type;
		float radius;
		bool m_search_static_structures;
		bool m_search_runtime_structures;

		char __padding0;
	};

	class Base
	{
	public:

		Vector4 GetPosition();
	};

	class AccessorObjectBase
	{
	public:
		void* __vtable;
		Base* m_nearest;
		float m_nearest_distSq;
	};
}

class AttractorManager
{
public:
	static AttractorManager* GetInstance();

	void FindAttractors(attractor::Search & searchSpec, attractor::AccessorObjectBase & result);
};