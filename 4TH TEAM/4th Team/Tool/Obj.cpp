#include "stdafx.h"
#include "Obj.h"


CObj::CObj() : m_bDead(false), m_eID(OBJ_END)
{
	ZeroMemory(&m_tFrame, sizeof(tagFrame));
	ZeroMemory(&m_tInfo, sizeof(tagInfo));

	m_tInfo.vDir = { 1, 0, 0 };
	
	D3DXMatrixIdentity(&m_tInfo.matWorld);
}


CObj::~CObj()
{
}
