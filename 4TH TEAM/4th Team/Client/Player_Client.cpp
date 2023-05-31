#include "stdafx.h"
#include "Player_Client.h"
#include "TextureMgr.h"
#include "Device.h"

CPlayer_Client::CPlayer_Client()
	: RMouseClick(false),
	MousePos(D3DXVECTOR3{0.f,0.f,0.f}),
	m_eUnitDir(UNIT_DIR::DIR_END),
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
	
	return S_OK;
}

int CPlayer_Client::Update(void)
{
	Key_Input();

	D3DXMATRIX	matScale, matRot, matTrans;

	D3DXMatrixScaling(&matScale, iReverse, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + __super::m_vScroll.x,
		m_tInfo.vPos.y + __super::m_vScroll.y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return 0;
}

void CPlayer_Client::Late_Update(void)
{
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
			Set_Motion(UNIT_STATETYPE::STATE_IDLE);
		/*	m_wstrStateKey = L"대기_1";*/
		}
	}
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

	__super::Move_Frame();
}

void CPlayer_Client::Render(void)
{
	//wstring strTemp = L"";

	//m_wstrStateKey = L"이동_1";

	TCHAR szPath[MAX_STR] = L"";

	swprintf_s(szPath, m_wstrStateKey.c_str(), m_iState);
	

	const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(),
		szPath, (int)m_tFrame.fFrame);

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
		MousePos = ::Get_Mouse();
		RMouseClick = true;

		D3DXVECTOR3 Dir = MousePos - m_tInfo.vPos;
		

		if (Dir.x < 0 && Dir.y < 0)
		{
			m_eUnitDir = DIR_LU;

			iReverse = 1.f;

			if (Dir.x < 30.f && Dir.x > -30.f)
			{
				m_eUnitDir = DIR_TOP;
			}

		}
		else if (Dir.x < 0 && Dir.y > 0)
		{
			m_eUnitDir = DIR_LD;

			iReverse = 1.f;

			if (Dir.x < 30.f && Dir.x > -30.f)
				m_eUnitDir = DIR_BOTTOM;
		}
		else if (Dir.x > 0 && Dir.y > 0)
		{
			m_eUnitDir = DIR_RD;

			iReverse = -1.f;

			if (Dir.x < 30.f && Dir.x > -30.f)
				m_eUnitDir = DIR_BOTTOM;
		}
		else if (Dir.x > 0 && Dir.y < 0)
		{
			m_eUnitDir = DIR_RU;
			
			iReverse = -1.f;

			if (Dir.x < 30.f && Dir.x > -30.f)
			{
				m_eUnitDir = DIR_TOP;
			}
		}


		if ((Dir.y > -30.f && Dir.y < 30.f) && Dir.x > 0)
		{
			m_eUnitDir = DIR_RIGHT;
			iReverse = -1.f;
		}
		else if ((Dir.y > -30.f && Dir.y < 30.f) && Dir.x < 0)
		{
			m_eUnitDir = DIR_LEFT;
			iReverse = 1.f;
		}

		D3DXVec3Normalize(&Dir, &Dir);


		float fAngle = acosf(Dir.x);
		if (m_tInfo.vDir.y < 0)
			fAngle = 2 * D3DX_PI - fAngle;

		fAngle = D3DXToDegree(fAngle);


		Set_Motion(UNIT_STATETYPE::STATE_MOVE);
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
		if (m_eUnitDir == DIR_LU)
			m_wstrStateKey = L"대기_3";
		if (m_eUnitDir == DIR_LD)
			m_wstrStateKey = L"대기_1";
		if (m_eUnitDir == DIR_RU)
			m_wstrStateKey = L"대기_3";
		if (m_eUnitDir == DIR_RD)
			m_wstrStateKey = L"대기_1";
		if (m_eUnitDir == DIR_RIGHT)
			m_wstrStateKey = L"대기_2";
		if (m_eUnitDir == DIR_LEFT)
			m_wstrStateKey = L"대기_2";
		break;
	case UNIT_STATETYPE::STATE_ATTAK:
		break;
	case UNIT_STATETYPE::STATE_HITED:
		break;
	case UNIT_STATETYPE::STATE_MOVE:
		if(m_eUnitDir == DIR_LU)
			m_wstrStateKey = L"이동_3";
		if (m_eUnitDir == DIR_LD)
			m_wstrStateKey = L"이동_1";
		if (m_eUnitDir == DIR_RU)
			m_wstrStateKey = L"이동_3";
		if (m_eUnitDir == DIR_RD)
			m_wstrStateKey = L"이동_1";
		if (m_eUnitDir == DIR_RIGHT)
			m_wstrStateKey = L"이동_2";
		if (m_eUnitDir == DIR_LEFT)
			m_wstrStateKey = L"이동_2";
		break;
	case UNIT_STATETYPE::STATE_SKILL:
		break;
	}
}
