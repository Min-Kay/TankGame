#include "stdafx.h"
#include "GuideBullet.h"
#include "AbstractFactory.h"
#include "Bullet.h"
CGuideBullet::CGuideBullet()
{
}


CGuideBullet::~CGuideBullet()
{
	Release();
}

void CGuideBullet::Initialize(void)
{
	m_Info.X = 200.f;
	m_Info.Y = 100.f;
	m_Type = OBJID::PLAYER;
	m_Info.Width = 20.f;
	m_Info.Height = 20.f;
	m_Distance = 200.f;
	m_Speed = 3.f;
	Update_Radian(m_Point[OBJECT::POINT_TYPE_TARGET]);
	m_Cooltime = GetTickCount();
}

int CGuideBullet::Update(void)
{
	if (true == m_Dead)
		return OBJ_DEAD;
	


	Rotation_Radian(m_Speed);

	return OBJ_NOEVENT;
}

void CGuideBullet::Late_Update(OBJLIST* _objlist)
{
	float m_Angle1 = 300;
	float m_Angle2 = 450;
	float m_Angle3 = 150;


	if (!m_Taget) {
		Set_Taget(_objlist[OBJID::PLAYER].front());
	
	}
	Set_Ownner(_objlist[OBJID::PLAYER].front());
	POINT temp{ m_Info.X, m_Info.Y };
	
	if (m_Cooltime + 1000 < GetTickCount())
	{

	_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp, m_Angle1, m_Type));
	_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp, m_Angle2, m_Type));
	_objlist[OBJID::MISSILE].push_back(CAbstractFactory<CBullet>::Create(temp, m_Angle3, m_Type));
	
	m_Cooltime = GetTickCount();
}

 Rotation_Radian(m_Speed);
 
	if (nullptr != m_Taget)
	{
		float	fX = m_Taget->Get_Info().X - m_Info.X;
		float	fY = m_Taget->Get_Info().Y - m_Info.Y;

		float	fDistance = sqrtf(fX * fX + fY * fY);

		float	fRadian = acosf(fX / fDistance);

		m_Radian = fRadian * 180.f / PI;

		if (m_Taget->Get_Info().Y > m_Info.Y)
			m_Radian *= -1.f;
	}

	m_Info.X += cosf(m_Radian * 180.f/PI);
	m_Info.Y -= sinf(m_Radian * 180.f / PI);
	//(m_Speed * cosf(m_Radian * PI / 180.f));
	//(m_Speed * sinf(m_Radian * PI / 180.f));
	Update_Rect();
}

void CGuideBullet::Render(HDC hDC)
{
	Rectangle(hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void CGuideBullet::Release(void)
{
}

void CGuideBullet::Set_Ownner(CObj * _ownner)
{
	m_Ownner = _ownner;
}

