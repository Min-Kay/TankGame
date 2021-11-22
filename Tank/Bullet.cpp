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
	m_Info.Width = BULLET_WIDTH;
	m_Info.Height = BULLET_HEIGHT;
	m_Speed = BULLET_SPEED;
	Update_Rect();
}

int CBullet::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD; 

	Update_Locate(m_Speed);
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBullet::Late_Update(OBJLIST* _objlist)
{
	if (Screen_Body_Check())
		Set_Dead(true);
}

void CBullet::Render(HDC _hDC)
{
	Render_Bullet(_hDC);
	/*Ellipse(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);*/
}

void CBullet::Release(void)
{
}

void CBullet::Render_Bullet(HDC _hdc)
{
	HPEN hpen=NULL; 
	HPEN hpenOld= NULL;

	switch (m_Type)
	{
	case OBJID::PLAYER:
		hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		hpenOld = (HPEN)::SelectObject(_hdc, (HGDIOBJ)hpen);
		break;
	case OBJID::MONSTER:
		hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hpenOld = (HPEN)::SelectObject(_hdc, (HGDIOBJ)hpen);
		m_Info.Width = 7;
		m_Info.Height = 7;
		break;
	case OBJID::MISSILE:

		break;
	case OBJID::SATELLITE:
		break;
	case OBJID::OBSTACLE:
		break;
	case OBJID::END:
		hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hpenOld = (HPEN)::SelectObject(_hdc, (HGDIOBJ)hpen);
		break;
		break;
	default:
		break;
	}





	POINTFLOAT temp1 = { 0.f,0.f };
	POINTFLOAT temp2 = { 0.f,0.f };
	int len = m_Info.Width;
	float tempR = 0;
	temp1.x = m_Info.X;
	temp1.y = m_Info.Y;

	MoveToEx(_hdc, m_Info.X, m_Info.Y, NULL);

	//1
	tempR = m_Radian - PI * 3 / 4;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len *cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	// 중간선1
	temp2 = temp1;
	tempR = m_Radian + PI / 2;
	len = m_Info.Width / 2;
	temp2.x = temp2.x + len * cosf(tempR);
	temp2.y = temp2.y + len * sinf(tempR);
	LineTo(_hdc, temp2.x, temp2.y);
	MoveToEx(_hdc, temp1.x, temp1.y, NULL);

	//2
	tempR = m_Radian - PI;
	len = m_Info.Width;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	//3
	tempR = m_Radian - PI * 3 / 4;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	//4
	tempR = m_Radian - PI;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);



	//5
	tempR = m_Radian - PI * 3 / 4 + PI;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);


	//중간선2
	temp2 = temp1;
	tempR = m_Radian;
	len = m_Info.Width / 2;
	temp2.x = temp2.x + len * cosf(tempR);
	temp2.y = temp2.y + len * sinf(tempR);
	LineTo(_hdc, temp2.x, temp2.y);
	MoveToEx(_hdc, temp1.x, temp1.y, NULL);


	//6
	tempR = m_Radian + PI / 2;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	//----------------------------------------우------------------------------

	MoveToEx(_hdc, m_Info.X, m_Info.Y, NULL);
	temp1.x = m_Info.X;
	temp1.y = m_Info.Y;

	//1
	tempR = m_Radian + PI * 3 / 4;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	// 중간선1
	temp2 = temp1;
	tempR = m_Radian - PI / 2;
	len = m_Info.Width / 2;
	temp2.x = temp2.x + len * cosf(tempR);
	temp2.y = temp2.y + len * sinf(tempR);
	LineTo(_hdc, temp2.x, temp2.y);
	MoveToEx(_hdc, temp1.x, temp1.y, NULL);

	//2
	tempR = m_Radian + PI;
	len = m_Info.Width;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	//3
	tempR = m_Radian + PI * 3 / 4;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	//4
	tempR = m_Radian + PI;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);



	//5
	tempR = m_Radian + PI * 3 / 4 + PI;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);


	//중간선2
	temp2 = temp1;
	tempR = m_Radian;
	len = m_Info.Width / 2;
	temp2.x = temp2.x + len * cosf(tempR);
	temp2.y = temp2.y + len * sinf(tempR);
	LineTo(_hdc, temp2.x, temp2.y);
	MoveToEx(_hdc, temp1.x, temp1.y, NULL);


	//6
	tempR = m_Radian - PI / 2;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	hpen = (HPEN)::SelectObject(_hdc, hpenOld);
	DeleteObject(hpen);	// 생성한 펜 삭제
}

void CBullet::Update_Locate(int _speed)
{
	m_Info.X += _speed*cosf(m_Radian);
	m_Info.Y += _speed*sinf(m_Radian);
}