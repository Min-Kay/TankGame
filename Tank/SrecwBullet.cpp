#include "stdafx.h"
#include "SrecwBullet.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Obj.h"


CSrecwBullet::CSrecwBullet()
	: m_CenterSpeed(0.f), m_RevolutionAngle(0.f), m_Start(true)
{
	ZeroMemory(&m_CenterPos, sizeof(m_CenterPos));
}

CSrecwBullet::~CSrecwBullet()
{
}

void CSrecwBullet::Initialize(void)
{
	m_Info.Width = BULLET_WIDTH+20;
	m_Info.Height = BULLET_HEIGHT+20;
	m_Speed = BULLET_SPEED+5.f;
	m_Type = OBJID::PLAYER;

	m_CenterSpeed = 5.f;
	m_Distance = 0.f;
	m_RevolutionAngle = m_Radian;
	Update_Rect();
}

int CSrecwBullet::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;

	Update_Locate(m_Speed);


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

	Update_Rect();

	return OBJ_NOEVENT;
}

void CSrecwBullet::Late_Update(OBJLIST * _objlist)
{
	if (Screen_Body_Check())
		Set_Dead(true);

	if (!m_Taget)
	{
		Set_Taget(_objlist[OBJID::PLAYER].front());

		Update_Rect();
	}
	if (!m_Taget) {
		Copy_Data(_objlist[OBJID::PLAYER].front());
		Update_Rect();
	}

	if (0 >= m_Body.left ||
		WINCX <= m_Body.right ||
		0 >= m_Body.top ||
		WINCY <= m_Body.bottom)
	{
		m_Dead = true;
	}
}

void CSrecwBullet::Render(HDC hDC)
{
	

	Ellipse(hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
	Ellipse(hDC, m_Body.left + 10, m_Body.top + 10, m_Body.right -10 , m_Body.bottom  -10);
	Ellipse(hDC, m_Body.left +10 , m_Body.top +10, m_Body.right - 20, m_Body.bottom - 20);
	Ellipse(hDC, m_Body.left +10, m_Body.top +20, m_Body.right - 20, m_Body.bottom - 10);
	Ellipse(hDC, m_Body.left + 20, m_Body.top + 10, m_Body.right - 10, m_Body.bottom -20);
	Ellipse(hDC, m_Body.left +20, m_Body.top + 20, m_Body.right - 10, m_Body.bottom - 10);


	


}

void CSrecwBullet::Release(void)
{
}

void CSrecwBullet::Update_Locate(int _speed)
{
	m_Info.X += _speed*cosf(m_Radian);
	m_Info.Y += _speed*sinf(m_Radian);
}


