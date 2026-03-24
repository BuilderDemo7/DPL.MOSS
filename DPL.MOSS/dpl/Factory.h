#pragma once
enum EFactoryType
{
	EFactoryType_File,
	EFactoryType_ChunkBuffer,
	EObjectType_Renderer,
	EFactoryType_RuntimeModelModule,
	EFactoryType_OccluderModule,
	EFactoryType_Font,

	EFactoryType_Helicopter = 0x20
};

namespace hamster
{
	void* CreateObject(EFactoryType eType);
}