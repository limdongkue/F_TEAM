#include "stdafx.h"
#include "Obj.h"


CObj::CObj() : m_bDead(false), m_iCurTileIndex(0)
{
	ZeroMemory(&m_tFrame, sizeof(tagFrame));
	ZeroMemory(&m_tInfo, sizeof(tagInfo));
	
	D3DXMatrixIdentity(&m_tInfo.matWorld);
}


CObj::~CObj()
{
}
