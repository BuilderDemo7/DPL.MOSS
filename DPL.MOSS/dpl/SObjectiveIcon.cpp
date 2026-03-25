#include "SObjectiveIcon.h"
#include "CGadgetHandler.h"
#include "CTargetManager.h"

#include <iostream>

void SetupObjectiveIcon(SObjectiveIcon* oicon, int displayType, int lifeEventType)
{
	if (lifeEventType == 2) {
		oicon->m_material = 0;
	}
	else if (lifeEventType == 3) {
		bool bIsLifeEventVisible = true;
		if (bIsLifeEventVisible) {
			oicon->m_material = 1;
		}
		else {
			oicon->m_material = 2;
		}
	}
	else {
		oicon->m_material = 0;
	}

	EGadgetType assetID = EGadgetType::POSITIONMARKERCONE;

	switch (displayType) {
	case 2:
		assetID = VEDIT;
		oicon->m_heightOffset = 1.5;
		break;
	default:
		oicon->m_bRotate = false;
		assetID = POSITIONMARKERTALLFAT;
		break;
	case 4:
		assetID = ARMOUREDCAR;
		oicon->m_heightOffset = 1.5;
		break;
	case 5:
		assetID = CIRCUITRACE;
		oicon->m_heightOffset = 1.5;
		break;
	case 6:
		assetID = HITMAN;
		oicon->m_heightOffset = 1.5;
		break;
	case 7:
		assetID = MOTOCROSS;
		oicon->m_heightOffset = 1.5;
		break;
	case 8:
		assetID = PERFECTDELIVERY;
		oicon->m_heightOffset = 1.5;
		break;
	case 10:
		assetID = REPOMAN;
		oicon->m_heightOffset = 1.5;
		break;
	case 0xb:
		assetID = SAFEHOUSE;
		oicon->m_heightOffset = 1.5;
		break;
	case 0xc:
		assetID = STICKUP;
		oicon->m_heightOffset = 1.5;
		break;
	case 0xd:
		assetID = STREETRACE;
		oicon->m_heightOffset = 1.5;
		break;
	case 0xe:
		assetID = TAXI;
		oicon->m_heightOffset = 1.5;
		break;
	case 0xf:
		assetID = LOANSHARK;
		oicon->m_heightOffset = 1.5;
		break;
	case 0x10:
		oicon->m_bRotate = false;
		assetID = POSITIONMARKERTALLSKINNY;
		break;
	case 0x11:
		oicon->m_bRotate = false;
		assetID = POSITIONMARKERSHORTSKINNY;
		break;
	case 0x13:
	case 0x16:
		oicon->m_bRotate = false;
		assetID = POSITIONMARKERSHORTFAT;
		break;
	case 0x14:
		oicon->m_bRotate = false;
		assetID = POSITIONMARKERCONE;
		break;
	case 0x15:
		assetID = PRISONTRANSPORT;
		oicon->m_heightOffset = 1.5;
		break;
	case 0x19:
		assetID = POSITIONMARKERSHORTFAT;
		oicon->m_material = 3;
		break;
	case 0x1a:
		assetID = POSITIONMARKERSHORTSKINNY;
		oicon->m_material = 3;
		break;
	case 0x1b:
		assetID = POSITIONMARKERTALLSKINNY;
		oicon->m_material = 3;
	}

	oicon->m_modelHandle = CGadgetHandler::GetInstance()->GetGadgetModelHandle(assetID);
}

void AutoRenderObjectiveIcon(SObjectiveIcon* oicon, Matrix* matrix, CPCViewport* piViewport)
{
	if (oicon->m_visibility != 3 && oicon->m_bParticleEffect == false)
	{
		CTargetManager* tman = CTargetManager::GetInstance();

		Matrix mtx = Matrix();

		mtx.right = Vector(1, 0, 0);
		mtx.up = Vector(0, 1, 0);
		mtx.forward = Vector(0, 0, 1);
		mtx.pos = matrix->pos;

		if (oicon->m_bRotate)
		{
			float fx = sin(oicon->m_rotation);
			float fz = cos(oicon->m_rotation);

			mtx.forward = Vector(fx, 0, fz);
			mtx.right = CrossProduct(Vector(0, 1, 0), mtx.forward);
			mtx.up = CrossProduct(mtx.forward, mtx.right);
		}

		mtx.pos.Y += oicon->m_heightOffset;
		tman->RenderObjectiveIcon(&mtx, piViewport, oicon);
	}
}