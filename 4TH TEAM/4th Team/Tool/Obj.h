#pragma once
#include	"Include.h"
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual HRESULT Initialize()	PURE;
	virtual int		Update()		PURE;
	virtual void	Late_Update()	PURE;
	virtual void	Render()	PURE;
	virtual void	Release()		PURE;


public:
	virtual	void	Collide(OBJID p_ID, CObj* p_Targ) PURE;

public:
	void			Set_Info(const INFO& p_Info)
	{
		m_tInfo = p_Info;
	}

	void			Set_ImgPath(const list<IMGPATH>& p_Info)
	{
		m_tImgPath = p_Info;
	}

	void			Set_ID(int p_id)
	{
		m_eID = (OBJID)p_id;
	}

	void			Set_Pos(const D3DXVECTOR3& p_V)
	{
		m_tInfo.vPos = p_V;
	}

public:
	const INFO&		Get_Info() { return m_tInfo; }

protected:
	tagFrame	m_tFrame;
	INFO		m_tInfo;
	list<IMGPATH>		m_tImgPath;

	OBJID		m_eID;

	bool		m_bDead;

};

