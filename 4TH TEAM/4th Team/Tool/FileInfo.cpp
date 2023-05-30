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
	CFileFind Find;

	wstring	wstrFilePath = wstrPath + L"\\*.*";

	BOOL	bContinue = Find.FindFile(wstrFilePath.c_str());

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

void CFileInfo::DirInfoExtraction(const wstring & wstrPath, list<IMGPATH*>& rPathList)
{
	CFileFind	Find;

	wstring	wstrFilePath = wstrPath + L"\\*.*";

	BOOL	bContinue = Find.FindFile(wstrFilePath.c_str());

	while (bContinue)
	{
		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;
		else if (Find.IsDirectory())
			DirInfoExtraction(wstring(Find.GetFilePath()), rPathList);
		else
		{
			if (Find.IsSystem())
				continue;

			IMGPATH*	pImagePath = new IMGPATH;
			TCHAR		szPathBuf[MAX_STR] = L"";

			lstrcpy(szPathBuf, Find.GetFilePath().GetString());
			PathRemoveFileSpec(szPathBuf);

			pImagePath->iCount = CFileInfo::DirFileCnt(szPathBuf);

			wstring		wstrTextureName = Find.GetFileTitle().GetString();

			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.size() - 1) + L"%d.png";

			PathCombine(szPathBuf, szPathBuf, wstrTextureName.c_str());

			pImagePath->wstrPath = ConvertRelativePath(szPathBuf);

			PathRemoveFileSpec(szPathBuf);

			pImagePath->wstrStateKey = PathFindFileName(szPathBuf);

			PathRemoveFileSpec(szPathBuf);

			pImagePath->wstrObjKey = PathFindFileName(szPathBuf);

			rPathList.push_back(pImagePath);
			bContinue = FALSE;
		}
	}
}
