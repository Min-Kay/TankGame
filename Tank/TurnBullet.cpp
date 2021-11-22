#include "stdafx.h"
#include "TurnBullet.h"


CTurnBullet::CTurnBullet()
{
}


CTurnBullet::~CTurnBullet()
{
}
void CTurnBullet::Initialize(void)
{
	m_Info.Width = BULLET_WIDTH;
	m_Info.Height = BULLET_HEIGHT ;

	m_Speed = 50;
	m_CenterSpeed = 5.f;
	m_Distance = 10;
	m_RevolutionAngle = 10.f;
	m_Type = OBJID::MISSILE;

}

int CTurnBullet::Update(void)
{
	if (true == m_Dead)
		return OBJ_DEAD;

	if (m_Start)
	{
		m_CenterPos.x = m_Info.X;
		m_CenterPos.y = m_Info.Y;
		m_RevolutionAngle = m_Radian;
		m_Start = false;
	}


	m_CenterPos.x += m_CenterSpeed * cosf(m_RevolutionAngle * PI / 180.f);
	m_CenterPos.y -= m_CenterSpeed * sinf(m_RevolutionAngle * PI / 180.f);

	m_Info.X = m_CenterPos.x + (m_Distance * cosf(m_Radian * PI / 180.f));
	m_Info.Y = m_CenterPos.y - (m_Distance * sinf(m_Radian * PI / 180.f));

	m_Radian += m_Speed;
	Update_Locate(m_Speed);
	Update_Rect();

	return OBJ_NOEVENT;
}

void CTurnBullet::Late_Update(OBJLIST* _objlist)
{
	/*if (100 >= m_tRect.left ||
	WINCX - 100 <= m_tRect.right ||
	100 >= m_tRect.top ||
	WINCY - 100 <= m_tRect.bottom)
	{
	m_bDead = true;
	}*/
	if (Screen_Body_Check())
		Set_Dead(true);
}

void CTurnBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void CTurnBullet::Release(void)
{

}


void CTurnBullet::Update_Locate(int _speed)
{
	m_Info.X += _speed*cosf(m_Radian);
	m_Info.Y += _speed*sinf(m_Radian);
}