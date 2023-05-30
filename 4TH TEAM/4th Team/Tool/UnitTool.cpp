// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"
#include	"MyForm.h"
#include	"EditMgr.h"
#include	"FileInfo.h"
#include	"TextureMgr.h"


// CUnitTool ��ȭ �����Դϴ�.

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
	//// m_mapUnitData�� ��� ��� ����
	//for (auto& pair : m_mapUnitData) {
	//	delete pair.second;
	//}
	//m_mapUnitData.clear();

	//// m_ListBox�� ��� ������ ����
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


// CUnitTool �޽��� ó�����Դϴ�.



void CUnitTool::OnPush()
{

	UpdateData(TRUE);


	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.





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

		AfxMessageBox(L"���ֵ����� ���� �Ϸ�");

		m_ListBox.SelectString(0, m_BC.m_strName.c_str());

		return;

	}

	m_ListBox.AddString(m_BC.m_strName.c_str());
	CEditMgr::Get_Instance()->Get_Map().insert({ m_BC.m_strName, m_BC });

	UpdateData(FALSE);

	AfxMessageBox(L"���ֵ����� �߰� �Ϸ�");


	m_ListBox.SelectString(0, m_BC.m_strName.c_str());


}


void CUnitTool::OnListBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString		strSelectName;

	// GetCurSel : ���� ����Ʈ �ڽ����� ���õ� ����� �ε����� ��ȯ
	int		iSelect = m_ListBox.GetCurSel();

	if (-1 == iSelect)
		return;

	// GetText : ���� �ε����� �ش��ϴ� ���ڿ��� ������ �Լ�
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
	lstrcat(strSrc, L"\\���_1\\0.png");


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

	//// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.


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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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

		// GetCurSel : ���� ����Ʈ �ڽ����� ���õ� ����� �ε����� ��ȯ
		int		iSelect = m_ListBox.GetCurSel();

		if (-1 == iSelect)
			return;


		// GetText : ���� �ε����� �ش��ϴ� ���ڿ��� ������ �Լ�
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
		lstrcat(strSrc,  L"\\���_1\\0.png");

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	int iIndex = m_ListBox.GetCurSel(); // ���� ����Ʈ �ڽ��� �ε��� ��ȯ

	if (LB_ERR == iIndex)
		return;

	CString wstrName = L"";
	m_ListBox.GetText(iIndex, wstrName);
	// GetText : ���� �ε����� �ش��ϴ� ���ڿ��� ������

	auto iter = CEditMgr::Get_Instance()->Get_Map().find(wstrName.GetString()); // ������ Ű �� ã��
	
	if (iter == CEditMgr::Get_Instance()->Get_Map().end())
		return;

	CEditMgr::Get_Instance()->Get_Map().erase(wstrName.GetString()); // erase
	m_ListBox.DeleteString(iIndex); // list�ڽ� �ε��� ����

	UpdateData(FALSE);
}




void CUnitTool::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.


	CDialog::OnOK();

	int iIndex = m_ListBox.GetCurSel(); // ���� ����Ʈ �ڽ��� �ε��� ��ȯ

	if (LB_ERR == iIndex)
		return;
	CString wstrName = L"";
	m_ListBox.GetText(iIndex, wstrName);

	auto iter = CEditMgr::Get_Instance()->Get_Map().find(wstrName.GetString()); // ������ Ű �� ã��

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

			wstring		strSrc = L"����_";

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

			strSrc = L"���_";

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

			strSrc = L"�̵�_";

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

			strSrc = L"��ų_";

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

		wstring		strSrc = L"����";

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

		strSrc = L"���_1\\0.png";

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
