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

	m_pImage->Load(iter->second.m_tPath.GetPath().c_str());

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

		m_pImage->Load(iter->second.m_tPath.GetPath().c_str());

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
	CFileDialog	Dlg(FALSE,
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

		BattleUnitCreator&		tSrc = m_BC;


		lstrcpy(pGetPath, strTemp.GetString());

		PathRemoveFileSpec(pGetPath);

		CString strIndex = PathFindFileName(pGetPath);
		CString	strPathPlus = PathFindFileName(pGetPath);

		int i = 0;

		wchar_t	src = strIndex[0];

		for (; i < strIndex.GetLength(); ++i)
		{
			// isdigit : �Ű� ������ ���޹��� ���ڰ� ���������� �������� �ƴϸ� ���������� �������� �Ǻ��ϴ� �Լ�
			// ���������� ���ڷ� �Ǻ��ϸ� 0�� �ƴ� ���� ��ȯ

			if (0 != iswdigit(strIndex[i]))
				break;
		}

		// Delete(index, count) : �ε��� ��ġ�κ��� ī��Ʈ��ŭ ���ڸ� �����ϴ� �Լ�
		strIndex.Delete(0, i);
		strPathPlus.Delete(i, strPathPlus.GetLength());
		strPathPlus += L"%d";

		//_tstoi : ���ڸ� ���������� ��ȯ�ϴ� �Լ�
		tSrc.m_tPath.iCount = _tstoi(strIndex);


		PathRemoveFileSpec(pGetPath);

		CString		strSrc = PathFindFileName(pGetPath);
		
		CString		strFileName = PathFindFileName(strTemp);


		tSrc.m_tPath.wstrStateKey = strSrc;

		PathRemoveFileSpec(pGetPath);

		tSrc.m_tPath.wstrObjKey = pGetPath;

		TCHAR	szMy[MAX_PATH] = L"";

		GetCurrentDirectory(MAX_PATH, szMy);

		PathRemoveFileSpec(szMy);

		lstrcat(szMy, L"\\Image");

		CString strSTmp = CFileInfo::ConvertRelativePath(szMy);

		tSrc.m_tPath.wstrObjKey = CFileInfo::ConvertRelativePath(tSrc.m_tPath.wstrObjKey.c_str());

		tSrc.m_tPath.wstrObjKey.erase(0, strSTmp.GetLength() + 1);

		tSrc.m_tPath.wstrPath = strSTmp;

		tSrc.m_strName = PathFindFileName(tSrc.m_tPath.wstrObjKey.c_str());

		tSrc.m_tData.strName = tSrc.m_strName.c_str();


		CTextureMgr::Get_Instance()->Insert_Texture(tSrc.m_tPath.GetPath().c_str(), TEX_SINGLE, tSrc.m_strName.c_str());

		UpdateData(TRUE);

		if (m_pImage != nullptr)
		{
			m_pImage->Destroy();
			Safe_Delete(m_pImage);
		}

		m_pImage = new CImage;

		m_pImage->Load(tSrc.m_tPath.GetPath().c_str());

		m_SpriteImg.SetBitmap(*m_pImage);

		m_strName = tSrc.m_strName.c_str();

		UpdateData(FALSE);
		

	}
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
