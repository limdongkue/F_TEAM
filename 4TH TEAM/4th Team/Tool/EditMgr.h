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

	void		Set_BUC(BattleUnitCreator& p_B)
	{
		m_tCreator = p_B;
	}

	map<wstring, BattleUnitCreator>&		Get_Map() { return m_mapBattle; }

	void		Save(CString p_string);
	void		Load(CString p_string);

private:
	EDIT_TYPE	m_eType;

	int			m_iTileNum;

	BattleUnitCreator	m_tCreator;

	map<wstring, BattleUnitCreator>	m_mapBattle;

};

