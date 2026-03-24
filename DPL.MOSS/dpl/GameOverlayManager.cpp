#include "GameOverlayManager.h"

COverheadMap* GetOverheadMap()
{
	return (COverheadMap*)(*(int*)(*(int*)(0x0070C558) + 0x34));
}

void COverheadMap::AddItem(SMapItem *item)
{
	((void(__thiscall*)(COverheadMap*, SMapItem*))0x4b9586)(this, item);
}

bool COverheadMap::GetItem(SMapItem *returnItem)
{
	return ((bool(__thiscall*)(COverheadMap*, SMapItem*))0x4b823f)(this, returnItem);
}

SMapItem* COverheadMap::FindItem(SMapItem* item)
{
	for (int i = 0; i < 32; i++)
	{
		SMapItem cItem = m_cMapMarkers.m_sItems[i];

		if (item->type == cItem.type)
		{
			if (item->position.X == cItem.position.X && item->position.Y == cItem.position.Z && item->position.Z == cItem.position.Z)
			{
				return &cItem;
			}
		}
	}
	return NULL;
}

CGameOverlayManager* GetGameOverlayManager()
{
	// 0x70C71C is what was meant to be here maybe?
	return (CGameOverlayManager*)(*(int*)(0x0070C558));
}

void CGameOverlayManager::Draw(int Viewport)
{
	((void(__thiscall*)(CGameOverlayManager*, int))0x4B7F36)(this, Viewport);
}

void CGameOverlayManager::Toggle(bool toggled)
{
	((void(__thiscall*)(CGameOverlayManager*, bool))0x5718A7)(this, toggled);
}

void CGameOverlay::ActivatePager()
{
	((void(__thiscall*)(CGameOverlay*))0x4B5DDD)(this);
}

// ???
//void COverheadMap_Hook::Draw(int Viewport)
//{
//	((void(__thiscall*)(COverheadMap_Hook*, int))0x4B9EF1)(this, Viewport);
//}
