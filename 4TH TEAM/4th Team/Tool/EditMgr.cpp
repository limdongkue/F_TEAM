#include "stdafx.h"
#include "EditMgr.h"
#include	"TextureMgr.h"
#include	"Device.h"
#include	"Terrain.h"


CEditMgr::CEditMgr() : m_eType(EDIT_END), m_vScrollPos({0,0,0})
{
	m_vCurPos = { 0, 0, 0 };
}


CEditMgr::~CEditMgr()
{
}

void CEditMgr::Save(CString p_string)
{
	{
		CString		strTemp = p_string;
		const TCHAR*	pGetPath = strTemp.GetString();

		HANDLE hFile = CreateFile(pGetPath,
			GENERIC_WRITE,
			0,
			nullptr,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			nullptr);


		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Save Failed");
			return;
		}


		DWORD dwByte = 0;
		DWORD dwStringSize = 0;
		DWORD dwSpriteLength = 0;

		for (auto& Pair : m_mapBattle)
		{
			// KEY 값 저장
			dwStringSize = sizeof(wchar_t) * (Pair.second.m_tData.strName.GetLength() + 1);
			WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, Pair.second.m_tData.strName.GetString(), dwStringSize, &dwByte, nullptr);

			// Value값 저장
			WriteFile(hFile, &Pair.second.m_tData.iAttack, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &Pair.second.m_tData.iHp, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &Pair.second.m_tData.byJobIndex, sizeof(BYTE), &dwByte, nullptr);
			WriteFile(hFile, &Pair.second.m_tData.byItem, sizeof(BYTE), &dwByte, nullptr);

			dwSpriteLength = Pair.second.m_tPath.size();

			WriteFile(hFile, &dwSpriteLength, sizeof(DWORD), &dwByte, nullptr);

			for (auto& iter : Pair.second.m_tPath)
			{
				dwStringSize = sizeof(wchar_t) * (iter.wstrPath.length() + 1);
				WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
				WriteFile(hFile, iter.wstrPath.c_str(), dwStringSize, &dwByte, nullptr);

				dwStringSize = sizeof(wchar_t) * (iter.wstrObjKey.length() + 1);
				WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
				WriteFile(hFile, iter.wstrObjKey.c_str(), dwStringSize, &dwByte, nullptr);

				dwStringSize = sizeof(wchar_t) * (iter.wstrStateKey.length() + 1);
				WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
				WriteFile(hFile, iter.wstrStateKey.c_str(), dwStringSize, &dwByte, nullptr);

				WriteFile(hFile, &iter.iCount, sizeof(int), &dwByte, nullptr);

			}



		}

		CloseHandle(hFile);
	}

	AfxMessageBox(L"Save Successful");

}

void CEditMgr::Load(CString p_string)
{

	m_mapBattle.clear();


	CString		strTemp = p_string;
	const TCHAR*	pGetPath = strTemp.GetString();

	HANDLE hFile = CreateFile(pGetPath,
		GENERIC_READ,
		0,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);


	if (INVALID_HANDLE_VALUE == hFile)
	{
		AfxMessageBox(L"Load Failed");
		return;
	}


	DWORD dwByte = 0;
	DWORD dwStringSize = 0;
	DWORD	dwSpriteLength = 0;
	BattleUnitCreator	pUnit = BattleUnitCreator();

	while (true)
	{
		// 키 값 불러오기
		ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);

		TCHAR* pName = new TCHAR[dwStringSize];
		ReadFile(hFile, pName, dwStringSize, &dwByte, nullptr);

		

		// Value값 불러오기
		pUnit =  BattleUnitCreator();

		if (0 == dwByte)
		{

			delete[]pName;
			pName = nullptr;
			break;
		}

		ReadFile(hFile, &pUnit.m_tData.iAttack, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &pUnit.m_tData.iHp, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &pUnit.m_tData.byJobIndex, sizeof(BYTE), &dwByte, nullptr);
		ReadFile(hFile, &pUnit.m_tData.byItem, sizeof(BYTE), &dwByte, nullptr);

		pUnit.m_strName = pName;
		pUnit.m_tData.strName = pName;

		delete[]pName;
		pName = nullptr;

		ReadFile(hFile, &dwSpriteLength, sizeof(DWORD), &dwByte, nullptr);

		pUnit.m_tPath.clear();

		for (size_t i = 0; i < dwSpriteLength; i++)
		{
			IMGPATH		pPath = IMGPATH();

			ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);

			pName = new TCHAR[dwStringSize];
			ReadFile(hFile, pName, dwStringSize, &dwByte, nullptr);
			pPath.wstrPath = pName;

			delete[]pName;
			pName = nullptr;

			ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);

			pName = new TCHAR[dwStringSize];
			ReadFile(hFile, pName, dwStringSize, &dwByte, nullptr);
			pPath.wstrObjKey = pName;

			delete[]pName;
			pName = nullptr;

			ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);

			pName = new TCHAR[dwStringSize];
			ReadFile(hFile, pName, dwStringSize, &dwByte, nullptr);
			pPath.wstrStateKey = pName;

			delete[]pName;
			pName = nullptr;

			ReadFile(hFile, &pPath.iCount, sizeof(int), &dwByte, nullptr);

			pUnit.m_tPath.push_back(pPath);
			CTextureMgr::Get_Instance()->Insert_Texture(pPath.wstrPath.c_str(), TEX_MULTI, pPath.wstrObjKey.c_str(), pPath.wstrStateKey.c_str(), pPath.iCount);
		}

		m_mapBattle.insert({ pUnit.m_strName, pUnit });

	}

	CloseHandle(hFile);
	AfxMessageBox(L"Load Successful");


}

void CEditMgr::Render(float posX, float posY)
{
	if (m_tCreator.m_strName == L"")
		return;

	auto iter = find_if(m_tCreator.m_tPath.begin(), m_tCreator.m_tPath.end(), [&](auto& Src)->bool
	{
		if (Src.wstrStateKey == L"대기_1")
			return true;
		else
			return false;
	});

	if (iter == m_tCreator.m_tPath.end())
		return;

	const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(iter->wstrObjKey.c_str(), iter->wstrStateKey.c_str(), 0);

	float	fX = pTexInfo->tImgInfo.Width / 2.f;
	float	fY = pTexInfo->tImgInfo.Height / 2.f;

	D3DXMATRIX matWorld;

	D3DXMatrixTranslation(&matWorld, m_vCurPos.x, m_vCurPos.y, 0);

	CTerrain::Set_Ratio(&matWorld, posX, posY);

	// 이미지에 행렬을 반영
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
		&D3DXVECTOR3(fX, fY, 0.f),			// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
		nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
		D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지


}
