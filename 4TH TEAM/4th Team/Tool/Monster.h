#pragma once
#include "BattleUnit.h"
class CMonster :
	public CBattleUnit
{
public:
	CMonster();
	virtual ~CMonster();

	// CBattleUnit��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Collide(OBJID p_ID, CObj * p_Targ) override;
};

