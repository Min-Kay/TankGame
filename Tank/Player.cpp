#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
	:	m_Bullet(nullptr)
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(void)
{
	m_Info.X= RESPONE_X;
	m_Info.Y = RESPONE_Y;
	m_Info.Width = PLAYER_WIDTH;
	m_Info.Height = PLAYER_HEIGHT;
	m_Info.Hp = PLAYER_HP;
	m_Info.Att = PLAYER_ATTACK;

	m_Type = OBJECT::OBJECT_TYPE_PLAYER;
	m_Point[OBJECT::POINT_TYPE_MOUSE] = { long(RESPONE_X),long(RESPONE_Y) };
	m_Point[OBJECT::POINT_TYPE_TARGET] = { long(RESPONE_X),long(RESPONE_Y) };
	m_Dir = OBJECT::DIRECTION_TOP;
	m_Speed = PLAYER_SPEED;
	m_Vaild = true;

	Update_Rect();
	Update_Radian();
	Update_Aim();
}

int CPlayer::Update(void)
{
	GetCursorPos(&m_Point[OBJECT::POINT_TYPE_MOUSE]);
	ScreenToClient(HWND(), &m_Point[OBJECT::POINT_TYPE_MOUSE]);
	ShowCursor(false);

	return 0;
}

void CPlayer::Late_Update(void)
{

}

void CPlayer::Render(HDC _hDC)
{
	Ellipse(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
	MoveToEx(_hDC, (int)m_Info.X, (int)m_Info.Y, NULL);
	LineTo(_hDC, m_Point[OBJECT::POINT_TYPE_MOUSE].x, m_Point[OBJECT::POINT_TYPE_MOUSE].y);
}

void CPlayer::Release(void)
{
}

void CPlayer::Update_Radian()
{
	m_Radian = atan2(m_Point[OBJECT::POINT_TYPE_MOUSE].y-m_Info.Y, m_Point[OBJECT::POINT_TYPE_MOUSE].x - m_Info.X);
}

void CPlayer::Update_Aim(void)
{
	m_Point[OBJECT::POINT_TYPE_AIM].x = m_Info.X + cos(m_Radian);
	m_Point[OBJECT::POINT_TYPE_AIM].y = m_Info.Y + sin(m_Radian);
}

//void CPlayer::Key_Input(void)
//{
//	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
//	{
//		m_Bullet->push_back(Create_Bullet());
//	}
//
//	if (GetAsyncKeyState(VK_A) & 0x8000)
//	{
//		if (INGAME_LEFT < m_Info.X)
//			m_Info.X -= m_Speed;
//	}
//
//	if (GetAsyncKeyState(VK_D) & 0x8000)
//	{
//		if (INGAME_RIGHT > m_Info.X)
//			m_Info.X += m_Speed;
//	}
//
//	if (GetAsyncKeyState(VK_W) & 0x8000)
//	{
//		if (INGAME_TOP < m_Info.Y)
//			m_Info.Y -= m_Speed;
//	}
//
//	if (GetAsyncKeyState(VK_S) & 0x8000)
//	{
//		if (INGAME_BOTTOM > m_Info.Y)
//			m_Info.Y += m_Speed;
//	}
//
//	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
//	{
//		m_Direction = DIRECTION::LEFT;
//	}
//	if (GetAsyncKeyState(VK_UP) & 0x8000)
//	{
//		m_Direction = DIRECTION::TOP;
//	}
//
//	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
//	{
//		m_Direction = DIRECTION::RIGHT;
//	}
//
//	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
//	{
//		m_Direction = DIRECTION::BOTTOM;
//	}
//}

CObj * CPlayer::Create_Bullet(void)
{
	if (m_Bullet)
	{
		//총알 생성 필요
		return nullptr;
	}
	return nullptr;
}

const POINT CPlayer::Get_Focus()
{
	return POINT();
}

void CPlayer::Set_Bullet(list<CObj*>* _pBullet)
{
	m_Bullet = _pBullet;
}
