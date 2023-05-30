// AnimTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "AnimTool.h"
#include "ToolView.h"
#include "FileInfo.h"
#include "EditMgr.h"
#include "Device.h"
#include "TextureMgr.h"
#include "afxdialogex.h"


// CAnimTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAnimTool, CDialog)

CAnimTool::CAnimTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ANIMTOOL, pParent)
{
	//if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Image/Texture/Player/Attack_1/KimSimin0.png", TEX_MULTI, L"KimSimin_A1", L"ATTACK_1", 8)))
	//{
	//	AfxMessageBox(L"PlayerTexture Create Failed");
	//}
}

CAnimTool::~CAnimTool()
{
}

void CAnimTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICURE_ANIM, m_AnimPicture);
}


BEGIN_MESSAGE_MAP(CAnimTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CAnimTool::OnChangeList)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CAnimTool �޽��� ó�����Դϴ�.


void CAnimTool::OnChangeList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int iIndex = m_ListBox.GetCurSel();

	if (iIndex == -1)
		return;

	CString	strSelectName = L"";
	m_ListBox.GetText(iIndex, strSelectName);

	int i = 0;

	for (; i < strSelectName.GetLength(); ++i)
		if (isdigit(strSelectName[i]))
			break;

	strSelectName.Delete(0, i);

	iDrawID = _wtoi(strSelectName.GetString());

	CEditMgr::Get_Instance()->Set_AnimNum(iDrawID);

	CDevice::Get_Instance()->Render_Begin();

	const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"KimSimin_A1", L"ATTACK_1", iDrawID);
	if (nullptr == pTexInfo)
		return;

	float fScaleWidth = 1.f;
	float fScaleHeight = 1.f;

	int iPictureWidth = static_cast<int>(pTexInfo->tImgInfo.Width * fScaleWidth);
	int iPictureHeight = static_cast<int>(pTexInfo->tImgInfo.Height * fScaleHeight);

	m_AnimPicture.SetWindowPos(nullptr, 0, 0, iPictureWidth, iPictureHeight, SWP_NOMOVE | SWP_NOZORDER);

	D3DXMATRIX	mScale, mWorld, mTrans;
	D3DXMatrixScaling(&mScale, WINCX / pTexInfo->tImgInfo.Width, WINCY / pTexInfo->tImgInfo.Height, 0.f);
	D3DXMatrixTranslation(&mTrans, 1.f, 1.f, 1.f);

	mWorld = mScale * mTrans;

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&mWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CDevice::Get_Instance()->Render_End(m_AnimPicture.m_hWnd);

	UpdateData(FALSE);

}


void CAnimTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	UpdateData(TRUE);

	CDialog::OnDropFiles(hDropInfo);

	TCHAR	szFilePath[MAX_PATH] = L"";
	TCHAR	szFileName[MIN_STR] = L"";

	int iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

		CString	strRelative = CFileInfo::ConvertRelativePath(szFilePath);
		CString	strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto iter = m_mapImg.find(strFileName);

		if (iter == m_mapImg.end())
		{
			CImage*	pPngImg = new CImage;
			pPngImg->Load(strRelative);

			m_mapImg.insert({ strFileName, pPngImg });
			m_ListBox.AddString(szFileName);
		}
	}

	Horizontal_Scroll();

	UpdateData(FALSE);

}

void CAnimTool::Horizontal_Scroll()
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


BOOL CAnimTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Image/Texture/Player/Attack_1/KimSimin%d.png", TEX_MULTI, L"KimSimin_A1", L"ATTACK_1", 8)))
	{
		AfxMessageBox(L"PlayerTexture Create Failed");
	}
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
