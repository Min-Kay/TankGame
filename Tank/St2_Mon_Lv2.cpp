#include "stdafx.h"
#include "St2_Mon_Lv2.h"


#include "AbstractFactory.h"
#include "Bullet.h"

St2_Mon_Lv2::St2_Mon_Lv2()
{
}


St2_Mon_Lv2::~St2_Mon_Lv2()
{
}

void St2_Mon_Lv2::Initialize(void)
{
	Set_Type(OBJID::MONSTER);
	Set_Speed(2.0f);
	m_Cooltime = GetTickCount();
}

int St2_Mon_Lv2::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;

	MoveFoward();

	Update_Rect();

	Shoot();

	return OBJ_NOEVENT;
}

void St2_Mon_Lv2::Late_Update(OBJLIST * _objlist)
{
	NeedToCheckScreen();

	if (!m_BulletList)
	{
		m_BulletList = &_objlist[OBJID::MISSILE];
		Update_Rect();
	}
}

void St2_Mon_Lv2::Render(HDC _hDC)
{
	Rectangle(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void St2_Mon_Lv2::Release(void)
{
	m_BulletList = nullptr;
}

void St2_Mon_Lv2::Copy_Data(CObj * _target)
{
	Move_Pos(_target->Get_Info().X, _target->Get_Info().Y);
	Set_Size(_target->Get_Info().Width, _target->Get_Info().Height);
	Set_Radian(_target->Get_Radian());
	isNeed = static_cast<St2_Mon_Lv2*>(_target)->Get_isNeed();
}

void St2_Mon_Lv2::Shoot()
{
	if (m_Cooltime + 500 < GetTickCount())
	{
		m_BarrelPos.x = (m_Info.X - m_Info.Width / 2) + cosf(m_Radian);
		m_BarrelPos.y = (m_Info.Y - m_Info.Width / 2) + sinf(m_Radian);
		m_BulletList->push_back(CAbstractFactory<CBullet>::Create(m_BarrelPos, -m_Radian, m_Type));
		m_Cooltime = GetTickCount();
	}
}

void St2_Mon_Lv2::MoveFoward()
{
	m_Info.X += m_Speed * cos(m_Radian);
	m_Info.Y -= m_Speed * sin(m_Radian);
}

void St2_Mon_Lv2::NeedToCheckScreen()
{
	if (!isNeed)
		return;

	Set_Dead(Screen_Body_Check());
}

void St2_Mon_Lv2::Set_ScreenCheck(bool _bool)
{
	isNeed = _bool;
}

