#include "stdafx.h"
#include "Player_Client.h"
#include "TextureMgr.h"
#include "Device.h"

CPlayer_Client::CPlayer_Client()
	: RMouseClick(false),
	MousePos(D3DXVECTOR3{0.f,0.f,0.f}),
	m_eUnitDir(UNIT_DIR::DIR_RIGHT),
	m_eUnitState(UNIT_STATETYPE::STATE_IDLE)
{
}


CPlayer_Client::~CPlayer_Client()
{
}

HRESULT CPlayer_Client::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	TCHAR	szPath[MAX_STR] = L"";

	m_wstrObjKey = L"김시민";
	m_wstrStateKey = L"대기_1";

	m_tFrame = { 0.f, 8.f };
	m_fSpeed = 3.f;

	iReverse = 1;
	
	return S_OK;
}

int CPlayer_Client::Update(void)
{


	Key_Input();

	switch (m_eUnitDir)
	{
	case DIR_BOTTOM:
		iDirection = 5;
		break;
	case DIR_RU:
		iReverse = -1;
	case DIR_LU:
		iDirection = 3;
		break;
	case DIR_RIGHT:
		iReverse = -1;
	case DIR_LEFT:
		iDirection = 2;
		break;
	case DIR_RD:
		iReverse = -1;
	case DIR_LD:
		iDirection = 1;
		break;
	case DIR_TOP:
		iDirection = 4;;
		break;
	case DIR_END:
		break;
	default:
		break;
	}



	const float fMaxDistance = 50.f;

	if (RMouseClick)
	{
		float fDistance = D3DXVec3Length(&(m_tInfo.vPos - MousePos));

		if (fDistance > fMaxDistance)
		{
			D3DXVECTOR3 targetDir = (MousePos - m_tInfo.vPos);
			D3DXVec3Normalize(&targetDir, &targetDir);

			m_tInfo.vPos += targetDir * m_fSpeed;
		}
		else
		{
			RMouseClick = false;
			m_eUnitState = STATE_IDLE;
			/*	m_wstrStateKey = L"대기_1";*/
		}
	}


	D3DXMATRIX	matScale, matRot, matTrans;

	D3DXMatrixScaling(&matScale, iReverse, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + __super::m_vScroll.x,
		m_tInfo.vPos.y + __super::m_vScroll.y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	__super::Move_Frame();


	return 0;
}

void CPlayer_Client::Late_Update(void)
{
	iReverse = 1;

	//m_tInfo.vDir = ::Get_Mouse() - m_tInfo.vPos;

	//D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	//D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	//float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);
	//float fAngle = acos(fDot);

	//if (m_tInfo.vPos.y < Get_Mouse().y)
	//	fAngle = 2 * D3DX_PI - fAngle;


	//float fDistance = D3DXVec3Length(&(m_tInfo.vPos - ::Get_Mouse()));

	//if (fDistance > fMaxDistance && RMouseClick)
	//{
	//	D3DXVECTOR3 targetDir = (::Get_Mouse() - m_tInfo.vPos);
	//	D3DXVec3Normalize(&targetDir, &targetDir);

	//	m_tInfo.vPos += targetDir * m_fSpeed;
	//	
	//	if ((int)fDistance <= (int)fMaxDistance + 2.f)
	//		RMouseClick = false;
	//	//m_tInfo.vPos.x += m_fSpeed * cos(fAngle);
	//	//m_tInfo.vPos.y -= m_fSpeed * sin(fAngle);
	//}

}

void CPlayer_Client::Render(void)
{
	//wstring strTemp = L"";

	//m_wstrStateKey = L"이동_1";


	Set_Motion(m_eUnitState);



	m_wstrStateKey += to_wstring(iDirection);
	

	const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(),
		m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	if (nullptr == pTexInfo)
		return;

	float	fX = pTexInfo->tImgInfo.Width * 0.5f;
	float	fY = pTexInfo->tImgInfo.Height * 0.5f;

	//D3DXMATRIX	mScale, mWorld, mTrans;
	//D3DXMatrixScaling(&mScale, WINCX / pTexInfo->tImgInfo.Width, WINCY / pTexInfo->tImgInfo.Height, 0.f);
	//D3DXMatrixTranslation(&mTrans, 1.f, 1.f, 1.f);

	//mWorld = mScale * mTrans;

	//CDevice::Get_Instance()->Get_Sprite()->SetTransform(&mWorld);

	//CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr,
	//	&D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	//CDevice::Get_Instance()->Render_End(m_AnimPicture.m_hWnd);

	//UpdateData(FALSE);

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fX, fY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));


}

void CPlayer_Client::Release(void)
{
}

void CPlayer_Client::Key_Input()
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		MousePos = Get_Mouse() - m_vScroll;
		RMouseClick = true;

		D3DXVECTOR3 Dir = MousePos - m_tInfo.vPos;

		D3DXVec3Normalize(&m_tInfo.vDir, &Dir);

		

		float fAngle = acosf(m_tInfo.vDir.x);
		if (m_tInfo.vDir.y < 0)
			fAngle = 2 * D3DX_PI - fAngle;

		fAngle = D3DXToDegree(fAngle);

		if (fAngle < 22.5f || fAngle >= 337.5f)
			m_eUnitDir = DIR_RIGHT;
		else if (fAngle >= 22.5f && fAngle < 67.5f)
			m_eUnitDir = DIR_RD;
		else if (fAngle >= 67.5f && fAngle < 112.5f)
			m_eUnitDir = DIR_BOTTOM;
		else if (fAngle >= 112.5f && fAngle < 157.5f)
			m_eUnitDir = DIR_LD;
		else if (fAngle >= 157.5f && fAngle < 202.5f)
			m_eUnitDir = DIR_LEFT;
		else if (fAngle >= 202.5f && fAngle < 247.5f)
			m_eUnitDir = DIR_LU;
		else if (fAngle >= 247.5f && fAngle < 292.5f)
			m_eUnitDir = DIR_TOP;
		else if (fAngle >= 292.5f && fAngle < 337.5f)
			m_eUnitDir = DIR_RU;


		m_eUnitState = STATE_MOVE;
	}

}

void CPlayer_Client::Set_Motion(UNIT_STATETYPE _eState)
{
	// switch문을 만들 때, 먼저 방향을 받고 
	// 그 방향 안에서 switch문을 State 중첩해서 Sprite를 바꾼다.
	// m_wstrStateKey = 를 스위치 문에서 바꿔줘야함.

	switch (_eState)
	{
	case UNIT_STATETYPE::STATE_IDLE:
		m_wstrStateKey = L"대기_";
		break;
	case UNIT_STATETYPE::STATE_ATTAK:
		m_wstrStateKey = L"공격";
		break;
	case UNIT_STATETYPE::STATE_HITED:
		m_wstrStateKey = L"피격_";

		break;
	case UNIT_STATETYPE::STATE_MOVE:

		m_wstrStateKey = L"이동_";

		break;
	case UNIT_STATETYPE::STATE_SKILL:

		m_wstrStateKey = L"스킬_";

		break;

	default:
		break;
	}
}
