#include "stdafx.h"
#include "JustAttack.h"
#include "AbstractFactory.h"
#include "Bullet.h"

CJustAttack::CJustAttack()
{
}


CJustAttack::~CJustAttack()
{
}

void CJustAttack::Initialize(void)
{
	Set_Type(OBJID::MONSTER);
	Set_Speed(1.0f);
	m_Cooltime = GetTickCount();
}

int CJustAttack::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;

	MoveFoward();

	Update_Rect();

	Shoot();

	return OBJ_NOEVENT;
}

void CJustAttack::Late_Update(OBJLIST * _objlist)
{
	NeedToCheckScreen();

	if (!m_BulletList)
	{
		m_BulletList = &_objlist[OBJID::MISSILE];
		Update_Rect();
	}
}

void CJustAttack::Render(HDC _hDC)
{
	MoveToEx(_hDC,(m_Info.X - m_Info.Width / 2) + cosf(m_Radian) , (m_Info.Y - m_Info.Height / 2) - sinf(m_Radian),nullptr);
	LineTo(_hDC, (m_Info.X + m_Info.Width / 2 ) + cosf(m_Radian), ( m_Info.Y - m_Info.Height / 2) - sinf(m_Radian));
	LineTo(_hDC, (m_Info.X) + cosf(m_Radian),( m_Info.Y + m_Info.Height / 2 ) - sinf(m_Radian));
	LineTo(_hDC, (m_Info.X - m_Info.Width / 2) + cosf(m_Radian), (m_Info.Y - m_Info.Height / 2) - sinf(m_Radian));
}

void CJustAttack::Release(void)
{
	m_BulletList = nullptr; 
}

void CJustAttack::Copy_Data(CObj * _target)
{
	Move_Pos(_target->Get_Info().X, _target->Get_Info().Y);
	Set_Size(_target->Get_Info().Width, _target->Get_Info().Height);
	Set_Radian(_target->Get_Radian());
	isNeed = static_cast<CJustAttack*>(_target)->Get_isNeed();
}

void CJustAttack::Shoot()
{
	if (m_Cooltime + 500 < GetTickCount())
	{
		m_BarrelPos.x = (m_Info.X) + cosf(m_Radian);
		m_BarrelPos.y = (m_Info.Y + m_Info.Height / 2) + sinf(m_Radian);
		m_BulletList->push_back(CAbstractFactory<CBullet>::Create(m_BarrelPos, -m_Radian, m_Type));
		m_Cooltime = GetTickCount();
	}
}

void CJustAttack::MoveFoward()
{
	m_Info.X += m_Speed * cos(m_Radian);
	m_Info.Y -= m_Speed * sin(m_Radian);
}

void CJustAttack::NeedToCheckScreen()
{
	if (!isNeed)
		return; 

	Set_Dead(Screen_Body_Check());
}

void CJustAttack::Set_ScreenCheck(bool _bool)
{
	isNeed = _bool;
}
