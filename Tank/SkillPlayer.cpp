#include "stdafx.h"
#include "SkillPlayer.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "Satellite.h"
#include "SrecwBullet.h"
#include "GuideBullet.h"
#include "TurnBullet.h"


CSkillPlayer::CSkillPlayer()
	: m_Bullet(nullptr)
	, m_Satellite(nullptr)
{
}


CSkillPlayer::~CSkillPlayer()
{
}

void CSkillPlayer::Initialize(void)
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

int CSkillPlayer::Update(void)
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

void CSkillPlayer::Late_Update(OBJLIST* _objlist)
{

}

void CSkillPlayer::Render(HDC _hDC)
{
	Rectangle(_hDC, 0, 0, 800, 600);
	Ellipse(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
	MoveToEx(_hDC, (int)m_Info.X, (int)m_Info.Y, NULL);
	LineTo(_hDC, m_Point[OBJECT::POINT_TYPE_AIM].x, m_Point[OBJECT::POINT_TYPE_AIM].y);
}

void CSkillPlayer::Release(void)
{
}

void CSkillPlayer::Key_Input(void)
{
	if ((GetAsyncKeyState(KEY_ATTACK) & 0x8000) && (m_CoolTime + m_InitTime < GetTickCount()))
	{
		Create_Bullet();
		m_CoolTime = GetTickCount();
	}
	
	if (GetAsyncKeyState('F') & 0x8000 && (m_CoolTime + 2000<GetTickCount())) {
		m_Bullet->push_back(CAbstractFactory<CBullet>::Create(m_Point[OBJECT::POINT_TYPE_AIM], OBJECT::POINT_TYPE_AIM, 0));
		m_Bullet->push_back(CAbstractFactory<CBullet>::Create(m_Point[OBJECT::POINT_TYPE_AIM], OBJECT::POINT_TYPE_AIM, 45));
		m_Bullet->push_back(CAbstractFactory<CBullet>::Create(m_Point[OBJECT::POINT_TYPE_AIM], OBJECT::POINT_TYPE_AIM, 90));
		m_Bullet->push_back(CAbstractFactory<CBullet>::Create(m_Point[OBJECT::POINT_TYPE_AIM], OBJECT::POINT_TYPE_AIM, 135));
		m_Bullet->push_back(CAbstractFactory<CBullet>::Create(m_Point[OBJECT::POINT_TYPE_AIM], OBJECT::POINT_TYPE_AIM, 180));
		m_Bullet->push_back(CAbstractFactory<CBullet>::Create(m_Point[OBJECT::POINT_TYPE_AIM], OBJECT::POINT_TYPE_AIM, 215));
		m_Bullet->push_back(CAbstractFactory<CBullet>::Create(m_Point[OBJECT::POINT_TYPE_AIM], OBJECT::POINT_TYPE_AIM, 250));
		m_Bullet->push_back(CAbstractFactory<CBullet>::Create(m_Point[OBJECT::POINT_TYPE_AIM], OBJECT::POINT_TYPE_AIM, 285));


		m_CoolTime = GetTickCount();

	}

	if (GetAsyncKeyState('X') & 0x8000 && (m_CoolTime + 2000<GetTickCount())) {

		m_Bullet->push_back(CAbstractFactory<CGuideBullet>::Create(m_Point[OBJECT::POINT_TYPE_AIM], OBJECT::POINT_TYPE_AIM, m_Radian));

		m_CoolTime = GetTickCount();
	}
	if (m_Bullet->empty() == false) {
		if ((m_CoolTime + 3300<GetTickCount())) {
			m_Bullet->pop_front();
			m_CoolTime = GetTickCount();
		}
	}

if (GetAsyncKeyState('G') & 0x8000)
	m_Bullet->push_back(CAbstractFactory<CTurnBullet>::Create(m_Point[OBJECT::POINT_TYPE_AIM], OBJECT::POINT_TYPE_AIM, 1200));

	

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
		if ((GetAsyncKeyState(KEY_LEFT) & 0x8000) && 0 < m_Body.left)
			m_Info.X -= m_Speed;

		if ((GetAsyncKeyState(KEY_RIGHT) & 0x8000) && WINCX > m_Body.right)
			m_Info.X += m_Speed;
	}
	

}

void CSkillPlayer::Create_Bullet(void)
{
	if (m_Bullet)
	{
		//총알 생성 필요
		m_Bullet->push_back(CAbstractFactory<CBullet>::Create(
			m_Point[OBJECT::POINT_TYPE_AIM],
			OBJECT::POINT_TYPE_AIM,
			m_Radian,
			m_Type
		));
	}
}

const POINT CSkillPlayer::Get_Focus()
{
	return POINT();
}



void CSkillPlayer::Set_Bullet(OBJLIST* _pBullet)
{
	m_Bullet = _pBullet;
}

void CSkillPlayer::Update_Aim(int _cannonsize)
{
	m_Point[OBJECT::POINT_TYPE_AIM].x = long(m_Info.X + _cannonsize*cos(m_Radian));
	m_Point[OBJECT::POINT_TYPE_AIM].y = long(m_Info.Y + _cannonsize*sin(m_Radian));
}
