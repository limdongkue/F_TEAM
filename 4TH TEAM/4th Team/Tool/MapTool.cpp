// MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "DlgTab1.h"
#include "DlgTab2.h"
#include "FileInfo.h"
#include "TextureMgr.h"
#include "Device.h"
#include "EditMgr.h"

// CMapTool ��ȭ �����Դϴ�.

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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	TCHAR szTile[128] = L"";
	TCHAR szIndex[MIN_STR] = L"";

	for (UINT i = 0; i < 216; ++i)
	{
		TCHAR	szTile[128] = L"";
		TCHAR	szIndex[MIN_STR] = L"";
		swprintf_s(szIndex, L"%d", (int)i);
		lstrcat(szTile, szIndex);

		m_ListBox.AddString(szTile);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnSaveData)
END_MESSAGE_MAP()


// CMapTool �޽��� ó�����Դϴ�.



void CMapTool::OnListBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.


	int iIndex = m_ListBox.GetCurSel();
	if (iIndex == -1)
		return;

	CString strSelectName = L"";
	m_ListBox.GetText(iIndex, strSelectName);

	//auto iter = m_mapngImg.find(strSelectName);

	//m_Picture.SetBitmap(*(iter->second));


	int i = 0;
	for (; i < strSelectName.GetLength(); ++i)
		if (isdigit(strSelectName[i]))
			break;

	strSelectName.Delete(0, i);

	m_iDrawID = _wtoi(strSelectName.GetString());

	CEditMgr::Get_Instance()->Set_TileNum(m_iDrawID);

	CDevice::Get_Instance()->Render_Begin();

	const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", m_iDrawID);
	if (nullptr == pTexInfo)
		return;

	float scaleWidth = 4.f;  // ���� ũ�⸦ 2��� Ȯ��
	float scaleHeight = 4.f; // ���� ũ�⸦ 2��� Ȯ��

							  // �̹����� ũ�⿡ ���� Picture ��Ʈ���� ũ�� ����
	int pictureWidth = static_cast<int>(pTexInfo->tImgInfo.Width * scaleWidth);
	int pictureHeight = static_cast<int>(pTexInfo->tImgInfo.Height * scaleHeight);
	m_Picture.SetWindowPos(nullptr, 0, 0, pictureWidth, pictureHeight, SWP_NOMOVE | SWP_NOZORDER);



	D3DXMATRIX mScale, mWorld, mTrans;
	D3DXMatrixScaling(&mScale, WINCX / pTexInfo->tImgInfo.Width, WINCY / pTexInfo->tImgInfo.Height, 0.f);
	D3DXMatrixTranslation(&mTrans, 1.f, 1.f, 1.f);

	mWorld = mScale * mTrans;

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&mWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	CDevice::Get_Instance()->Render_End(m_Picture.m_hWnd);


	//UpdateData(TRUE);

	//int iIndex = m_ListBox.GetCurSel();

	//CEditMgr::Get_Instance()->Set_TileNum(iIndex);

	//CString	wstrFindName;

	//m_ListBox.GetText(iIndex, wstrFindName);

	//auto iter = m_mapngImg.find(wstrFindName);

	//m_Picture.SetBitmap(*(iter->second));

	//int i = 0;

	//for (; i < wstrFindName.GetLength(); ++i)
	//{
	//	if (isdigit(wstrFindName[i]))
	//		break;
	//}

	//wstrFindName.Delete(0, i);

	//m_iDrawID = _tstoi(wstrFindName);

	//const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", m_iDrawID);

	//if (nullptr == pTexInfo)
	//	return;

	//float fOriginalWidth = static_cast<float>(pTexInfo->tImgInfo.Width);
	//float fOriginalHeight = static_cast<float>(pTexInfo->tImgInfo.Height);

	//float fDisPlayWidth = fOriginalWidth * 4.f;
	//float fDisPlayHieght = fOriginalHeight * 4.f;

	//CRect rect;
	//m_Picture.GetClientRect(rect);
	//m_Picture.SetWindowPos(nullptr, rect.left, rect.top,
	//	(int)fDisPlayWidth, (int)fDisPlayHieght, SWP_NOMOVE | SWP_NOZORDER);
	//

	// �������

	//D3DXMATRIX matScale, matTrans, matWorld;

	//float fRatioX = WINCX / TILECX;
	//float fRatioY = WINCY / TILECY;

	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	//D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);
	//matWorld = matScale * matTrans;

	//float fCenterX = fDisPlayWidth * 0.5f;
	//float fCenterY = fDisPlayHieght * 0.5;

	//CDevice::Get_Instance()->Render_Begin();
	//CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	//CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
	//	nullptr,
	//	&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
	//	nullptr,
	//	D3DCOLOR_ARGB(255, 255, 255, 255));


	//CDevice::Get_Instance()->Render_End(m_Picture.m_hWnd);



	//CString	strSelectName;

	//int iSelect = m_ListBox.GetCurSel();

	//if (LB_ERR == iSelect)
	//	return;

	//m_ListBox.GetText(iSelect, strSelectName);

	//auto iter = m_mapngImg.find(strSelectName);

	//if (iter == m_mapngImg.end())
	//	return;

	//m_Picture.SetBitmap(*(iter->second));

	//int i = 0;

	//for (; i < strSelectName.GetLength(); ++i)
	//{
	//	if (0 != isdigit(strSelectName[i]))
	//		break;
	//}

	//strSelectName.Delete(0, i);

	//m_iDrawID = _tstoi(strSelectName);

	UpdateData(FALSE);

	
}


void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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

	Horizontal_Scroll();

	UpdateData(FALSE);

}


void CMapTool::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.


	for_each(m_mapngImg.begin(), m_mapngImg.end(), [](auto& MyPair)
	{
		MyPair.second->Destroy();
		Safe_Delete(MyPair.second);
	});

	m_mapngImg.clear();
}


void CMapTool::OnSaveData()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog		Dlg(FALSE,
		L"dat",
		L"*dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*dat) | *.dat||",
		this);

	TCHAR	szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		CString		strTemp = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = strTemp.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;
		
		CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*		pTool = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 0));
		CTerrain*		pTerrain = pTool->m_pTerrain;
		vector<TILE*>   vecTile = pTerrain->Get_VecTile();

		DWORD	dwByte = 0;

		for (auto& iter : vecTile)
			WriteFile(hFile, iter, sizeof(TILE), &dwByte, nullptr);

		CloseHandle(hFile);
		
	}

}
