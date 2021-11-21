#include "stdafx.h"
#include "Pet.h"

void CPet::Initialize(void)
{
	m_Type = OBJID::PLAYER;
	m_Info.X = 0.f;
	m_Info.Y = 0.f;
	m_Info.Width = 15.f;
	m_Info.Height = 15.f;

	m_Speed = 0.05f; 
	m_Hp = 3;
}

int CPet::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;

	if (m_target)
	{
		m_TargetInfo = { long(m_target->Get_Info().X) ,long(m_target->Get_Info().Y)};
		m_PetInfo = { long(m_Info.X) , long(m_Info.Y)};

		if (Calc_Distance(m_TargetInfo, m_PetInfo) >= 50.f)
		{
			if (m_TargetInfo.x < m_PetInfo.x)
				m_Info.X -= abs(m_PetInfo.x - m_TargetInfo.x) * 0.5f * m_Speed;
			else if (m_TargetInfo.x > m_PetInfo.x)
				m_Info.X += abs(m_PetInfo.x - m_TargetInfo.x) * 0.5f * m_Speed;

			if (m_TargetInfo.y < m_PetInfo.y)
				m_Info.Y -= abs(m_PetInfo.y - m_TargetInfo.y) * 0.5f * m_Speed;
			else if (m_TargetInfo.y > m_PetInfo.y)
				m_Info.Y += abs(m_PetInfo.y - m_TargetInfo.y) * 0.5f * m_Speed;
		}
	}

	Update_Rect(); 

	return OBJ_NOEVENT;
}

void CPet::Late_Update(OBJLIST* _objlist)
{
	if (!m_target)
	{
		m_target = _objlist[OBJID::PLAYER].front(); 
		Move_Pos(m_target->Get_Info().X + 50, m_target->Get_Info().Y);
	}

	if (m_Hp <= 0)
		Set_Dead(true);
}

void CPet::Render(HDC _hDC)
{
	Rectangle(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void CPet::Release(void)
{
}

bool CPet::Check_Type(CObj* _opponent)
{
	return false;
}

void CPet::Copy_Data(CObj* _target)
{
	Move_Pos(_target->Get_Info().X, _target->Get_Info().Y);
	Set_Size(_target->Get_Info().Width, _target->Get_Info().Height);
	Initialize();
}

float CPet::Calc_Distance(POINT dest, POINT src)
{
	float	fX = dest.x - src.x;
	float	fY = dest.y - src.y;

	return sqrtf(fX * fX + fY * fY);
}

void CPet::Set_Angle_To_Target(POINT dest, POINT src)
{
	float	fRadian = acosf((dest.x - src.x) / Calc_Distance(dest, src));

	m_Angle = fRadian * 180.f / PI;

	if (dest.y > src.y)
		m_Angle *= -1.f;
}
