#pragma once
#include "afxwin.h"


// CAnimTool 대화 상자입니다.

class CAnimTool : public CDialog
{
	DECLARE_DYNAMIC(CAnimTool)

public:
	CAnimTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAnimTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
