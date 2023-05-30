// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"
#include	"MyForm.h"
#include	"EditMgr.h"
#include	"FileInfo.h"
#include	"TextureMgr.h"


// CUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_strName(_T(""))
	, m_iHp(0)
	, m_iAttack(0), m_pImage(nullptr)
{

}

CUnitTool::~CUnitTool()
{
	//// m_mapUnitData의 모든 요소 해제
	//for (auto& pair : m_mapUnitData) {
	//	delete pair.second;
	//}
	//m_mapUnitData.clear();

	//// m_ListBox의 모든 아이템 삭제
	//m_ListBox.ResetContent();
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_iHp);
	DDX_Text(pDX, IDC_EDIT3, m_iAttack);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);
	DDX_Control(pDX, IDC_PICT, m_SpriteImg);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnPush)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnListBox)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnSave)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnLoad)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnDelete)

	ON_WM_DESTROY()

	ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::OnImgSelectClicked)
END_MESSAGE_MAP()


// CUnitTool 메시지 처리기입니다.



void CUnitTool::OnPush()
{

	UpdateData(TRUE);


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.





	m_BC.m_strName  = m_strName;
	m_BC.m_tData.strName = m_strName;
	m_BC.m_tData.iAttack = m_iAttack;
	m_BC.m_tData.iHp = m_iHp;

	
	for (int i = 0; i < 3; ++i)
	{
		if (m_Radio[i].GetCheck())
		{
			m_BC.m_tData.byJobIndex = i;
			break;
		}
	}

	auto iter = CEditMgr::Get_Instance()->Get_Map().find(m_strName.GetString());

	if (iter != CEditMgr::Get_Instance()->Get_Map().end())
	{
		iter->second = m_BC;
		UpdateData(FALSE);

		AfxMessageBox(L"유닛데이터 변경 완료");

		m_ListBox.SelectString(0, m_BC.m_strName.c_str());

		return;

	}

	m_ListBox.AddString(m_BC.m_strName.c_str());
	CEditMgr::Get_Instance()->Get_Map().insert({ m_BC.m_strName, m_BC });

	UpdateData(FALSE);

	AfxMessageBox(L"유닛데이터 추가 완료");


	m_ListBox.SelectString(0, m_BC.m_strName.c_str());


}


void CUnitTool::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString		strSelectName;

	// GetCurSel : 현재 리스트 박스에서 선택된 목록의 인덱스를 반환
	int		iSelect = m_ListBox.GetCurSel();

	if (-1 == iSelect)
		return;

	// GetText : 현재 인덱스에 해당하는 문자열을 얻어오는 함수
	m_ListBox.GetText(iSelect, strSelectName);

	auto	iter = CEditMgr::Get_Instance()->Get_Map().find(strSelectName.GetString());

	if (iter == CEditMgr::Get_Instance()->Get_Map().end())
		return;

	m_strName = iter->second.m_strName.c_str();
	m_iHp = iter->second.m_tData.iHp;
	m_iAttack = iter->second.m_tData.iAttack;

	for (int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE);

	m_Radio[iter->second.m_tData.byJobIndex].SetCheck(TRUE);

	if (m_pImage != nullptr)
	{
		m_pImage->Destroy();
		Safe_Delete(m_pImage);
	}

	m_pImage = new CImage;

	TCHAR		strSrc[MAX_PATH] = L"";

	lstrcpy(strSrc, iter->second.m_tPath.front().wstrPath.c_str());
	PathRemoveFileSpec(strSrc);
	PathRemoveFileSpec(strSrc);
	lstrcat(strSrc, L"\\대기_1\\0.png");


	if (!PathFileExists(strSrc))
	{
		m_pImage->Destroy();
		Safe_Delete(m_pImage);
		return;
	}
	m_pImage->Load(strSrc);

	m_SpriteImg.SetBitmap(*m_pImage);

	m_BC.m_tPath = iter->second.m_tPath;

	UpdateData(FALSE);
}

void CUnitTool::OnDestroy()
{
	CDialog::OnDestroy();

	//// TODO: 여기에 메시지 처리기 코드를 추가합니다.


	m_ListBox.ResetContent();

	m_pImage->Destroy();
	Safe_Delete(m_pImage);
}



void CUnitTool::OnSave()
{
	CFileDialog	Dlg(FALSE,
		L"dat",
		L"*dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat) | *.dat||",
		this);


	TCHAR	szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);

	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		CEditMgr::Get_Instance()->Save(Dlg.GetPathName().GetString());
	}

}


