#pragma once
#include "afxwin.h"
#include "Include.h"

// CUnitTool ��ȭ �����Դϴ�.
class CMyForm;
class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPush();
	afx_msg void OnListBox();
	afx_msg void OnDestroy();
	afx_msg void OnSave();
	afx_msg void OnLoad();
	afx_msg void OnDelete();


public:
	CString m_strName;
	int m_iHp;
	int m_iAttack;

public:
	CListBox m_ListBox;
	CButton m_Radio[3];

public:
	map<CString, UNITDATA*>		m_mapUnitData;
	CMyForm*		m_pOwner;
	virtual void OnOK();
};
