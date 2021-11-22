#include "stdafx.h"
#include "St3_FireBullet.h"
#include "Def_St3.h"

St3_FireBullet::St3_FireBullet()
	: m_MaxCize(0)
	, m_Max(false)
	, m_RangeTime(0)
	, m_RadianCircle(0)
{

}

St3_FireBullet::~St3_FireBullet()
{
	Release();
}

void St3_FireBullet::Initialize(void)
{
	m_Info.Width = 1;
	m_Info.Height = 1;
	m_Speed = BULLET_SPEED;
	m_Type = OBJID::MISSILE;

	m_MaxCize = 0;
	m_RangeTime= 20;
	m_Max = false;
	Update_Rect();
	m_MaxtimeMAX = m_RangeTime;
}

int St3_FireBullet::Update(void)
{
	--m_RangeTime;
	m_MaxCize+=5;

	if(m_Once)
		Once();

	if (m_RangeTime <= 0)
	{
		m_Info.Width = 0;
		m_Dead = true;
		return 0;
	}

	if (m_MaxCize < St3_FIRE_MAXCIZE)
	{
		m_Info.Width = m_MaxCize;
		m_Info.Height = m_MaxCize;
	}

	m_Speed += 0.5f;

	Update_Locate(m_Speed);

	Update_Rect();
	return 0;
}

void St3_FireBullet::Late_Update(OBJLIST* _objlist)
{
	Check_Out();
}

void St3_FireBullet::Render(HDC hDC)
{
	Render_Body(hDC);

	HBRUSH oBrush;

	HBRUSH Brush1;

	m_Temp = (float)m_RangeTime / m_MaxtimeMAX * 100;
	
	if (m_Temp > 80)
	{
		Brush1 = CreateSolidBrush(RGB(255, 255, 1));
		oBrush = (HBRUSH)SelectObject(hDC, Brush1);
		Ellipse(hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
		SelectObject(hDC, oBrush);
		DeleteObject(Brush1);
	}
	else if (m_Temp > 60)
	{
		Brush1 = CreateSolidBrush(RGB(255, 128, 1));
		oBrush = (HBRUSH)SelectObject(hDC, Brush1);
		Ellipse(hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
		SelectObject(hDC, oBrush);
		DeleteObject(Brush1);
	}
	else
	{
		Brush1 = CreateSolidBrush(RGB(255, 0, 0));
		oBrush = (HBRUSH)SelectObject(hDC, Brush1);
		Ellipse(hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
		SelectObject(hDC, oBrush);
		DeleteObject(Brush1);
	}

}

void St3_FireBullet::Release(void)
{
}

void St3_FireBullet::Set_RangeTime(int _range)
{
	m_RangeTime = _range;
}

void St3_FireBullet::Once()
{
	m_Once = false;
	m_Radian += (rand() % 45) * PI / 180 - PI/8;
	m_MaxtimeMAX = m_RangeTime;
	return;
}

void St3_FireBullet::Render_Body(HDC _hdc)
{
}

void St3_FireBullet::Check_Out()
{
	if (0 >= m_Body.top - m_Speed || //啊厘磊府 面倒贸府
		0 >= m_Body.left - m_Speed ||
		600 <= m_Body.bottom + m_Speed ||
		800 <= m_Body.right + m_Speed
		)
	{
		m_Dead = true;
	}
}