void CUnitTool::OnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);


	CFileDialog	Dlg(TRUE,
		L"dat",
		L"*dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat) | *.dat||",
		this);


	TCHAR	szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);

	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{

		m_ListBox.ResetContent();

		CEditMgr::Get_Instance()->Load(Dlg.GetPathName().GetString());

		map<wstring, BattleUnitCreator>& m_mapUnitData = CEditMgr::Get_Instance()->Get_Map();


		for (auto&	iter : m_mapUnitData)
		{
			m_ListBox.AddString(iter.second.m_strName.c_str());
		}


		m_ListBox.SelectString(0, CEditMgr::Get_Instance()->Get_Map().begin()->first.c_str());

		CString		strSelectName;

		// GetCurSel : 현재 리스트 박스에서 선택된 목록의 인덱스를 반환
		int		iSelect = m_ListBox.GetCurSel();

		if (-1 == iSelect)
			return;


		// GetText : 현재 인덱스에 해당하는 문자열을 얻어오는 함수
		m_ListBox.GetText(iSelect, strSelectName);

		auto	iter = m_mapUnitData.find(strSelectName.GetString());

		if (iter == m_mapUnitData.end())
			return;

		UpdateData(TRUE);

		m_strName = iter->second.m_strName.c_str();
		m_iHp = iter->second.m_tData.iHp;
		m_iAttack = iter->second.m_tData.iAttack;

		for (int i = 0; i < 3; ++i)
			m_Radio[i].SetCheck(FALSE);

		m_Radio[iter->second.m_tData.byJobIndex].SetCheck(TRUE);

		m_BC.m_tPath = iter->second.m_tPath;

		if (m_pImage != nullptr)
		{
			m_pImage->Destroy();
			Safe_Delete(m_pImage);
		}

		m_pImage = new CImage;

		TCHAR		strSrc[MAX_PATH] = L"";

		lstrcpy(strSrc, iter->second.m_tPath.front().wstrPath.c_str());
		PathRemoveFileSpec(strSrc);
		PathRemoveFileSpec(strSrc);
		lstrcat(strSrc,  L"\\대기_1\\0.png");

		if (!PathFileExists(strSrc))
		{
			m_pImage->Destroy();
			Safe_Delete(m_pImage);
			return;
		}
		m_pImage->Load(strSrc);
		m_SpriteImg.SetBitmap(*m_pImage);


		UpdateData(FALSE);
	}


}


void CUnitTool::OnDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int iIndex = m_ListBox.GetCurSel(); // 현재 리스트 박스의 인덱스 반환

	if (LB_ERR == iIndex)
		return;

	CString wstrName = L"";
	m_ListBox.GetText(iIndex, wstrName);
	// GetText : 현재 인덱스에 해당하는 문자열을 얻어오기

	auto iter = CEditMgr::Get_Instance()->Get_Map().find(wstrName.GetString()); // 삭제할 키 값 찾기
	
	if (iter == CEditMgr::Get_Instance()->Get_Map().end())
		return;

	CEditMgr::Get_Instance()->Get_Map().erase(wstrName.GetString()); // erase
	m_ListBox.DeleteString(iIndex); // list박스 인덱스 삭제

	UpdateData(FALSE);
}




void CUnitTool::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


	CDialog::OnOK();

	int iIndex = m_ListBox.GetCurSel(); // 현재 리스트 박스의 인덱스 반환

	if (LB_ERR == iIndex)
		return;
	CString wstrName = L"";
	m_ListBox.GetText(iIndex, wstrName);

	auto iter = CEditMgr::Get_Instance()->Get_Map().find(wstrName.GetString()); // 삭제할 키 값 찾기

	if (iter == CEditMgr::Get_Instance()->Get_Map().end())
		return;

	CEditMgr::Get_Instance()->Set_BUC(iter->second);


	for (auto& iter : m_pOwner->m_TypeBut)
	{
		iter.SetCheck(FALSE);
	}

	m_pOwner->m_TypeBut[1].SetCheck(TRUE);

	CEditMgr::Get_Instance()->Set_EType(EDIT_OBJECT);
	
}


