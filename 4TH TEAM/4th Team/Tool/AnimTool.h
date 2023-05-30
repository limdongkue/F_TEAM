#pragma once
#include "afxwin.h"


// CAnimTool ��ȭ �����Դϴ�.

class CAnimTool : public CDialog
{
	DECLARE_DYNAMIC(CAnimTool)

public:
	CAnimTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAnimTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	afx_msg void OnChangeList();
	afx_msg void OnDropFiles(HDROP hDropInfo);

public:
	virtual BOOL OnInitDialog();
	void	Horizontal_Scroll();


public:
	CListBox m_ListBox;
	map<CString, CImage*> m_mapImg;

	int iDrawID = 0;
	CStatic m_AnimPicture;

};
