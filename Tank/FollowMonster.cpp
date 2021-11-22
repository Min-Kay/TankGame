#include "stdafx.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "Obj.h"
#include "FollowMonster.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "SrecwBullet.h"


CFollowMonster::CFollowMonster()
{
}

CFollowMonster::~CFollowMonster()
{
}

void CFollowMonster::Initialize(void)
{

	//m_Info.X = 10.f;
	//m_Info.Y = 10.f;
	//m_Info.Width = 10.f;
	//m_Info.Height = 10.f;
	m_Speed = 2.f;
	m_Type = OBJID::MONSTER;
	m_Cooltime = GetTickCount();
	
}

int CFollowMonster::Update(void)
{

	if (true == m_Dead)
		return OBJ_DEAD;
	if (m_Taget) {

	fllow_Player(m_objlist[OBJID::PLAYER]);
	}


	return OBJ_NOEVENT;

}

void CFollowMonster::Late_Update(OBJLIST* _objlist)
{

		POINT temp{ m_Info.X, m_Info.Y };

	if (m_Cooltime + 2000 < GetTickCount())
	{
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CSrecwBullet>::Create(temp, 900, m_Type));
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CSrecwBullet>::Create(temp, 0, m_Type));
		_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CSrecwBullet>::Create(temp, 270, m_Type));
	_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CSrecwBullet>::Create(temp, 1150, m_Type));
		m_Cooltime = GetTickCount();
	}

	
	Update_Rect();
	//if (!m_Taget) {
	//	Copy_Data(_objlist[OBJID::PLAYER].front());
	//	
	//}
	if (!m_Taget) {
		Set_Taget(_objlist[OBJID::PLAYER].front());
		Update_Rect();
	}


}

void CFollowMonster::Render(HDC _hDC)
{
	Rectangle(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
	//MoveToEx(_hDC, (m_Info.X - m_Info.Width / 2) + cosf(m_Radian), (m_Info.Y - m_Info.Height / 2) - sinf(m_Radian), nullptr);
	//LineTo(_hDC, (m_Info.X + m_Info.Width / 2) + cosf(m_Radian), (m_Info.Y - m_Info.Height / 2) - sinf(m_Radian));
	//LineTo(_hDC, (m_Info.X) + cosf(m_Radian), (m_Info.Y + m_Info.Height / 2) - sinf(m_Radian));
	//LineTo(_hDC, (m_Info.X - m_Info.Width / 2) + cosf(m_Radian), (m_Info.Y - m_Info.Height / 2) - sinf(m_Radian));
}

void CFollowMonster::Release(void)
{

}


void CFollowMonster::fllow_Player(OBJLIST* _objlist)
{
	m_X = m_Taget->Get_Info().X - m_Info.X;
	m_Y = m_Taget->Get_Info().Y - m_Info.Y;

	m_Distance = sqrtf(m_X* m_X + m_Y * m_Y);

	m_Radian = acosf(m_X / m_Distance);

	if (m_Taget->Get_Info().Y > m_Info.Y) 
		m_Radian = 2 * PI - m_Radian;

	m_Info.X += cosf(m_Radian) * m_Speed;
	m_Info.Y -= sinf(m_Radian) * m_Speed;
}

bool CFollowMonster::Confined_Monster()
{

	return (WINCX <= m_Body.right || WINCY <= m_Body.bottom || 0 >= m_Body.top || 0 >= m_Body.left) ? true : false;

}

void CFollowMonster::Copy_Data(CObj * _target)
{
	Move_Pos(_target->Get_Info().X, _target->Get_Info().Y);
	Set_Size(_target->Get_Info().Width, _target->Get_Info().Height);
	Set_Radian(_target->Get_Radian());

	Update_Rect();
}
//void CPlayer::Set_Bullet(OBJLIST* _pBullet)
//{
//	m_Bullet = _pBullet;
//}


