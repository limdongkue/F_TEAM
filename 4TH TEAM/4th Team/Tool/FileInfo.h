#pragma once
#include "Include.h"

class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();

public:
	static CString		ConvertRelativePath(CString strFullPath);

	static int DirFileCnt(const wstring & wstrPath);
};

