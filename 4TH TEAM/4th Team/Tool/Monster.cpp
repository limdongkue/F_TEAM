#include "stdafx.h"
#include "Monster.h"
#include	"TextureMgr.h"
#include	"Terrain.h"
#include	"EditMgr.h"
#include	"Device.h"

CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

HRESULT CMonster::Initialize()
{
	return E_NOTIMPL;
}

int CMonster::Update()
{
	return 0;
}

void CMonster::Late_Update()
{
}

void CMonster::Render()
{
	auto iter = find_if(m_tImgPath.begin(), m_tImgPath.end(), [&](IMGPATH iter)->bool
	{
		if (iter.wstrStateKey == L"대기_1")
			return true;
		return false;
	});

	if (iter == m_tImgPath.end())
		return;

	const TEXINFO* src = CTextureMgr::Get_Instance()->Get_Texture(iter->wstrObjKey.c_str(), iter->wstrStateKey.c_str(), 0);

	D3DXMATRIX matWorld, matScale, matTrans;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CEditMgr::Get_Instance()->Get_Scroll().x, // 0일 경우 x 스크롤 값 얻어옴
		m_tInfo.vPos.y + CEditMgr::Get_Instance()->Get_Scroll().y, // 1일 경우 y 스크롤 값 얻어옴
		0.f);

	matWorld = matScale * matTrans;

	CTerrain::Set_Ratio(&matWorld, CEditMgr::Get_Instance()->Get_RatioX(), CEditMgr::Get_Instance()->Get_RatioY());

	float	fX = src->tImgInfo.Width / 2.f;
	float	fY = src->tImgInfo.Height / 2.f;

	// 이미지에 행렬을 반영
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(src->pTexture,
		nullptr,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
		&D3DXVECTOR3(fX, fY, 0.f),			// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
		nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
		D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지

}

void CMonster::Release()
{
}

void CMonster::Collide(OBJID p_ID, CObj * p_Targ)
{
}
