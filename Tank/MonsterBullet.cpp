#include "stdafx.h"
#include "MonsterBullet.h"


CMonsterBullet::CMonsterBullet()
	: m_CenterSpeed(0.f), m_RevolutionAngle(0.f), m_Start(true)
{
	ZeroMemory(&m_CenterPos, sizeof(m_CenterPos));
}



CMonsterBullet::~CMonsterBullet()
{
}


void CMonsterBullet::Initialize(void)
{
	m_Info.Width = BULLET_WIDTH;
	m_Info.Height = BULLET_HEIGHT;
	m_Speed = BULLET_SPEED+5.f;
	m_Type = OBJID::MISSILE;
	Update_Rect();

	m_CenterSpeed = 5.f;
	m_Distance = 40.f;
	m_RevolutionAngle = 50.f;
}

int CMonsterBullet::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;

	Update_Locate(m_Speed);
	Update_Rect();



	return OBJ_NOEVENT;

	//if (m_Start)
	//{
	//	m_CenterPos.x = m_Info.X;
	//	m_CenterPos.y = m_Info.Y;
	//	m_RevolutionAngle = m_Radian;
	//	m_Start = false;
	//}


	//m_CenterPos.x += m_CenterSpeed * cosf(m_RevolutionAngle * PI / 180.f);
	//m_CenterPos.y -= m_CenterSpeed * sinf(m_RevolutionAngle * PI / 180.f);

	//m_Info.X = m_CenterPos.x + (m_Distance * cosf(m_Radian * PI / 180.f));
	//m_Info.Y = m_CenterPos.y - (m_Distance * sinf(m_Radian * PI / 180.f));

	//m_Radian += m_Speed;

	//Update_Rect();

	//return OBJ_NOEVENT;
	//if (m_Dead)
	//	return OBJ_DEAD;

	//Update_Locate(m_Speed);
	//Update_Rect();

}

void CMonsterBullet::Late_Update(OBJLIST* _objlist)
{
	if (Screen_Body_Check())
		Set_Dead(true);
}

void CMonsterBullet::Render(HDC _hDC)
{
	Rectangle(_hDC, m_Body.left, m_Body.top + 20, m_Body.right + 10, m_Body.bottom + 50);

	MoveToEx(_hDC, m_Info.X - 4, m_Info.Y + 17, NULL);
	LineTo(_hDC, m_Info.X -8, m_Info.Y + 5);
	LineTo(_hDC, m_Info.X - 3, m_Info.Y + 10);
	LineTo(_hDC, m_Info.X , m_Info.Y + 5);
	LineTo(_hDC, m_Info.X+3, m_Info.Y + 10);
	LineTo(_hDC, m_Info.X + 6, m_Info.Y + 5);
	LineTo(_hDC, m_Info.X + 9, m_Info.Y + 10);
	LineTo(_hDC, m_Info.X + 16, m_Info.Y + 5);
	LineTo(_hDC, m_Info.X + 12, m_Info.Y + 17);
	//왼쪽 뒷날개
	MoveToEx(_hDC, m_Info.X - 4, m_Info.Y + 17, NULL);
	LineTo(_hDC, m_Info.X - 25, m_Info.Y + 17);
	LineTo(_hDC, m_Info.X - 25, m_Info.Y + 23);
	LineTo(_hDC, m_Info.X - 3, m_Info.Y + 28);
	//오른쪽 뒷날개
	MoveToEx(_hDC, m_Info.X + 12, m_Info.Y + 17, NULL);
	LineTo(_hDC, m_Info.X + 30, m_Info.Y + 17);
	LineTo(_hDC, m_Info.X + 30, m_Info.Y + 23);
	LineTo(_hDC, m_Info.X + 10, m_Info.Y + 28);
	//왼쪽 앞날개
	MoveToEx(_hDC, m_Info.X - 4, m_Info.Y + 35, NULL);
	LineTo(_hDC, m_Info.X - 25, m_Info.Y + 35);
	LineTo(_hDC, m_Info.X - 25, m_Info.Y + 41);
	LineTo(_hDC, m_Info.X - 3, m_Info.Y + 46);
	//앞날개 오른쪽
	MoveToEx(_hDC, m_Info.X + 12, m_Info.Y + 35, NULL);
	LineTo(_hDC, m_Info.X + 30, m_Info.Y + 35);
	LineTo(_hDC, m_Info.X + 30, m_Info.Y + 41);
	LineTo(_hDC, m_Info.X + 10, m_Info.Y + 46);

	//포신?

	MoveToEx(_hDC, m_Info.X - 3, m_Info.Y + 51, NULL);
	LineTo(_hDC, m_Info.X + 4, m_Info.Y + 65);
	LineTo(_hDC, m_Info.X + 12, m_Info.Y + 51);
	  
}

void CMonsterBullet::Release(void)
{
}
