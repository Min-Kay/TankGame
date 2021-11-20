#include "stdafx.h"
#include "Ball.h"

void CBall::Initialize(void)
{
	Set_Angle(); 
	m_Speed = 5.f;
	m_Type = OBJID::MONSTER;
}

int CBall::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;

	m_Info.X += m_Speed * cosf(m_Radian);
	m_Info.Y -= m_Speed * sinf(m_Radian);

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBall::Late_Update(OBJLIST* _objlist)
{
	if (Screen_Body_Check())
		Set_Dead(true);
}

void CBall::Render(HDC hDC)
{
	Ellipse(hDC,m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void CBall::Release(void)
{
}

void CBall::Set_Angle()
{
	m_Angle = m_Radian * 180.f / PI;
}