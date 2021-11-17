#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_Vaild = true;
	m_Info.Width = BULLET_WIDTH;
	m_Info.Height = BULLET_HEIGHT;
	m_Speed = BULLET_SPEED;
	m_Type = OBJECT::OBJECT_TYPE_BULLET;
	Update_Rect();
}

int CBullet::Update(void)
{
	Update_Locate(m_Speed);
	Update_Rect();
	return 0;
}

void CBullet::Late_Update(void)
{
	if (Screen_Body_Check())
		Set_Dead(true);
}

void CBullet::Render(HDC _hDC)
{
	Ellipse(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void CBullet::Release(void)
{
}

void CBullet::Update_Locate(int _speed)
{
	m_Info.X += _speed*cos(m_Radian);
	m_Info.Y += _speed*sin(m_Radian);
}