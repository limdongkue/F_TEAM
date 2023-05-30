#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

CString CFileInfo::ConvertRelativePath(CString strFullPath)
{

	TCHAR	szRelativePath[MAX_PATH] = L"";
	TCHAR	szCurDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szCurDirPath);

	PathRelativePathTo(szRelativePath,
		szCurDirPath,
		FILE_ATTRIBUTE_DIRECTORY,
		strFullPath.GetString(),
		FILE_ATTRIBUTE_DIRECTORY);

	
	return CString(szRelativePath);
}

int CFileInfo::DirFileCnt(const wstring & wstrPath)
{
	CFileFind			Find;

	wstring		wstrFilePath = wstrPath + L"\\*.*";

	// FindFile : �־��� ��ο� ������ ������ �Ǵ��ϴ� �Լ�, ������ ������ FALSE�� ����
	// ���� �ľ� ��, ���� �� ���Ͽ� �����ϰ� ���� ��쿣 �ݵ�� FindNextfile �Լ��� ������ ȣ���ؾ� �Ѵ�.

	BOOL		bContinue = Find.FindFile(wstrFilePath.c_str());

	int iFileCnt = 0;

	while (bContinue)
	{
		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;

		if (Find.IsSystem())
			continue;

		++iFileCnt;

	}

	return iFileCnt;
}
