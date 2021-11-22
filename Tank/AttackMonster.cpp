#include "stdafx.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "AttackMonster.h"

CAttackMonster::CAttackMonster()
{
}


CAttackMonster::~CAttackMonster()
{
}

void CAttackMonster::Initialize(void)
{
	
	m_Info.Width = 50.f;
	m_Info.Height = 50.f;
	m_Speed = 5.f;
	m_Type = OBJID::MONSTER;
	m_Cooltime = GetTickCount();

	
}

int CAttackMonster::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;
	m_Info.X += m_Speed;
	Update_Rect();
	return OBJ_NOEVENT;

}

void CAttackMonster::Late_Update(OBJLIST * _objlist)
{

	POINT temp{ m_Info.X, m_Info.Y };

	if (m_Cooltime + 1000 < GetTickCount())
	{
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp, 900, m_Type));
	//	_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp, 0, m_Type));
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp, 1050, m_Type));
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp, 750, m_Type));
		m_Cooltime = GetTickCount();
	}
	if ((0 >= m_Body.left) || (WINCX  <= m_Body.right))
		m_Speed *= -1.f;

	
}

void CAttackMonster::Render(HDC _hDC)
{


	Rectangle(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}



void CAttackMonster::Release(void)
{
}


