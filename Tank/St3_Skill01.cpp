#include "stdafx.h"
#include "St3_Skill01.h"
#include "St3_ChaseBullet.h"

St3_Skill01::St3_Skill01()
{
}


St3_Skill01::~St3_Skill01()
{
}

void St3_Skill01::Initialize(void)
{
	DWORD m_FinishTimer = GetTickCount();
	m_Vaild = false;
	m_Count = 30;
}

void St3_Skill01::Attraction(OBJLIST* _bullet, CObj* _ownner)
{
	if (_ownner)
		m_OWnner = _ownner;
	else
		return;
	
	float Radian = 0;

	for (int i = 0; i < 12; i++)
	{
		Radian += PI / 6;

		CObj* temp = new CBullet;
		temp->Initialize();
		temp->Set_Type(m_OWnner->Get_Type());
		temp->Move_Pos(
			m_OWnner->Get_Info().X +  20*cosf(Radian),
			m_OWnner->Get_Info().Y+  20*sinf(Radian)
		);
		temp->Set_Radian(Radian);
		_bullet->push_back(temp);
	}

}


void St3_Skill01::Attraction_Chase(OBJLIST* _bullet, CObj* _ownner)
{
	if (_ownner)
		m_OWnner = _ownner;
	else
		return;

	float Radian = 0;

	for (int i = 0; i < 12; i++)
	{
		Radian += PI / 6;

		CObj* temp = new St3_ChaseBullet;
		temp->Initialize();
		temp->Set_Type(m_OWnner->Get_Type());
		temp->Move_Pos(
			m_OWnner->Get_Info().X + 20 * cosf(Radian),
			m_OWnner->Get_Info().Y + 20 * sinf(Radian)
		);
		temp->Set_Radian(Radian);
		_bullet->push_back(temp);
	}

}