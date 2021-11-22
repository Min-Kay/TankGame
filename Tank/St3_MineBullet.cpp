#include "stdafx.h"
#include "St3_MineBullet.h"

St3_MineBullet::St3_MineBullet()
	:m_Rect1({})
{
}

St3_MineBullet ::~St3_MineBullet()
{
}

int St3_MineBullet::Update(void)
{
	Update_Rect();
	
	if (m_Once)
	{
		m_Rect1 = m_Body;
		m_Once = false;
	}
	POINT temp = { m_Info.X,m_Info.Y };

	if (m_Bomb)
	{
		m_Info.Width = m_BombTime * 10;
		m_Info.Height = m_BombTime * 10;
		--m_BombTime;
		if (m_BombTime <= 0)
			m_Dead = true;

		return 0;
	}

	if (m_DelayTime <= 0)
		m_Bomb = true;

	m_Info.Width = m_Info.Width*m_DelayTime/150;
	m_Info.Height = m_Info.Height * m_DelayTime / 150;

	--m_DelayTime;
	return 0;
}

void St3_MineBullet::Initialize(void)
{
	m_Info.Width = 100;
	m_Info.Height = 100;
	m_Type = OBJID::MISSILE;
	m_DelayTime = 150;
	m_BombTime = 20;
	Update_Rect();
	m_Maxtime = m_BombTime;
}

void St3_MineBullet::Render(HDC hDC)
{
	//Ellipse(hDC, m_Rect1.left, m_Rect1.top, m_Rect1.right, m_Rect1.bottom);
	//Ellipse(hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);

	for (int i = 0; i < 8; ++i)
	{
		POINT temp;
		temp.x = m_Info.X + m_Info.Width / 2 * m_DelayTime / 45 * cosf(m_Radian + (PI / 4 * i));
		temp.y = m_Info.Y + m_Info.Width / 2 * m_DelayTime / 45 * sinf(m_Radian + (PI / 4 * i));

		MoveToEx(hDC, temp.x, temp.y, NULL);

		temp.x = m_Info.X + m_Info.Width / 3 * m_DelayTime / 45 * cosf(m_Radian + (PI / 4 * i));
		temp.y = m_Info.Y + m_Info.Width / 3 * m_DelayTime / 45 * sinf(m_Radian + (PI / 4 * i));

		LineTo(hDC, temp.x, temp.y);
		/*  LineTo(_hDC, temp.x + m_Size * m_FPS / 90, temp.y + m_Size * m_FPS / 90);*/
	}

	HBRUSH Brush1;

	if (m_Bomb)
	{
		HBRUSH oBrush;

		int m_Temp = (float)m_BombTime / m_Maxtime * 100;

	
		Brush1 = CreateSolidBrush(RGB(255, 100, 0));
		oBrush = (HBRUSH)SelectObject(hDC, Brush1);
		Ellipse(hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
		SelectObject(hDC, oBrush);
		DeleteObject(Brush1);
	
		Brush1 = CreateSolidBrush(RGB(255, 153, 50));
		oBrush = (HBRUSH)SelectObject(hDC, Brush1);
		Ellipse(hDC, m_Body.left + m_Info.Width * 33 / 100, m_Body.top + m_Info.Width * 33 / 100, m_Body.right - m_Info.Width * 33 / 100, m_Body.bottom - m_Info.Width * 33 / 100);
		SelectObject(hDC, oBrush);
		DeleteObject(Brush1);

		Brush1 = CreateSolidBrush(RGB(255, 255, 0));
		oBrush = (HBRUSH)SelectObject(hDC, Brush1);
		Ellipse(hDC, m_Body.left + m_Info.Width * 75 / 100, m_Body.top + m_Info.Width * 75 / 100, m_Body.right -m_Info.Width * 75 / 100, m_Body.bottom - m_Info.Width * 75 / 100);
		SelectObject(hDC, oBrush);
		DeleteObject(Brush1);
	
	
	


		//HBRUSH Brush1 = CreateSolidBrush(RGB(255, 255, 81));
		//oBrush = (HBRUSH)SelectObject(hDC, Brush1);
		//Ellipse(hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
		//SelectObject(hDC, oBrush);
		//DeleteObject(Brush1);

		//HBRUSH Brush1 = CreateSolidBrush(RGB(255, 255, 81));
		//oBrush = (HBRUSH)SelectObject(hDC, Brush1);
		//Ellipse(hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
		//SelectObject(hDC, oBrush);
		//DeleteObject(Brush1);

		//for (int i = 0; i < 8; ++i)  ÅÍÁú‹š ¼±
		//{
		//	POINT temp;
		//	temp.x = m_Info.X + m_Info.Width / 2 * m_BombTime / 45 * cosf(m_Radian + (PI / 4 * i));
		//	temp.y = m_Info.Y + m_Info.Width / 2 * m_BombTime / 45 * sinf(m_Radian + (PI / 4 * i));

		//	MoveToEx(hDC, temp.x, temp.y, NULL);

		//	temp.x = m_Info.X + m_Info.Width / 3 * m_BombTime / 45 * cosf(m_Radian + (PI / 4 * i));
		//	temp.y = m_Info.Y + m_Info.Width / 3 * m_BombTime / 45 * sinf(m_Radian + (PI / 4 * i));

		//	LineTo(hDC, temp.x, temp.y);
		//	/*  LineTo(_hDC, temp.x + m_Size * m_FPS / 90, temp.y + m_Size * m_FPS / 90);*/
		//}

	}

		
}

void St3_MineBullet::Late_Update(OBJLIST* _objlist)
{
}

void St3_MineBullet::Release(void)
{
}

bool St3_MineBullet::Delay()
{
	return false;
}

void St3_MineBullet::Render_Body(HDC _hdc)
{
}
