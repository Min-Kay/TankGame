#include "stdafx.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Bullet.h"

CMonster::CMonster()	
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_Info.Width	= 50.f;
	m_Info.Height	= 50.f;
	m_Speed			=  5.f;
	m_Type			= OBJID::MONSTER;
	m_Cooltime		= GetTickCount();
}

int CMonster::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;

}

void CMonster::Late_Update(OBJLIST* _objlist)
{

}

void CMonster::Render(HDC _hDC)
{
	Rectangle(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void CMonster::Release(void)
{
}

