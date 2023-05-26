// MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "DlgTab1.h"
#include "DlgTab2.h"


// CMapTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{

}

CMapTool::~CMapTool()
{
	Safe_Delete<CDlgTab1*>(m_dlg1);
	Safe_Delete<CDlgTab2*>(m_dlg2);
}

BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect	rect;
	m_tab.GetWindowRect(rect);

	m_tab.InsertItem(0, L"Tile");
	m_tab.InsertItem(1, L"None");

	m_tab.SetCurSel(0);

	m_dlg1 = new CDlgTab1;
	m_dlg1->Create(IDD_DIALOG1, &m_tab);
	m_dlg1->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_dlg1->ShowWindow(SW_HIDE);

	m_dlg2 = new CDlgTab2;
	m_dlg2->Create(IDD_DIALOG2, &m_tab);
	m_dlg2->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_dlg2->ShowWindow(SW_HIDE);

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMapTool::OnChangeTap)
END_MESSAGE_MAP()


// CMapTool �޽��� ó�����Դϴ�.


void CMapTool::OnChangeTap(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (IDD_MAPTOOL == pNMHDR->idFrom)
	{
		int iSelect = m_tab.GetCurSel();

		switch (iSelect)
		{
		case OBJID::OBJ_PLAYER:
			m_dlg1->ShowWindow(SW_SHOW);
			m_dlg2->ShowWindow(SW_HIDE);
			break;
		case OBJID::OBJ_BULLET:
			m_dlg1->ShowWindow(SW_HIDE);
			m_dlg2->ShowWindow(SW_SHOW);
			break;
		}

	}

	*pResult = 0;
}


