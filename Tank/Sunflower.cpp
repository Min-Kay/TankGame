#include "stdafx.h"
#include "Sunflower.h"
#include "Obj.h"
#include  "SunBullet.h"

CSunflower::CSunflower()
{
}


CSunflower::~CSunflower()
{
}

void CSunflower::Initialize(void)
{
	m_CoolTime = GetTickCount();
	Set_Delay(1000);
	Set_FinMoveDis(30.f);
	Set_BulletCount(9);
}

int CSunflower::Update(void)
{
	if (m_Dead)
	{
		for (auto& i : *m_BulletList)
		{
			if (static_cast<CSunBullet*>(i))
			{
				if (this == static_cast<CSunBullet*>(i)->Get_Parent())
					static_cast<CSunBullet*>(i)->Set_Parent(nullptr);
			}
		}
		return OBJ_DEAD;
	}

	Move(); 

	SunShine();

	Jet();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CSunflower::Late_Update(OBJLIST * _objlist)
{
	if (!m_BulletList)
	{
		m_BulletList = &_objlist[OBJID::MISSILE];
		Update_Rect(); 
	}

	if (Screen_Body_Check() || m_Hp <= 0)
		Set_Dead(true);

}

void CSunflower::Render(HDC _hDC)
{
	MoveToEx(_hDC, (m_Info.X - m_Info.Width / 2) + cosf(m_Radian), (m_Info.Y - m_Info.Height / 2) - sinf(m_Radian), nullptr);
	LineTo(_hDC, (m_Info.X + m_Info.Width / 2) + cosf(m_Radian), (m_Info.Y - m_Info.Height / 2) - sinf(m_Radian));
	LineTo(_hDC, (m_Info.X) + cosf(m_Radian), (m_Info.Y + m_Info.Height / 2) - sinf(m_Radian));
	LineTo(_hDC, (m_Info.X - m_Info.Width / 2) + cosf(m_Radian), (m_Info.Y - m_Info.Height / 2) - sinf(m_Radian));

	MoveToEx(_hDC, (m_Info.X) + cosf(m_Radian), (m_Info.Y - m_Info.Height / 2) - sinf(m_Radian), nullptr);
	LineTo(_hDC, (m_Info.X - m_Info.Width / 4) + cosf(m_Radian), (m_Info.Y) - sinf(m_Radian));
	LineTo(_hDC, (m_Info.X + m_Info.Width / 4) + cosf(m_Radian), (m_Info.Y) - sinf(m_Radian));
	LineTo(_hDC, (m_Info.X) + cosf(m_Radian), (m_Info.Y - m_Info.Height / 2) - sinf(m_Radian));

}

void CSunflower::Release(void)
{
}

void CSunflower::Copy_Data(CObj* _target)
{
	Move_Pos(_target->Get_Info().X, _target->Get_Info().Y);
	Set_Size(_target->Get_Info().Width, _target->Get_Info().Height);
	Set_Speed(_target->Get_Speed());
	Set_Radian(_target->Get_Radian());
	Set_FinMoveDis(static_cast<CSunflower*>(_target)->Get_FinMoveDis());
	Set_Delay(static_cast<CSunflower*>(_target)->Get_Delay());
	Set_BulletCount(static_cast<CSunflower*>(_target)->Get_BulletCount());
	InitPos.x = m_Info.X;
	InitPos.y = m_Info.Y;
}

void CSunflower::Set_Collision()
{
	--m_Hp;
}

void CSunflower::Move()
{
	if (finMoveDis <= totalMoveDis)
	{
		reach_Dis = true; 
		return; 
	}

	float fx = m_Info.X - InitPos.x;
	float fy = m_Info.Y - InitPos.y;

	totalMoveDis = sqrtf(fx*fx + fy*fy);

	m_Info.X += m_Speed * cosf(m_Radian);
	m_Info.Y -= m_Speed * sinf(m_Radian);
	
}

void CSunflower::SunShine()
{	
	if (!reach_Dis || bulletCount <= currCount )
		return; 

	if (m_CoolTime + m_Delay <= GetTickCount())
	{
		CObj* temp = new CSunBullet;
		temp->Set_Type(m_Type);
		static_cast<CSunBullet*>(temp)->Set_Parent(static_cast<CObj*>(this));
		static_cast<CSunBullet*>(temp)->Set_Distance(25.f);
		static_cast<CSunBullet*>(temp)->Set_SpinCount(bulletCount +  1);
		temp->Set_Radian(this->Get_Radian());
		temp->Initialize();
		m_BulletList->push_back(temp);
		m_CoolTime = GetTickCount();
		++currCount;
	}
}

void CSunflower::Jet()
{
	if (bulletCount > currCount || Check_My_Kids())
		return;

	m_Info.X += m_Speed * 30.f * cosf(m_Radian);
	m_Info.Y -= m_Speed * 30.f* sinf(m_Radian);
	
}

bool CSunflower::Check_My_Kids()
{

	for (auto& i : *m_BulletList)
	{
		if (static_cast<CSunBullet*>(i) && static_cast<CSunBullet*>(i)->Get_Parent() == this)
			return true;
	}

	return false;
}
