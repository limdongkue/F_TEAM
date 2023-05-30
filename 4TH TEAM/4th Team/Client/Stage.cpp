#include "stdafx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Player_Client.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Image/Texture/Back/Tile/%d.png", 
		TEX_MULTI, L"Terrain", L"Tile", 216)))
	{
		ERR_MSG(L"Stage Tile Image Insert failed");
		return E_FAIL;
	}

	TCHAR	strTmp[MAX_PATH] = L"../Image/Texture/Unit/1�� ���/����/��ù�/";

	TCHAR	strDst[MAX_PATH] = L"";

	wstring		strSrc = strTmp;

	for (size_t i = 1; i < 6; i++)
	{
		wstring	strAtk = L"����_";

		strAtk += to_wstring(i);


		int tmp = 8;
		lstrcpy(strDst, strTmp);
		lstrcat(strDst, strAtk.c_str());
		lstrcat(strDst, L"/%d.png");

		if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(strDst,
			TEX_MULTI, L"��ù�", strAtk.c_str(), tmp)))
		{
			ERR_MSG(L"Stage Tile Image Insert failed");
			return E_FAIL;
		}

		wstring	strIdle = L"���_";

		//int tmp = fileinfo�� ���ϰ��� �˷��ִ°� 
		strIdle += to_wstring(i);


		tmp = 8;
		lstrcpy(strDst, strTmp);
		lstrcat(strDst, strIdle.c_str());
		lstrcat(strDst, L"/%d.png");

		// HRESULT CTextureMgr::Insert_Texture(const TCHAR * pFilePath, TEXTYPE eType, const TCHAR * pObjKey, const TCHAR * pStateKey, const int & iCount)

		if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(strDst,
			TEX_MULTI, L"��ù�", strIdle.c_str(), tmp)))
		{
			ERR_MSG(L"Stage Tile Image Insert failed");
			return E_FAIL;
		}

		wstring	strSkill = L"��ų_";

		//int tmp = fileinfo�� ���ϰ��� �˷��ִ°� 
		strSkill += to_wstring(i);


		tmp = 8;
		lstrcpy(strDst, strTmp);
		lstrcat(strDst, strSkill.c_str());
		lstrcat(strDst, L"/%d.png");

		// HRESULT CTextureMgr::Insert_Texture(const TCHAR * pFilePath, TEXTYPE eType, const TCHAR * pObjKey, const TCHAR * pStateKey, const int & iCount)

		if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(strDst,
			TEX_MULTI, L"��ù�", strSkill.c_str(), tmp)))
		{
			ERR_MSG(L"Stage Tile Image Insert failed");
			return E_FAIL;
		}

		wstring	strMove = L"�̵�_";

		//int tmp = fileinfo�� ���ϰ��� �˷��ִ°� 
		strMove += to_wstring(i);


		tmp = 8;
		lstrcpy(strDst, strTmp);
		lstrcat(strDst, strMove.c_str());
		lstrcat(strDst, L"/%d.png");

		// HRESULT CTextureMgr::Insert_Texture(const TCHAR * pFilePath, TEXTYPE eType, const TCHAR * pObjKey, const TCHAR * pStateKey, const int & iCount)

		if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(strDst,
			TEX_MULTI, L"��ù�", strMove.c_str(), tmp)))
		{
			ERR_MSG(L"Stage Tile Image Insert failed");
			return E_FAIL;
		}
		
	}

	CObj*	pObj = new CMyTerrain;

	if (nullptr == pObj)
		return E_FAIL;

	pObj->Initialize();
	
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::TERRAIN, pObj);

	// �÷��̾�
	pObj = new CPlayer_Client;
	if (nullptr == pObj)
		return E_FAIL;

	pObj->Initialize();

	CObjMgr::Get_Instance()->Add_Object(CObjMgr::PLAYER, pObj);
	
	return S_OK;
}

void CStage::Update_Scene()
{
	CObjMgr::Get_Instance()->Update();
}

void CStage::Late_Update_Scene()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render_Scene()
{
	CObjMgr::Get_Instance()->Render();
}

void CStage::Release_Scene()
{
}
