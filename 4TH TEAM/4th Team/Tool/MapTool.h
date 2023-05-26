#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <atlimage.h>

// CMapTool ��ȭ �����Դϴ�.

class CDlgTab1;
class CDlgTab2;
class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMapTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void		 Horizontal_Scroll(void);

public:
	afx_msg void OnListBox();
	afx_msg void OnDropFiles(HDROP hDropInfo);

public:
	CTabCtrl m_tab;
	CDlgTab1* m_dlg1;
	CDlgTab2* m_dlg2;


	CStatic m_Picture;
	CListBox m_ListBox;
	map<CString, CImage*>	m_mapngImg;
	int						m_iDrawID = 0;

};
