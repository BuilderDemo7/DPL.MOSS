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
	
	EFactoryType_Camera_MatrixOffset = 0x51,
	EFactoryType_Camera_Fixed = 0x52,
	EFactoryType_Camera_Tracking = 0x53,
	EFactoryType_Camera_Free = 0x55, // free camera!!
	
	EFactoryType_LifeInstance_Character = 0x88,
	EFactoryType_LifeInstance_Vehicle = 0x89,
	EFactoryType_LifeInstance_Volume = 0x8A,

	EFactoryType_LifeActor_Vehicle = 0x70,
	EFactoryType_LifeActor_Character = 0x72,
	EFactoryType_LifeActor_Marker = 0x7c,
	EFactoryType_LifeActor_Helicopter = 0x80,
	EFactoryType_LifeActor_Train = 0x83,
	EFactoryType_LifeActor_Prop = 0x7a,
	EFactoryType_LifeActor_TestVolume = 0x74,
	EFactoryType_LifeActor_Camera = 0x7d,

	EFactoryType_LifeNode_CameraSelect = 0x11f,
	EFactoryType_LifeNode_PlayAudio = 0xdd,
	EFactoryType_CharacterAttackLifeNode = 0x94,
	EFactoryType_VehiclePathMoveLifeNode = 0x9d,
};

namespace hamster
{
	void* CreateObject(EFactoryType eType);
}