#include "stdafx.h"
#include "Satellite.h"


CSatellite::CSatellite()
	:	m_Ownner(nullptr)
{
}


CSatellite::~CSatellite()
{
}

void CSatellite::Initialize(void)
{
	m_Info.X = RESPONE_X;
	m_Info.Y = RESPONE_Y;
	m_Info.Width = PLAYER_WIDTH;
	m_Info.Height = PLAYER_HEIGHT;

	m_Type = OBJID::PLAYER;
	m_Point[OBJECT::POINT_TYPE_MOUSE] = { (long)RESPONE_X,(long)RESPONE_Y };
	m_Point[OBJECT::POINT_TYPE_TARGET] = { (long)RESPONE_X,(long)RESPONE_Y };
	m_Dir = OBJECT::DIRECTION_TOP;
	m_Speed = SATELLITE_SPEED;

	Update_Radian(m_Point[OBJECT::POINT_TYPE_TARGET]);
	Update_Rect();
	//주인 주소는 생성시 가져온다
}

int CSatellite::Update(void)
{
	Rotation_Radian(m_Speed); //지속 회전

	Move_Pos(
		m_Ownner->Get_Info().X + 50 * cosf(m_Radian),
		m_Ownner->Get_Info().Y + 50 * sinf(m_Radian)
	);

	Update_Rect();
	return 0;
}

void CSatellite::Late_Update(OBJLIST* _objlist)
{
}

void CSatellite::Render(HDC _hDC)
{
	Ellipse(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void CSatellite::Release(void)
{
}

void CSatellite::Set_Ownner(CObj * _ownner)
{
	m_Ownner = _ownner;
}


