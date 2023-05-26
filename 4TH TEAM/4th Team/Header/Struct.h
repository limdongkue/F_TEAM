#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vSize;

	D3DXMATRIX		matWorld;
}INFO;

typedef	struct tagFrame
{
	float		fFrame; // 프레임을 세기 위한 변수
	float		fMax;	// 최대 이미지의 프레임 수

}FRAME;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;   // 컴 객체

	D3DXIMAGE_INFO			tImgInfo;	// 구조체

}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;
	D3DXVECTOR3 vSize;

	BYTE		byOption;
	BYTE		byDrawID;
}TILE;

typedef	struct tagUnitData
{
	CString	strName = L"";
	int		iAttack = 0;
	int		iHp = 0;
	BYTE	byJobIndex = 0;
	BYTE	byItem = 0;

}UNITDATA;

typedef struct tagTexturePath
{
	wstring		wstrObjKey		= L"";
	wstring		wstrStateKey	= L"";
	wstring		wstrPath = L"";
	int			iCount = 0;

	wstring		GetPath()
	{
		wstring src = L"";

		src = wstrPath + L"\\" + wstrObjKey + L"\\" + wstrStateKey + L"\\" + to_wstring(iCount) + L".png";
		return src;
	}

}IMGPATH;


static D3DXVECTOR3		Get_Mouse()
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3((float)Pt.x, (float)Pt.y, 0.f);
}

struct BattleUnitCreator
{
	UNITDATA	m_tData;
	IMGPATH		m_tPath;
	wstring		m_strName = L"";

};