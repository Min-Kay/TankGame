#include "stdafx.h"
#include "SunBullet.h"


CSunBullet::CSunBullet()
{
}


CSunBullet::~CSunBullet()
{
}

void CSunBullet::Initialize(void)
{
	m_Info.Height = 20;
	m_Info.Width = 20;
	m_Info.X = m_parent->Get_Info().X;
	m_Info.Y = m_parent->Get_Info().Y;
	m_Speed = 10.f;

	isInit = false;
	isTurn = false;
	isAttack = false; 

	Set_Angle(m_Radian);
	Update_Rect();
}

int CSunBullet::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;

	if (m_parent)
	{
		MoveToInitPos();
		Spin();
		if (m_target)
			Attack(); 
	}
	else
	{
		m_Info.X += cosf(m_Angle * PI / 180.f) * m_Speed;
		m_Info.Y -= sinf(m_Angle * PI / 180.f) * m_Speed;
	}

	Update_Rect(); 

	return OBJ_NOEVENT;
}

void CSunBullet::Late_Update(OBJLIST * _objlist)
{
	if (!m_target)
	{
		Set_target(_objlist[OBJID::PLAYER].front());
		Update_Rect(); 
	}

	if (Screen_Body_Check())
		Set_Dead(true);
}

void CSunBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_Body.left,m_Body.top,m_Body.right,m_Body.bottom);
}

void CSunBullet::Release(void)
{
}

void CSunBullet::MoveToInitPos()
{
	if (isInit)
		return;

	m_Info.X += cosf(270 * PI / 180.f) * m_Speed;
	m_Info.Y -= sinf(270 * PI / 180.f) * m_Speed;

	if (Calc_CurrDistance())
	{
		isInit = true;
		isTurn = true; 	
		m_Angle = 90.f;
	}
		
}

void CSunBullet::Spin()
{
	if (!isTurn)
		return; 


	m_Info.X = m_parent->Get_Info().X + cosf(m_Angle * PI / 180.f) * m_distance;
	m_Info.Y = m_parent->Get_Info().Y + sinf(m_Angle * PI / 180.f) * m_distance;

	m_Angle += 5.f;

	if (360.f * m_spinCount <= m_Angle)
	{
		isTurn = false; 
		isAttack = true;
		m_targetPoint = { long(m_target->Get_Info().X),long(m_target->Get_Info().Y) };
	
		float	fX = m_targetPoint.x - m_Info.X;
		float	fY = m_targetPoint.y - m_Info.Y;

		float	fDistance = sqrtf(fX * fX + fY * fY);

		float	fRadian = acosf(fX / fDistance);

		m_Angle = fRadian * 180.f / PI;

		if (m_targetPoint.y  > m_Info.Y)
			m_Angle *= -1.f;
	}
}

void CSunBullet::Attack()
{
	if (!isAttack)
		return; 

	m_Info.X += cosf(m_Angle * PI / 180.f) * m_Speed * 2.f;
	m_Info.Y -= sinf(m_Angle * PI / 180.f) * m_Speed * 2.f;
}

void CSunBullet::Set_Angle(float _radian)
{
	m_Angle = _radian * 180.f / PI; 
}

bool CSunBullet::Calc_CurrDistance()
{
	float fx = abs(m_Info.X - m_parent->Get_Info().X);
	float fy = abs(m_Info.Y - m_parent->Get_Info().Y);

	float result = sqrtf(fx * fx + fy * fy);
	
	if (m_distance * 2 <= result)
	{
		m_distance = result; 
		return true;
	}
	return false;
}
