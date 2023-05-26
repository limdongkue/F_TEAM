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
	TCHAR		szRelativePath[MAX_PATH] = L""; // 상대 경로를 저장할 문자배열
	TCHAR		szCurDirPath[MAX_PATH] = L""; // 현재 절대 경로를 저장할 문자배열

	GetCurrentDirectory(MAX_PATH, szCurDirPath);

	// szCurDirPath 에서 strFullPath.GetString()으로 가는 상대 경로를 구해서 szRelativePath 저장해주는 함수(단, 같은 드라이브 내에서만 변경 가능)

	PathRelativePathTo(szRelativePath,
		szCurDirPath,
		FILE_ATTRIBUTE_DIRECTORY,
		strFullPath.GetString(),
		FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelativePath);
}
