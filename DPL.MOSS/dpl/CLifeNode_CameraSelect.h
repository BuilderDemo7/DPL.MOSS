#pragma once
#include "CLifeNode.h"
#include "CLifeActor.h"
#include "ICamera.h"

enum ECameraSelectType
{
	ECameraSelectType_UNDEFINED = -1,
	ECameraSelectType_CameraActor = 1,
	ECameraSelectType_VehicleCam = 2,
	ECameraSelectType_ThrillCam = 3,
	ECameraSelectType_IGCSOff = 4,
	ECameraSelectType_FPSCamera = 5,
};

enum ECameraSelect_VehicleCamType
{
	ECameraSelect_VehicleCamType_Bonnet = 1,
	ECameraSelect_VehicleCamType_Boot = 2,
	ECameraSelect_VehicleCamType_Chase = 3,
	ECameraSelect_VehicleCamType_Driver = 4,
	ECameraSelect_VehicleCamType_Bumper = 5,
	ECameraSelect_VehicleCamType_First = 6,
	ECameraSelect_VehicleCamType_LWheel = 7,
	ECameraSelect_VehicleCamType_RWheel = 8,
};

#pragma pack(push, 1)
class CLifeNode_CameraSelect : CLifeNode
{
public:
	void CustomInitalise(ECameraSelectType cameraType, CLifeActor* targetActor, ECameraSelect_VehicleCamType vehiclePosition = ECameraSelect_VehicleCamType_Bonnet, float speed = 1.0f, float zoom = 1.0f, float motionBlur = 0.0f, float duration = 60.0f, float blendTime = 0.0f);

	char __padding0[0x20];

	ECameraSelectType m_cameraType;
	CLifeActor* m_targetActor;
	ECameraSelect_VehicleCamType m_vehiclePosition;

	char __padding1[0x8];

	float m_fSpeed;
	float m_fZoom;
	float m_fMotionBlur;
	ICamera* m_Camera;
	int m_steps;
	int m_stepsToDeath;
	int m_blendSteps;
};
#pragma pack(pop)