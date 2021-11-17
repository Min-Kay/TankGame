#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_Info.X = 200.f;
	m_Info.Y = 200.f;

	m_Info.Width	= 30.f;
	m_Info.Height	= 30.f;
	m_Speed			=  5.f;
}

int CMonster::Update(void)
{

	if (true == m_Dead)
		return OBJ_DEAD;

	//m_Info.X += m_Speed;

	Update_Rect();

	return OBJ_NOEVENT;

}

void CMonster::Late_Update(void)
{
	if ((100 >= m_Body.left) || (WINCX - 100 <= m_Body.right))
		m_Speed *= -1.f;
}

void CMonster::Render(HDC _hDC)
{
	Rectangle(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void CMonster::Release(void)
{
}
