#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "Satellite.h"

CPlayer::CPlayer()
	: m_Bullet(nullptr)
	, m_Satellite(nullptr)
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(void)
{
	m_Info.X = RESPONE_X;
	m_Info.Y = RESPONE_Y;
	m_Info.Width = PLAYER_WIDTH;
	m_Info.Height = PLAYER_HEIGHT;

	m_Type = OBJID::PLAYER;
	m_Point[OBJECT::POINT_TYPE_MOUSE] = { (long)RESPONE_X,(long)RESPONE_Y };
	m_Point[OBJECT::POINT_TYPE_TARGET] = { (long)RESPONE_X,(long)RESPONE_Y };
	m_Dir = OBJECT::DIRECTION_TOP;
	m_Speed = PLAYER_SPEED;

	Update_Rect();
	Update_Radian(m_Point[OBJECT::POINT_TYPE_MOUSE]);
	Update_Aim(PLAYER_CANNON_LEN);
	
	m_CoolTime = GetTickCount();
	m_InitTime = 500;
}

int CPlayer::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;

	GetCursorPos(&m_Point[OBJECT::POINT_TYPE_MOUSE]);
	ScreenToClient(g_hWnd, &m_Point[OBJECT::POINT_TYPE_MOUSE]);
	ShowCursor(false);


	Key_Input();
	Update_Rect();
	Update_Radian(m_Point[OBJECT::POINT_TYPE_MOUSE]);
	Update_Aim(PLAYER_CANNON_LEN);


	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(OBJLIST* _objlist)
{

}

void CPlayer::Render(HDC _hDC)
{
	Rectangle(_hDC, 0, 0, 800, 600);
	Ellipse(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
	MoveToEx(_hDC, (int)m_Info.X, (int)m_Info.Y, NULL);
	LineTo(_hDC, m_Point[OBJECT::POINT_TYPE_AIM].x, m_Point[OBJECT::POINT_TYPE_AIM].y);
}

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{
	if ((GetAsyncKeyState(KEY_ATTACK) & 0x8000) && (m_CoolTime + m_InitTime < GetTickCount()))
	{
		Create_Bullet();
		m_CoolTime = GetTickCount();
	}

	if (GetAsyncKeyState(KEY_DOWN) & 0x8000)
	{
		if (GetAsyncKeyState(KEY_LEFT) & 0x8000)
		{
			if (WINCY > m_Body.bottom && 0 < m_Body.left)
			{
				m_Info.X -= m_Speed / sqrtf(2);
				m_Info.Y += m_Speed / sqrtf(2);
			}
			else if (WINCY > m_Body.bottom)
			{
				m_Info.Y += m_Speed / sqrtf(2);
			}
			else if (0 < m_Body.left)
			{
				m_Info.X -= m_Speed / sqrtf(2);
			}
		}
		else if (GetAsyncKeyState(KEY_RIGHT) & 0x8000)
		{
			if (WINCY > m_Body.bottom && WINCX > m_Body.right)
			{
				m_Info.X += m_Speed / sqrtf(2);
				m_Info.Y += m_Speed / sqrtf(2);
			}
			else if (WINCY > m_Body.bottom)
			{
				m_Info.Y += m_Speed / sqrtf(2);
			}
			else if (WINCX > m_Body.right)
			{
				m_Info.X += m_Speed / sqrtf(2);
			}
		}
		else
		{
			if (WINCY > m_Body.bottom)
				m_Info.Y += m_Speed;
		}
	}

	if (GetAsyncKeyState(KEY_UP) & 0x8000)
	{
		if (GetAsyncKeyState(KEY_LEFT) & 0x8000)
		{
			if (0 < m_Body.top && 0 < m_Body.left)
			{
				m_Info.X -= m_Speed / sqrtf(2);
				m_Info.Y -= m_Speed / sqrtf(2);
			}
			else if (0 < m_Body.top)
			{
				m_Info.Y -= m_Speed / sqrtf(2);
			}
			else if (0 < m_Body.left)
			{
				m_Info.X -= m_Speed / sqrtf(2);
			}
		}
		else if (GetAsyncKeyState(KEY_RIGHT) & 0x8000)
		{
			if (0 < m_Body.top && WINCX > m_Body.right)
			{
				m_Info.X += m_Speed / sqrtf(2);
				m_Info.Y -= m_Speed / sqrtf(2);
			}
			else if (0 < m_Body.top)
			{
				m_Info.Y -= m_Speed / sqrtf(2);
			}
			else if (WINCX > m_Body.right)
			{
				m_Info.X += m_Speed / sqrtf(2);
			}
		}
		else
		{
			if (0 < m_Body.top)
				m_Info.Y -= m_Speed;
		}
	}

	if (!(GetKeyState(KEY_UP) & 0x8000) && !(GetKeyState(KEY_DOWN) & 0x8000))
	{
		if ((GetAsyncKeyState(KEY_LEFT) & 0x8000) && 0 < m_Body.left )
			m_Info.X -= m_Speed;

		if ((GetAsyncKeyState(KEY_RIGHT) & 0x8000) && WINCX > m_Body.right)
			m_Info.X += m_Speed;
	}

}

void CPlayer::Create_Bullet(void)
{
	if (m_Bullet)
	{
		m_Bullet->push_back(CAbstractFactory<CBullet>::Create(
			m_Point[OBJECT::POINT_TYPE_AIM],
			OBJECT::POINT_TYPE_AIM,
			m_Radian,
			m_Type
		));
	}
}

const POINT CPlayer::Get_Focus()
{
	return POINT();
}

void CPlayer::Set_Bullet(OBJLIST* _pBullet)
{
	m_Bullet = _pBullet;
}

void CPlayer::Update_Aim(int _cannonsize)
{
	m_Point[OBJECT::POINT_TYPE_AIM].x = long(m_Info.X + _cannonsize*cos(m_Radian));
	m_Point[OBJECT::POINT_TYPE_AIM].y = long(m_Info.Y + _cannonsize*sin(m_Radian));
}
