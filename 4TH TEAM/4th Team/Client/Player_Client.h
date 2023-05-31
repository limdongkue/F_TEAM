#pragma once
#include "Obj.h"
class CPlayer_Client :
	public CObj
{
public:
	CPlayer_Client();
	virtual ~CPlayer_Client();

public:
	virtual HRESULT		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(void);
	virtual void		Render(void);
	virtual void		Release(void);

private:
	void	Key_Input();
	void	Set_Motion(UNIT_STATETYPE _eState);

public:
	bool	RMouseClick;

private:
	D3DXVECTOR3	MousePos;

	UNIT_DIR m_eUnitDir;
	UNIT_STATETYPE m_eUnitState;

	int iReverse = 1.f;
	int	iDirection = 0;
};

