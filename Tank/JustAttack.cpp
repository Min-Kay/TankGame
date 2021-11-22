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

	if (!m_Target)
	{
		m_Target = _objlist[OBJID::PLAYER].front();
	}
}

void CJustAttack::Render(HDC _hDC)
{
	Rectangle(_hDC,m_Body.left,m_Body.top,m_Body.right,m_Body.bottom);
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
		m_BarrelPos.x = m_Info.X;
		m_BarrelPos.y = m_Info.Y;
		m_BulletList->push_back(CAbstractFactory<CBullet>::Create(m_BarrelPos, -(m_Angle * PI / 180.f), m_Type));
		m_Cooltime = GetTickCount();
	}
}

void CJustAttack::MoveFoward()
{
	if (m_Target)
	{
		POINT target_Point = { long(m_Target->Get_Info().X), long(m_Target->Get_Info().Y) };
		POINT info_Point = { long(m_Info.X), long(m_Info.Y) };
		Set_Angle_To_Target(target_Point, info_Point);

		m_Info.X += m_Speed * cos(m_Angle * PI / 180.f);
		m_Info.Y -= m_Speed * sin(m_Angle * PI / 180.f);
	}
	else
	{
		m_Info.X += m_Speed * cos(m_Angle * PI / 180.f);
		m_Info.Y -= m_Speed * sin(m_Angle * PI / 180.f);
	}
}

float CJustAttack::Calc_Distance(POINT dest, POINT src)
{
	float	fX = dest.x - src.x;
	float	fY = dest.y - src.y;

	return sqrtf(fX * fX + fY * fY);
}

void CJustAttack::Set_Angle_To_Target(POINT dest, POINT src)
{
	float	fRadian = acosf((dest.x - src.x) / Calc_Distance(dest, src));

	m_Angle = fRadian * 180.f / PI;

	if (dest.y > src.y)
		m_Angle *= -1.f;
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
