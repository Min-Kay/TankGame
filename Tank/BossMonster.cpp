#include "stdafx.h"
#include "BossMonster.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "GuideBullet.h"
#include "SrecwBullet.h"
#include "MonsterBullet.h"
CBossMonster::CBossMonster()
{
}


CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	m_Info.Width = 50.f;
	m_Info.Height = 50.f;
	m_Speed = 3.f;
	m_Type = OBJID::MONSTER;
	m_Radian = 15.f;
	m_Distance  =60.f;
	m_Cooltime = GetTickCount();
	m_Shottime = GetTickCount();
	m_Time = GetTickCount();
	m_Radian = 900;
}

int CBossMonster::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;
	m_Radian += 10.f;
m_Info.X += m_Speed;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBossMonster::Late_Update(OBJLIST * _objlist)
{

	POINT temp{ m_Info.X, m_Info.Y +30};
	POINT temp2{ m_Info.X+80, m_Info.Y + 20 };
	POINT temp3{ m_Info.X + 46, m_Info.Y + 20 };

	POINT temp4{ m_Info.X+70, m_Info.Y + 20 };
	POINT temp5{ m_Info.X-80, m_Info.Y + 20 };//¿ÞÂÊ ³¡
	POINT temp6{ m_Info.X-70, m_Info.Y + 20 }; // ¿ÞÂÊ 2¹ø¤Š
	POINT temp7{ m_Info.X - 40, m_Info.Y + 20 }; 
	if (m_Cooltime + 400 < GetTickCount())
	{
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp, 900, m_Type));
		
		

		m_Cooltime = GetTickCount();
	}
	if (m_Shottime + 3000 < GetTickCount()) {

		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp2, 900, m_Type));
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp3, 900, m_Type));
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp4, 900, m_Type));
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp5, 900, m_Type));
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp6, 900, m_Type));
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp7, 900, m_Type));
		m_Shottime = GetTickCount();
	}

	POINT Skill{ m_Info.X, m_Info.Y + 30 };
	DWORD Skill_Time = GetTickCount();
	if (m_Time + 4000 < GetTickCount()) {

	
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CMonsterBullet>::Create(Skill, 900, m_Type));
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CMonsterBullet>::Create(Skill, 750, m_Type));
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CMonsterBullet>::Create(Skill, 1050, m_Type));
	
		m_Time = GetTickCount();
	}
	if ((80 >= m_Body.left) || (WINCX -80<= m_Body.right))
		m_Speed *= -1.f;
}

void CBossMonster::Render(HDC _hDC)
{
	
	Ellipse(_hDC, m_Body.left-20, m_Body.top-20, m_Body.right+20, m_Body.bottom+20);
	Ellipse(_hDC, m_Body.left-70, m_Body.top+28, m_Body.right-90, m_Body.bottom+3);
	Ellipse(_hDC, m_Body.left -55, m_Body.top + 28, m_Body.right - 75, m_Body.bottom + 3);
	Ellipse(_hDC, m_Body.left - 30, m_Body.top + 28, m_Body.right - 50, m_Body.bottom + 3);
	Ellipse(_hDC, m_Body.left + 70, m_Body.top + 28, m_Body.right + 50, m_Body.bottom + 3);
	Ellipse(_hDC, m_Body.left + 55, m_Body.top + 28, m_Body.right + 35, m_Body.bottom + 3);
	Ellipse(_hDC, m_Body.left + 90, m_Body.top + 28, m_Body.right + 70, m_Body.bottom + 3);
	Ellipse(_hDC, m_Body.left+20, m_Body.top + 50, m_Body.right-20, m_Body.bottom +25);
	Rectangle(_hDC, m_Body.left + 20, m_Body.top -40, m_Body.right - 20, m_Body.bottom - 49);
	MoveToEx(_hDC, m_Info.X -6, m_Info.Y - 54, NULL);
	LineTo(_hDC, m_Info.X -26, m_Info.Y - 53);
	LineTo(_hDC, m_Info.X - 18, m_Info.Y - 28);
	MoveToEx(_hDC, m_Info.X + 6, m_Info.Y - 54, NULL);
	LineTo(_hDC, m_Info.X + 26, m_Info.Y - 53);
	LineTo(_hDC, m_Info.X + 18, m_Info.Y - 28);

	MoveToEx(_hDC, m_Info.X-32, m_Info.Y-10, NULL);
	LineTo(_hDC, m_Info.X+32, m_Info.Y-10 );
	MoveToEx(_hDC, m_Info.X-35, m_Info.Y+5, NULL);
	LineTo(_hDC, m_Info.X +35, m_Info.Y+5 );
	MoveToEx(_hDC, m_Info.X -15, m_Info.Y - 10, NULL);
	LineTo(_hDC, m_Info.X -10, m_Info.Y +5);
	MoveToEx(_hDC, m_Info.X - 20, m_Info.Y - 10, NULL);
	LineTo(_hDC, m_Info.X - 15, m_Info.Y + 5);
	MoveToEx(_hDC, m_Info.X +10, m_Info.Y - 10, NULL);
	LineTo(_hDC, m_Info.X +15, m_Info.Y + 5);
	MoveToEx(_hDC, m_Info.X + 15, m_Info.Y - 10, NULL);
	LineTo(_hDC, m_Info.X + 20, m_Info.Y + 5);
	MoveToEx(_hDC, m_Info.X - 35, m_Info.Y +5, NULL);
	LineTo(_hDC, m_Info.X -90, m_Info.Y +12);
	LineTo(_hDC, m_Info.X - 33, m_Info.Y+12);
	MoveToEx(_hDC, m_Info.X + 35, m_Info.Y + 5, NULL);
	LineTo(_hDC, m_Info.X + 90, m_Info.Y + 12);
	LineTo(_hDC, m_Info.X + 33, m_Info.Y + 12);
}

void CBossMonster::Release(void)
{
}
