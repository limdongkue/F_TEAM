// MyForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"
#include	"EditMgr.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{
}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO2, m_TypeBut[0]);
	DDX_Control(pDX, IDC_RADIO1, m_TypeBut[1]);

}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnUnitTool)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyForm::OnMapTool)
	ON_BN_CLICKED(IDC_RADIO2, &CMyForm::OnTileEdit)
	ON_BN_CLICKED(IDC_RADIO1, &CMyForm::OnObjectEdit)
END_MESSAGE_MAP()


void CMyForm::OnUnitTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (nullptr == m_UnitTool.GetSafeHwnd())
	{
		m_UnitTool.Create(IDD_UNITTOOL);
		m_UnitTool.m_pOwner = this;
	}

	m_UnitTool.ShowWindow(SW_SHOW);
	m_UnitTool.m_Radio[0].SetCheck(TRUE);
	CEditMgr::Get_Instance()->Set_EType(EDIT_TILE);

}

void CMyForm::OnMapTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_MapTool.GetSafeHwnd())
		m_MapTool.Create(IDD_MAPTOOL);

	m_MapTool.ShowWindow(SW_SHOW);
}

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	m_Font.CreatePointFont(150, L"�ü�");

	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON5)->SetFont(&m_Font);

	m_TypeBut[0].SetCheck(TRUE);

}

void CMyForm::Closed_Edit()
{
	switch (CEditMgr::Get_Instance()->Get_EType())
	{	
	case EDIT_TILE: 
		m_TypeBut[0].SetCheck(TRUE);
		break;

	case EDIT_OBJECT:
		m_TypeBut[1].SetCheck(TRUE);

		break;

	default:
		break;
	}
}

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CMyForm::OnTileEdit()
{
	CEditMgr::Get_Instance()->Set_EType(EDIT_TILE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMyForm::OnObjectEdit()
{
	CEditMgr::Get_Instance()->Set_EType(EDIT_OBJECT);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
