#include "stdafx.h"
#include "Wall.h"

void CWall::Initialize(void)
{
	brush = CreateSolidBrush(RGB(0, 0, 100));
	Set_Angle();
	
	m_Type = OBJID::OBSTACLE;
	m_Speed = 10.f;
	m_LifeTime = 20000;
	m_Tick = GetTickCount();
}

int CWall::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;

	MoveDistance();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CWall::Late_Update(OBJLIST* _objlist)
{
	if (m_Tick + m_LifeTime <= GetTickCount())
		Set_Dead(true);
}

void CWall::Render(HDC _hDC)
{
	Rectangle(_hDC,m_Body.left,m_Body.top,m_Body.right,m_Body.bottom);
	FillRect(_hDC,&m_Body, brush);
}

void CWall::Release(void)
{
}

void CWall::MoveDistance()
{
	if (Check_Distance() || Screen_Body_Check())
		return;
			
	m_Info.X += cosf(m_Angle * PI / 180.f) * m_Speed;
	m_Info.Y -= sinf(m_Angle * PI / 180.f) * m_Speed;

}

bool CWall::Check_Distance()
{
	float fx = m_Info.X - m_InitPos.x;
	float fy = m_Info.Y - m_InitPos.y;

	float result = sqrtf(fx * fx + fy * fy);

	return result >= m_Distance ? true : false ;

}

void CWall::Set_Angle()
{
	m_Angle = m_Radian * 180.f / PI;
}

void CWall::Set_Collision()
{

}

void CWall::Set_InitPos()
{
	m_InitPos.x = m_Info.X;
	m_InitPos.y = m_Info.Y;
}
