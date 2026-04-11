#include "CLifeNode_CameraSelect.h"

void CLifeNode_CameraSelect::CustomInitalise(ECameraSelectType cameraType, CLifeActor* targetActor, ECameraSelect_VehicleCamType vehiclePosition, float speed, float zoom, float motionBlur, float duration, float blendTime)
{
	// base props
	m_cameraType = cameraType;
	m_vehiclePosition = vehiclePosition;

	// camera props
	m_targetActor = targetActor;
	m_fSpeed = speed;
	m_fZoom = zoom;
	m_fMotionBlur = motionBlur;

	// define duration/steps
	m_steps = 0;
	m_stepsToDeath = (int)(duration * 120.0f);
	m_blendSteps = (int)(blendTime * 120.0f);
	m_Camera = NULL;
}