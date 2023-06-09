#pragma once
#include "UnitTool.h"
#include "MapTool.h"
#include "afxwin.h"


// CMyForm 폼 뷰입니다.

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnUnitTool();
	afx_msg void OnMapTool();


private:
	CFont	m_Font;
	CUnitTool	m_UnitTool;
	CMapTool	m_MapTool;
	
public:
	virtual void OnInitialUpdate();

	void		Closed_Edit();
	afx_msg void OnTileEdit();
	afx_msg void OnObjectEdit();
	CButton m_TypeBut[2];
};


