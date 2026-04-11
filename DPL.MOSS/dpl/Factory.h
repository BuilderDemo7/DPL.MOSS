#pragma once
enum EFactoryType
{
	EFactoryType_File,
	EFactoryType_ChunkBuffer,
	EObjectType_Renderer,
	EFactoryType_RuntimeModelModule,
	EFactoryType_OccluderModule,
	EFactoryType_Font,

	EFactoryType_Helicopter = 0x20, // actual helicopter
	EFactoryType_LifeInstance_Vehicle = 0x89,

	EFactoryType_LifeActor_Vehicle = 0x70,
	EFactoryType_LifeActor_Character = 0x72,
	EFactoryType_LifeActor_Helicopter = 0x80,
	EFactoryType_LifeActor_Train = 0x83,
	EFactoryType_LifeActor_Prop = 0x7a,

	EFactoryType_LifeNode_CameraSelect = 0x11f,
};

namespace hamster
{
	void* CreateObject(EFactoryType eType);
}