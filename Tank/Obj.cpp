#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_Type(OBJECT::OBJECT_TYPE_END)
	, m_Dir(OBJECT::DIRECTION_END)
	, m_Radian(NULL)
	, m_Speed(NULL)
	, m_Vaild(FALSE)
{
	ZeroMemory(&m_Body, sizeof(m_Body));
	ZeroMemory(&m_Info, sizeof(m_Info));
	ZeroMemory(&m_Point, sizeof(POINT)*OBJECT::POINT_TYPE_END);
}


CObj::~CObj()
{
}


void CObj::Update_Rect(void)
{
	m_Body.left = long(m_Info.X - (m_Info.Width *0.5f));
	m_Body.top = long(m_Info.Y - (m_Info.Height *0.5f));
	m_Body.right = long(m_Info.X + (m_Info.Width *0.5f));
	m_Body.bottom = long(m_Info.Y + (m_Info.Height *0.5f));
}

float CObj::Update_Radian(void)
{
	return m_Radian = atan2(m_Point[OBJECT::POINT_TYPE_MOUSE].y - m_Info.Y, m_Point[OBJECT::POINT_TYPE_MOUSE].x - m_Info.X);
}


void CObj::Set_Size(const long _cx, const long _cy)
{
	m_Info.Width = float(_cx);
	m_Info.Height = float(_cy);
}

void CObj::Set_Point(const POINT & _src, OBJECT::POINT_TYPE _ptype)
{
	m_Point[_ptype] = _src;
}

bool CObj::Screen_Body_Check()
{
	if (WINCX <= m_Body.right ||
		WINCY <= m_Body.bottom ||
		0 >= m_Body.left ||
		0 >= m_Body.right)
		return true;
	
	return false;
}

void CObj::Move_Pos(float _x, float _y)
{
	m_Info.X = _x;
	m_Info.Y = _y;
}
