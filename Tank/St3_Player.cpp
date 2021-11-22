#include "stdafx.h"
#include "St3_Player.h"
#include "Def_St3.h"
#include "St3_ChaseBullet.h"
#include "St3_FireBullet.h"
#include "AbstractFactory.h"
#include "St3_CollisionMgr.h"
#include "St3_Skill01.h"
#include "St3_MineBullet.h"

St3_Player::St3_Player()
{
	m_FPS = 65;
	m_CoolTimeZ = 0;
}


St3_Player::~St3_Player()
{
}

int St3_Player::Update(void)
{
	if (m_CoolTimeC > 0)
		--m_CoolTimeC;
	else
		m_CoolTimeC = 2;

	if (true == m_Dead)
		return OBJ_DEAD;

	GetCursorPos(&m_Point[OBJECT::POINT_TYPE_MOUSE]);
	ScreenToClient(g_hWnd, &m_Point[OBJECT::POINT_TYPE_MOUSE]);
	ShowCursor(false);


	Key_Input(); //키입력
	Key_Input_Plus();

	Update_Rect();
	Update_Radian(m_Point[OBJECT::POINT_TYPE_MOUSE]);
	Update_Aim(PLAYER_CANNON_LEN);
	return OBJ_NOEVENT;
}

void St3_Player::Late_Update(OBJLIST * _objlist)
{
	
}

void St3_Player::Render(HDC _hDC)
{
	if (m_FPS <= 0)
		m_FPS = 65;
	else
		--m_FPS;

	Rectangle(_hDC, 0, 0, 800, 600);
	Ellipse(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
	MoveToEx(_hDC, (int)m_Info.X, (int)m_Info.Y, NULL);
	LineTo(_hDC, m_Point[OBJECT::POINT_TYPE_AIM].x, m_Point[OBJECT::POINT_TYPE_AIM].y);

	

}

void St3_Player::Release(void)
{
	SAFE_DELETE(m_Satellite);
}

void St3_Player::Key_Input_Plus(void)
{

	if (GetAsyncKeyState(VK_Z) & 0x8000 && (m_FPS <= 0))
	{
		CObj* temp = CAbstractFactory<St3_MineBullet>::Create();
		temp->Set_Type(OBJID::END);
		temp->Move_Pos(m_Info.X + (rand()% 100) - 50, m_Info.Y + (rand() %100) - 50);
		m_Bullet->push_back(temp);

	}

	if (GetAsyncKeyState(VK_X) & 0x8000 && m_CoolTimeZ +500<GetTickCount())
	{
		St3_Skill01().Attraction_Chase(m_Bullet,this);
		m_CoolTimeZ = GetTickCount();
	}

	if (GetAsyncKeyState(VK_C) & 0x8000 && m_CoolTimeC<=0)
	{
		Create_FireBullet();
	}
}

void St3_Player::Create_ChaseBullet(void)
{
	if (m_Bullet)
	{
		//총알 생성 필요
		m_Bullet->push_back(CAbstractFactory<St3_ChaseBullet>::Create(
			m_Point[OBJECT::POINT_TYPE_AIM],
			m_Radian,
			m_Type
		));
	}
}

void St3_Player::Create_FireBullet(void)
{
	if (m_Bullet)
	{
		//총알 생성 필요
		m_Bullet->push_back(CAbstractFactory<St3_FireBullet>::Create(
			m_Point[OBJECT::POINT_TYPE_AIM],
			m_Radian,
			m_Type
		));
	}
}