void CUnitTool::OnImgSelectClicked()
{
	CFileDialog	Dlg(TRUE,
		L"png",
		L"*png",
		OFN_HIDEREADONLY,
		L"Data Files(*.png) | *.png||",
		this);

	TCHAR	szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);

	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Image\\Texture\\Unit");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		CString		strTemp = Dlg.GetPathName().GetString();
		TCHAR	pGetPath[MAX_PATH];

		m_BC.m_tPath.clear();

		IMGPATH		tSrc;


		for (size_t i = 1; i < 6; i++)
		{

			wstring		strSrc = L"공격_";

			strSrc += to_wstring(i);

			lstrcpy(pGetPath, strTemp.GetString());



			PathRemoveFileSpec(pGetPath);

			PathRemoveFileSpec(pGetPath);

			tSrc.wstrObjKey = PathFindFileName(pGetPath);

			tSrc.wstrStateKey = strSrc;

			PathCombine(pGetPath, pGetPath, strSrc.c_str());

			if (PathIsDirectory(pGetPath))
			{


				tSrc.iCount = CFileInfo::DirFileCnt(pGetPath);

				lstrcat(pGetPath, L"\\%d.png");

				tSrc.wstrPath = CFileInfo::ConvertRelativePath(pGetPath);

				m_BC.m_tPath.push_back(tSrc);

			}

			strSrc = L"대기_";

			strSrc += to_wstring(i);

			lstrcpy(pGetPath, strTemp.GetString());



			PathRemoveFileSpec(pGetPath);

			PathRemoveFileSpec(pGetPath);

			tSrc.wstrObjKey = PathFindFileName(pGetPath);

			tSrc.wstrStateKey = strSrc;


			PathCombine(pGetPath, pGetPath, strSrc.c_str());

			if (PathIsDirectory(pGetPath))
			{



				tSrc.iCount = CFileInfo::DirFileCnt(pGetPath);

				lstrcat(pGetPath, L"\\%d.png");

				tSrc.wstrPath = CFileInfo::ConvertRelativePath(pGetPath);

				m_BC.m_tPath.push_back(tSrc);

			}

			strSrc = L"이동_";

			strSrc += to_wstring(i);

			lstrcpy(pGetPath, strTemp.GetString());



			PathRemoveFileSpec(pGetPath);

			PathRemoveFileSpec(pGetPath);

			tSrc.wstrObjKey = PathFindFileName(pGetPath);

			tSrc.wstrStateKey = strSrc;


			PathCombine(pGetPath, pGetPath, strSrc.c_str());

			if (PathIsDirectory(pGetPath))
			{



				tSrc.iCount = CFileInfo::DirFileCnt(pGetPath);

				lstrcat(pGetPath, L"\\%d.png");

				tSrc.wstrPath = CFileInfo::ConvertRelativePath(pGetPath);

				m_BC.m_tPath.push_back(tSrc);

			}

			strSrc = L"스킬_";

			strSrc += to_wstring(i);

			lstrcpy(pGetPath, strTemp.GetString());



			PathRemoveFileSpec(pGetPath);

			PathRemoveFileSpec(pGetPath);

			tSrc.wstrObjKey = PathFindFileName(pGetPath);

			tSrc.wstrStateKey = strSrc;

			PathCombine(pGetPath, pGetPath, strSrc.c_str());

			if (PathIsDirectory(pGetPath))
			{




				tSrc.iCount = CFileInfo::DirFileCnt(pGetPath);

				lstrcat(pGetPath, L"\\%d.png");

				tSrc.wstrPath = CFileInfo::ConvertRelativePath(pGetPath);

				m_BC.m_tPath.push_back(tSrc);

			}


		}

		wstring		strSrc = L"죽음";

		lstrcpy(pGetPath, strTemp.GetString());



		PathRemoveFileSpec(pGetPath);

		PathRemoveFileSpec(pGetPath);

		tSrc.wstrObjKey = PathFindFileName(pGetPath);

		tSrc.wstrStateKey = strSrc;

		PathCombine(pGetPath, pGetPath, strSrc.c_str());

		if (PathIsDirectory(pGetPath))
		{

			tSrc.iCount = CFileInfo::DirFileCnt(pGetPath);

			lstrcat(pGetPath, L"\\%d.png");

			tSrc.wstrPath = CFileInfo::ConvertRelativePath(pGetPath);

			m_BC.m_tPath.push_back(tSrc);

		}

		strSrc = L"대기_1\\0.png";

		lstrcpy(pGetPath, strTemp.GetString());



		PathRemoveFileSpec(pGetPath);

		PathRemoveFileSpec(pGetPath);

		PathCombine(pGetPath, pGetPath, strSrc.c_str());

		UpdateData(TRUE);

		if (PathFileExists(pGetPath) && !m_BC.m_tPath.empty())
		{
			if (m_pImage != nullptr)
			{
				m_pImage->Destroy();
				Safe_Delete(m_pImage);
			}

			m_pImage = new CImage;

			m_pImage->Load(pGetPath);

			m_SpriteImg.SetBitmap(*m_pImage);

			m_strName = m_BC.m_tPath.front().wstrObjKey.c_str();

		}

		UpdateData(FALSE);


	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
