// MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "ToolView.h"
#include "afxdialogex.h"
#include "DlgTab1.h"
#include "DlgTab2.h"
#include "FileInfo.h"

// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{

}

CMapTool::~CMapTool()
{
}

BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMapTool::Horizontal_Scroll(void)
{
	CString	strName;
	CSize	Size;

	int		iWidth = 0;

	CDC*	pDC = m_ListBox.GetDC();

	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);

		Size = pDC->GetTextExtent(strName);

		if (Size.cx > iWidth)
			iWidth = Size.cx;
	}

	m_ListBox.ReleaseDC(pDC);

	if (iWidth > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iWidth);
}


void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_WM_DESTROY()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnListBox)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.



void CMapTool::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString	strSelectName;

	int iSelect = m_ListBox.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	m_ListBox.GetText(iSelect, strSelectName);

	auto iter = m_mapngImg.find(strSelectName);

	if (iter == m_mapngImg.end())
		return;

	m_Picture.SetBitmap(*(iter->second));

	int i = 0;

	for (; i < strSelectName.GetLength(); ++i)
	{
		if (0 != isdigit(strSelectName[i]))
			break;
	}

	strSelectName.Delete(0, i);

	m_iDrawID = _tstoi(strSelectName);

	UpdateData(FALSE);
}


void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);

	CDialog::OnDropFiles(hDropInfo);

	TCHAR	szFilePath[MAX_PATH] = L"";
	TCHAR	szFileName[MIN_STR] = L"";

	int		iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

		CString	strRelative = CFileInfo::ConvertRelativePath(szFilePath);
		CString strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto iter = m_mapngImg.find(strFileName);

		if(iter == m_mapngImg.end())
		{
			CImage*	pPngImg = new CImage;
			pPngImg->Load(strRelative);

			m_mapngImg.insert({ strFileName, pPngImg });
			m_ListBox.AddString(szFileName);
		}
	}



}
