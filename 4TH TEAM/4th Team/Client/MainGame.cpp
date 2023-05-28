#include "stdafx.h"
#include "MainGame.h"
#include "Device.h"

#include "SceneMgr.h"
#include "ObjMgr.h"
#include "TimeMgr.h"


CMainGame::CMainGame()
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * MIN_STR);
	m_iFps = 0;
}


CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Initialize(void)
{
	if (FAILED(CDevice::Get_Instance()->Initialize()))
	{
		ERR_MSG(L"Client Device Create Failed");
		return E_FAIL;
	}

	CTimeMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Change_SceneMgr(CSceneMgr::STAGE);

	/*
	#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
	FILE* nfp[3];
	freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
	freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
	freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
	std::ios::sync_with_stdio();
	}

	#endif // _DEBUG*/


	return S_OK;
}

void CMainGame::Update(void)
{
	CTimeMgr::Get_Instance()->Update();
	CSceneMgr::Get_Instance()->Update_SceneMgr();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update_SceneMgr();
}

void CMainGame::Render(void)
{
	//++m_iFps;

	CDevice::Get_Instance()->Render_Begin();

	CSceneMgr::Get_Instance()->Render_SceneMgr();

	CDevice::Get_Instance()->Render_End();
}

void CMainGame::Release(void)
{
#ifdef _DEBUG

	//FreeConsole();

#endif // _DEBUG


	/*m_pGraphicDev->Destroy_Instance();*/
}

