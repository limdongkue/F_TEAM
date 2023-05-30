#include "stdafx.h"
#include "TextureMgr.h"



CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release();
}

const TEXINFO * CTextureMgr::Get_Texture(const TCHAR * pObjKey, const TCHAR * pStateKey, const int & iCount)
{
	auto	iter = find_if(m_mapTexture.begin(), m_mapTexture.end(), [&](auto& MyPair)->bool
	{
		if (pObjKey == MyPair.first)
			return true;

		return false;
	});

	if (iter == m_mapTexture.end())
		return nullptr;
	
	return iter->second->Get_Texture(pStateKey, iCount);
}

HRESULT CTextureMgr::Insert_Texture(const TCHAR * pFilePath, TEXTYPE eType, const TCHAR * pObjKey, const TCHAR * pStateKey, const int & iCount)
{
	auto	iter = find_if(m_mapTexture.begin(), m_mapTexture.end(), [&](auto& MyPair)->bool
	{
		if (pObjKey == MyPair.first)
			return true;

		return false;
	});

	if (iter == m_mapTexture.end())
	{
		CTexture*		pTexture = nullptr;

		switch (eType)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;

		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if (FAILED(pTexture->Insert_Texture(pFilePath, pStateKey, iCount)))
		{
			AfxMessageBox(pFilePath);
			return E_FAIL;
		}

		m_mapTexture.insert({ pObjKey, pTexture });

	}
	else if (eType == TEX_MULTI)
	{
		iter->second->Insert_Texture(pFilePath, pStateKey, iCount);
	}


	return S_OK;
}

int CTextureMgr::Find_TextSize(const TCHAR * pObjKey, const TCHAR * pStateKey)
{
	auto	iter = find_if(m_mapTexture.begin(), m_mapTexture.end(), [&](pair<wstring,CTexture*> MyPair)->bool
	{
		if (MyPair.first == pObjKey)
			return true;

		return false;
	});

	if (iter == m_mapTexture.end() || !dynamic_cast<CMultiTexture*>(iter->second))
		return -1;

	return dynamic_cast<CMultiTexture*>(iter->second)->Get_Size(pStateKey);


}

void CTextureMgr::Release(void)
{
	for_each(m_mapTexture.begin(), m_mapTexture.end(), [](auto& MyPair)
	{
		Safe_Delete(MyPair.second);
	});
	m_mapTexture.clear();

}
