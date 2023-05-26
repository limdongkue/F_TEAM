
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "Tool.h"

#include "MainFrm.h"
#include "ToolView.h"
#include	"Terrain.h"
#include	"MiniView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	// CreateStatic : ���� â�� ����� ���� �Լ�(�θ� ������ �ּ�, ���� ��, ���� ��, â ��Ÿ��, �ڽ�â id)
	//m_MainSplitter.CreateStatic(this, 1, 2);

	// CreateView : ���� â�� ǥ���� view â�� ����� �Լ�(��ġ�� ��, ��ġ�� ��, ��ġ�� viewâ�� ���� ũ��, �ʱ� ũ��, pContext)

	//m_MainSplitter.CreateView(0, 0, RUNTIME_CLASS(CMyForm), CSize(300, WINCY), pContext);
	//m_MainSplitter.CreateView(0, 1, RUNTIME_CLASS(CToolView), CSize(WINCX, WINCY), pContext);


	//m_MainSplitter.CreateStatic(this, 2, 2);

	//m_MainSplitter.CreateView(0, 0, RUNTIME_CLASS(CMiniView), CSize(300, 300), pContext);
	//m_MainSplitter.CreateView(0, 1, RUNTIME_CLASS(CMyForm), CSize(300, 300), pContext);

	//m_MainSplitter.CreateView(1, 0, RUNTIME_CLASS(CMyForm), CSize(300, 300), pContext);
	//m_MainSplitter.CreateView(1, 1, RUNTIME_CLASS(CToolView), CSize(WINCX, WINCY), pContext);

	m_MainSplitter.CreateStatic(this, 1, 2);

	m_MainSplitter.CreateView(0, 1, RUNTIME_CLASS(CToolView) , CSize(WINCX, WINCY), pContext);

	m_SecondSplitter.CreateStatic(&m_MainSplitter, 2, 1, 
									WS_CHILD | WS_VISIBLE, // WS_CHILD : �������� �ڽ� â, WS_VISIBLE | ���� �� �ٷ� ȭ�鿡 ǥ���ϰڴٴ� �ɼ�
									m_MainSplitter.IdFromRowCol(0, 0)); //: IdFromRowCol(��, ��) - ������ ��� ���� â id���� ��ȯ

	m_SecondSplitter.CreateView(0, 0, RUNTIME_CLASS(CMiniView), CSize(300, 300), pContext);

	m_SecondSplitter.CreateView(1, 0, RUNTIME_CLASS(CMyForm), CSize(300, 300), pContext);

	//SetColumnInfo(�� ��ȣ, ���� ũ�� ����, ��� ������ �ּ� ũ��)
	m_MainSplitter.SetColumnInfo(0, 300, 10);

	CToolView* pSrc = dynamic_cast<CToolView*>(m_MainSplitter.GetPane(0, 1));

	CMiniView* pTmp = dynamic_cast<CMiniView*>(m_SecondSplitter.GetPane(0, 0));

	
	return TRUE;
}
