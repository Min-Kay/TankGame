#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_Type(OBJID::END)
	, m_Dir(OBJECT::DIRECTION_END)
	, m_Radian(NULL)
	, m_Speed(NULL)
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

float CObj::Update_Radian(POINT _focus)
{
	return m_Radian = atan2(_focus.y - m_Info.Y, _focus.x - m_Info.X);
}

void CObj::Rotation_Radian(int _speed)
{
	m_Radian += _speed*(PI / 180);

	if (m_Radian > 2 * PI)
		m_Radian -= 2 * PI;
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

void CObj::Add_PosX(float _fX)
{
	m_Info.X += _fX;
}

void CObj::Add_PosY(float _fY)
{
	m_Info.Y += _fY;
}

void CObj::Add_Speed(float _speed)
{
	m_Speed += _speed; 
}

bool CObj::Check_Type(CObj * _opponent)
{
	if (m_Type == _opponent->Get_Type())
		return true;
	else
		return false;
}

void CObj::Copy_Data(CObj * _target) // 오브젝트 간 데이터 공유를 위함
{
	Set_Size(_target->Get_Info().Width, _target->Get_Info().Height);
	Move_Pos(_target->Get_Info().X, _target->Get_Info().Y); 
}

bool CObj::Screen_Body_Check()
{
	return (WINCX <= m_Body.right || WINCY <= m_Body.bottom || 0 >= m_Body.top || 0 >= m_Body.left) ? true : false;
}

void CObj::Move_Pos(float _x, float _y)
{
	m_Info.X = _x;
	m_Info.Y = _y;
}
