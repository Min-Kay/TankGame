#include "stdafx.h"
#include "Ball.h"

void CBall::Initialize(void)
{ 
	m_Speed = 5.f;
	m_Type = OBJID::MONSTER;
	m_Tick = GetTickCount(); 
	m_LifeTime = 15000;
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
	Set_Window_Bounce();

	if(m_Tick + m_LifeTime < GetTickCount())
		Set_Dead(true);
}

void CBall::Render(HDC hDC)
{
	ori = SelectObject(hDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hDC,RGB(255,0,0));
	Ellipse(hDC,m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
	SelectObject(hDC, ori);
	DeleteObject(ori);
}

void CBall::Release(void)
{
}

void CBall::Set_Window_Bounce()
{
	if (m_Body.right >= WINCX || m_Body.left <= 0)
		m_Radian = PI - m_Radian;

	if(m_Body.bottom >= WINCY || m_Body.top <= 0)
		m_Radian = PI * 2 - m_Radian;
}
