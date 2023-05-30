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
		if (iter.wstrStateKey == L"���_1")
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
		m_tInfo.vPos.x + CEditMgr::Get_Instance()->Get_Scroll().x, // 0�� ��� x ��ũ�� �� ����
		m_tInfo.vPos.y + CEditMgr::Get_Instance()->Get_Scroll().y, // 1�� ��� y ��ũ�� �� ����
		0.f);

	matWorld = matScale * matTrans;

	CTerrain::Set_Ratio(&matWorld, CEditMgr::Get_Instance()->Get_RatioX(), CEditMgr::Get_Instance()->Get_RatioY());

	float	fX = src->tImgInfo.Width / 2.f;
	float	fY = src->tImgInfo.Height / 2.f;

	// �̹����� ����� �ݿ�
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(src->pTexture,
		nullptr,							// ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0 �������� ���
		&D3DXVECTOR3(fX, fY, 0.f),			// ����� �̹����� �߽��࿡ ���� vector3 �ּ�, null�� ��� �̹����� 0, 0�� �߽� ��ǥ
		nullptr,							// ��ġ ��ǥ�� ���� vector3 �ּ�, null�� ��� ��ũ�� ���� 0, 0��ǥ ���
		D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� ���� ����

}

void CMonster::Release()
{
}

void CMonster::Collide(OBJID p_ID, CObj * p_Targ)
{
}
