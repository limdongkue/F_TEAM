#pragma once
#include "Obj.h"
class CMyTerrain :	public CObj
{
public:
	CMyTerrain();
	virtual ~CMyTerrain();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

private:
	HRESULT			LoadTile(const TCHAR* pTilePath);

private:
	vector<TILE*>		m_vecTile;
};

