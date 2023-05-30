#include "stdafx.h"
#include "EditMgr.h"
#include	"TextureMgr.h"


CEditMgr::CEditMgr() : m_eType(EDIT_END)
{
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
			/*WriteFile(hFile, &Pair.second->byItem, sizeof(BYTE), &dwByte, nullptr);*/

			dwStringSize = sizeof(wchar_t) * (Pair.second.m_tPath.wstrPath.length() + 1);
			WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, Pair.second.m_tPath.wstrPath.c_str(), dwStringSize, &dwByte, nullptr);

			dwStringSize = sizeof(wchar_t) * (Pair.second.m_tPath.wstrObjKey.length() + 1);
			WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, Pair.second.m_tPath.wstrObjKey.c_str(), dwStringSize, &dwByte, nullptr);

			dwStringSize = sizeof(wchar_t) * (Pair.second.m_tPath.wstrStateKey.length() + 1);
			WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, Pair.second.m_tPath.wstrStateKey.c_str(), dwStringSize, &dwByte, nullptr);

			WriteFile(hFile, &Pair.second.m_tPath.iCount, sizeof(int), &dwByte, nullptr);


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
		//ReadFile(hFile, &pUnit->byItem, sizeof(BYTE), &dwByte, nullptr);

		pUnit.m_strName = pName;
		pUnit.m_tData.strName = pName;

		delete[]pName;
		pName = nullptr;

		ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);

		pName = new TCHAR[dwStringSize];
		ReadFile(hFile, pName, dwStringSize, &dwByte, nullptr);

		pUnit.m_tPath.wstrPath = pName;

		delete[]pName;
		pName = nullptr;

		ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);

		pName = new TCHAR[dwStringSize];
		ReadFile(hFile, pName, dwStringSize, &dwByte, nullptr);

		pUnit.m_tPath.wstrObjKey = pName;

		delete[]pName;
		pName = nullptr;

		ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);

		pName = new TCHAR[dwStringSize];
		ReadFile(hFile, pName, dwStringSize, &dwByte, nullptr);

		pUnit.m_tPath.wstrStateKey = pName;

		delete[]pName;
		pName = nullptr;

		ReadFile(hFile, &pUnit.m_tPath.iCount, sizeof(int), &dwByte, nullptr);



		m_mapBattle.insert({ pUnit.m_strName, pUnit });

		CTextureMgr::Get_Instance()->Insert_Texture(pUnit.m_tPath.GetPath().c_str(), TEX_SINGLE, pUnit.m_strName.c_str());

	}

	CloseHandle(hFile);
	AfxMessageBox(L"Load Successful");


}
