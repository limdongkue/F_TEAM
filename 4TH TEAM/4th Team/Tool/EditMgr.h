#pragma once
#include	"Include.h"

class CEditMgr
{
	SINGLETON(CEditMgr);


public:
	EDIT_TYPE	Get_EType() { return m_eType; }
	int			Get_TileNum() { return m_iTileNum; }

public:
	void		Set_EType(EDIT_TYPE p_Type)
	{
		m_eType = p_Type;
	}

	void		Set_TileNum(int p_I)
	{
		m_iTileNum = p_I;
	}

	BattleUnitCreator&		Get_BUC()
	{
		return m_tCreator;
	}

public: // Anim
	void	Set_AnimNum(int _Anim) { m_iAnimNum = _Anim; }
	

	int		Get_AnimNum()		   { return m_iAnimNum; }

	void		Set_BUC(BattleUnitCreator& p_B)
	{
		m_tCreator = p_B;
	}

	map<wstring, BattleUnitCreator>&		Get_Map() { return m_mapBattle; }

	void		Save(CString p_string);
	void		Load(CString p_string);

	void		Render(float posX, float posY);

	void		Set_CurPos(const D3DXVECTOR3& p_V)
	{
		if (m_vCurPos == p_V)
			return;
		m_vCurPos = p_V;
	}

	const D3DXVECTOR3&		Get_Pos() { return m_vCurPos; }

	void		Set_Ratio(float pX, float pY)
	{
		m_fRatioX = pX;
		m_fRatioY = pY;
	}

	const	float&	Get_RatioX() { return m_fRatioX; }
	const	float&	Get_RatioY() { return m_fRatioY; }


	void		Set_ScrollPos(const D3DXVECTOR3& p_V)
	{
		if (m_vScrollPos == p_V)
			return;
		m_vScrollPos = p_V;
	}

	const D3DXVECTOR3&		Get_Scroll() { return m_vScrollPos; }


private:
	EDIT_TYPE	m_eType;

	int			m_iTileNum;
	int			m_iAnimNum;

	D3DXVECTOR3		m_vCurPos;

	BattleUnitCreator	m_tCreator;

	map<wstring, BattleUnitCreator>	m_mapBattle;

	D3DXVECTOR3		m_vScrollPos;

	float			m_fRatioX, m_fRatioY;

};

