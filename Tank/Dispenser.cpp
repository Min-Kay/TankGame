#include "stdafx.h"
#include "Dispenser.h"
#include "Wall.h"
#include "Ball.h"
#include <time.h>
#include "AbstractFactory.h"

void CDispenser::Initialize(void)
{
	srand(unsigned(time(NULL)));
	m_Info.Height = 40;
	m_Info.Width = 40;

	m_Type = OBJID::MONSTER; 

	m_State = MONSTER::IDLE;
	m_InitHp = 100;
	m_Hp = m_InitHp;
	m_CurrCount = 0;
	m_Angle = 0;

	m_Tick = GetTickCount();

	m_IdleSpeed = 1.0f;

	m_PunchCoolTime = 2000;
	m_PunchCount = 3;
	m_PunchGauge = 0;
	m_PunchSpeed = 30.f;

	m_BilliardCoolTime = 1000; 
	m_BilliardCount = 5;
	m_BilliardGauge = 0;

	m_GroggyCoolTime = 4000;
	
	m_RepeatCount = 0; 

	m_Enrage = false;
	m_Ready = false;
	m_ReadyTime = 1500;

	m_LockTime = 2000;
	m_LockSpeed = 10.f;

	m_ShootSpeed = 30.f; 

	m_InitLock = false; 
	m_LockOn = false; 
	m_SetAngle = false; 
	m_Shoot = false; 

	m_SpawnAllBall = false; 
	m_SpawnAllObstacle = false; 
}

int CDispenser::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;

	StateMachine();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CDispenser::Late_Update(OBJLIST* _objlist)
{
	if (!m_Target)
	{
		m_Target = _objlist[OBJID::PLAYER].front(); 
		Update_Rect(); 
	}


	if (!m_Ball)
	{
		m_Ball = &_objlist[OBJID::MISSILE];
	}


	if (!m_Obstacle)
	{
		m_Obstacle = &_objlist[OBJID::OBSTACLE];
	}

	Check_Hp();
	
}

void CDispenser::Render(HDC _hDC)
{
	ori = SelectObject(_hDC,GetStockObject(DC_PEN));
	SetDCPenColor(_hDC, RGB(60, 60, 100));
	Rectangle(_hDC,m_Body.left,m_Body.top, m_Body.right, m_Body.bottom); // 본체

	// 본체 사방 사각
	Rectangle(_hDC, m_Body.right, m_Body.top, m_Body.right + m_Info.Width  * 0.5f, m_Body.bottom);
	Rectangle(_hDC, m_Body.left - m_Info.Width * 0.5f, m_Body.top, m_Body.left, m_Body.bottom);
	Rectangle(_hDC, m_Body.left, m_Body.top - m_Info.Width * 0.5f, m_Body.right, m_Body.top);
	Rectangle(_hDC, m_Body.left, m_Body.bottom, m_Body.right, m_Body.bottom + m_Info.Width * 0.5f);

	// 사방 사각 잇는 선
	MoveToEx(_hDC, m_Body.right + m_Info.Width * 0.5f, m_Body.top,nullptr);
	LineTo(_hDC, m_Body.right, m_Body.top - m_Info.Width * 0.5f);

	MoveToEx(_hDC, m_Body.left - m_Info.Width * 0.5f, m_Body.top, nullptr);
	LineTo(_hDC, m_Body.left, m_Body.top - m_Info.Width * 0.5f);

	MoveToEx(_hDC, m_Body.right + m_Info.Width * 0.5f, m_Body.bottom, nullptr);
	LineTo(_hDC, m_Body.right, m_Body.bottom + m_Info.Width * 0.5f);

	MoveToEx(_hDC, m_Body.left - m_Info.Width * 0.5f, m_Body.bottom, nullptr);
	LineTo(_hDC, m_Body.left, m_Body.bottom + m_Info.Width * 0.5f);

	switch (m_State)
	{
	case MONSTER::IDLE:
		m_brush = CreateSolidBrush(RGB(0,255,0));
		break;
	case MONSTER::GROGGY:
		m_brush = CreateSolidBrush(RGB(255, 0, 0));
		break; 
	case MONSTER::PUNCH:
		m_brush = CreateSolidBrush(RGB(255, 255, 0));
		break;
	case MONSTER::BILLIARD:
		m_brush = CreateSolidBrush(RGB(120, 0, 150));
		break;
	}
	FillRect(_hDC, &m_Body, m_brush);

	if (m_State == MONSTER::PUNCH && m_Ready )
	{
		if (!m_LockOn && !m_Shoot)
		{
			SetDCPenColor(_hDC, RGB(255, 0, 0));
			MoveToEx(_hDC, m_Info.X, m_Info.Y, nullptr);
			LineTo(_hDC, m_LockPoint.x, m_LockPoint.y);
			Ellipse(_hDC, m_LockPoint.x - 10, m_LockPoint.y - 10, m_LockPoint.x + 10, m_LockPoint.y + 10);
			MoveToEx(_hDC, m_LockPoint.x + 5, m_LockPoint.y, nullptr);
			LineTo(_hDC, m_LockPoint.x + 15, m_LockPoint.y);
			MoveToEx(_hDC, m_LockPoint.x - 5, m_LockPoint.y, nullptr);
			LineTo(_hDC, m_LockPoint.x - 15, m_LockPoint.y);
			MoveToEx(_hDC, m_LockPoint.x, m_LockPoint.y + 5, nullptr);
			LineTo(_hDC, m_LockPoint.x, m_LockPoint.y + 15);
			MoveToEx(_hDC, m_LockPoint.x, m_LockPoint.y - 5, nullptr);
			LineTo(_hDC, m_LockPoint.x, m_LockPoint.y - 15);
		}
		else if (m_Shoot)
		{
			SetDCPenColor(_hDC, RGB(0, 255, 0));
			MoveToEx(_hDC, m_Info.X, m_Info.Y, nullptr);
			LineTo(_hDC, m_LockPoint.x, m_LockPoint.y);
			Ellipse(_hDC, m_LockPoint.x - 10, m_LockPoint.y - 10, m_LockPoint.x + 10, m_LockPoint.y + 10);
			MoveToEx(_hDC, m_LockPoint.x + 5, m_LockPoint.y, nullptr);
			LineTo(_hDC, m_LockPoint.x + 15, m_LockPoint.y);
			MoveToEx(_hDC, m_LockPoint.x - 5, m_LockPoint.y, nullptr);
			LineTo(_hDC, m_LockPoint.x - 15, m_LockPoint.y);
			MoveToEx(_hDC, m_LockPoint.x, m_LockPoint.y + 5, nullptr);
			LineTo(_hDC, m_LockPoint.x, m_LockPoint.y + 15);
			MoveToEx(_hDC, m_LockPoint.x, m_LockPoint.y - 5, nullptr);
			LineTo(_hDC, m_LockPoint.x, m_LockPoint.y - 15);
		}

	}

	SelectObject(_hDC, ori);
}

void CDispenser::Release(void)
{
}

void CDispenser::Copy_Data(CObj* _target)
{
	Move_Pos(_target->Get_Info().X, _target->Get_Info().Y);
	Initialize(); 
}

void CDispenser::Set_Collision()
{
	m_Hp -= 10;
}

void CDispenser::StateMachine()
{
	switch (m_State)
	{
	case MONSTER::IDLE:
		Idle(); 
		break;
	case MONSTER::PUNCH:
		Punch();
		break;
	case MONSTER::BILLIARD:
		Billiard();
		break;
	case MONSTER::GROGGY:
		Groggy();
		break;
	case MONSTER::DEAD:
		for (auto& i : *m_Obstacle)
		{
			if(static_cast<CWall*>(i) && static_cast<CWall*>(i)->Get_Parent() == this)
				i->Set_Dead(true);
		}
		Set_Dead(true);
		break;
	}
}

void CDispenser::Idle()
{
	m_PunchGauge += rand() % 5;
	m_BilliardGauge += rand() % 5;

	if (m_PunchGauge > 1000)
	{
		m_State = MONSTER::PUNCH;
		m_PunchGauge = 0;
		m_BilliardGauge *= 0.5f;
		m_Tick = GetTickCount();
		return;
	}
	
	if (m_BilliardGauge > 1000)
	{
		m_State = MONSTER::BILLIARD;
		m_BilliardGauge = 0;
		m_PunchGauge *= 0.5f;
		m_Tick = GetTickCount();
		return;
	}

	if (m_Target)
	{
		target_Point = {long(m_Target->Get_Info().X), long(m_Target->Get_Info().Y)};
		info_Point = {long(m_Info.X), long(m_Info.Y)};
		Set_Angle_To_Target(target_Point, info_Point); 

		m_Info.X += cosf(m_Angle * PI / 180.f) * m_IdleSpeed;
		m_Info.Y -= sinf(m_Angle * PI / 180.f) * m_IdleSpeed;
	}
}

void CDispenser::Punch()
{
	Ready_To_Play();

	if (m_Ready)
	{
		LockOn();
		Shoot();

		if (m_CurrCount >= m_PunchCount)
		{
			m_State = MONSTER::GROGGY;
			m_CurrCount = 0;
			m_Ready = false; 
			m_Tick = GetTickCount();
		}
	}
}

void CDispenser::Billiard()
{
	Ready_To_Play(); 

	if (m_Ready)
	{
		Spawn_Obstacle();
		Spawn_Ball();

		if (m_SpawnAllBall && m_SpawnAllObstacle)
		{
			m_State = MONSTER::GROGGY;
			m_SpawnAllBall = false;
			m_SpawnAllObstacle = false;
			m_Ready = false; 
			m_Tick = GetTickCount();
		}
	}
}

void CDispenser::Groggy()
{
	if (m_Tick + m_GroggyCoolTime < GetTickCount())
		m_State = MONSTER::IDLE;
}

void CDispenser::Ready_To_Play()
{
	if (m_Ready)
		return;

	if (m_Tick + m_ReadyTime < GetTickCount() || m_Enrage)
	{
		m_Tick = GetTickCount(); 
		m_Ready = true; 
	}
}

float CDispenser::Calc_Distance(POINT dest, POINT src)
{
	float	fX = dest.x - src.x;
	float	fY = dest.y - src.y;

	return sqrtf(fX * fX + fY * fY);
}

void CDispenser::Set_Angle_To_Target(POINT dest, POINT src)
{
	float	fRadian = acosf((dest.x - src.x )/ Calc_Distance(dest, src));

	m_Angle = fRadian * 180.f / PI;

	if (dest.y > src.y)
		m_Angle *= -1.f;
}

void CDispenser::Check_Hp()
{
	if (m_Hp <= 0)
		m_State = MONSTER::DEAD;
	else if (m_Hp <= m_InitHp * 0.5f)
		m_Enrage = true; 
}

void CDispenser::LockOn()
{
	if (m_LockOn)
		return;

	if (!m_InitLock)
	{
		m_LockPoint.x = m_Info.X;
		m_LockPoint.y = m_Info.Y;
		m_InitLock = true; 
		m_Tick = GetTickCount(); 
	}

	target_Point = {long(m_Target->Get_Info().X), long(m_Target->Get_Info().Y)};

	Set_Angle_To_Target(target_Point, m_LockPoint);

	m_LockPoint.x += cosf(m_Angle * PI / 180.f) * m_LockSpeed;
	m_LockPoint.y -= sinf(m_Angle * PI / 180.f) * m_LockSpeed;

	if (Calc_Distance(target_Point, m_LockPoint) <= 5.0f || m_Tick + m_LockTime < GetTickCount())
	{
		m_LockOn = true; 
		m_InitLock = false; 
		m_Shoot = true; 
		m_Tick = GetTickCount();
	}
}

void CDispenser::Shoot()
{
	if (!m_LockOn && !m_Shoot)
		return;

	if (!m_SetAngle)
	{
		info_Point = { long(m_Info.X), long(m_Info.Y) };

		Set_Angle_To_Target(m_LockPoint, info_Point);

		m_SetAngle = true; 
	}
	
	m_Info.X += cosf(m_Angle * PI / 180.f) * m_ShootSpeed;
	m_Info.Y -= sinf(m_Angle * PI / 180.f) * m_ShootSpeed;

	info_Point = { long(m_Info.X), long(m_Info.Y) };

	if (Calc_Distance(m_LockPoint, info_Point) <= m_ShootSpeed)
	{
		m_LockOn = false;
		m_Shoot = false; 
		m_SetAngle = false; 
		++m_CurrCount;
	}
}

void CDispenser::Spawn_Obstacle()
{
	if (m_SpawnAllObstacle)
		return;

	if (m_Tick + m_BilliardCoolTime < GetTickCount())
	{
		for (int i = 0; i < int(m_BilliardCount); ++i)
		{
			int size = rand() % 30 + 30;
			int distance = rand() % 300 + 100;
			int angle = rand() % 360;
			CObj* obstacle = CAbstractFactory<CWall>::Create(m_Info.X, m_Info.Y, size, size, angle * 180.f / PI);
			static_cast<CWall*>(obstacle)->Set_Distance(distance);
			static_cast<CWall*>(obstacle)->Set_InitPos();
			static_cast<CWall*>(obstacle)->Set_Angle();
			static_cast<CWall*>(obstacle)->Set_Parent(this);
			m_Obstacle->push_back(obstacle);
		}
		m_Tick = GetTickCount();
		++m_RepeatCount;
		if (m_RepeatCount >= 3)
		{
			m_SpawnAllObstacle = true;
			m_RepeatCount = 0; 
		}
	}
}

void CDispenser::Spawn_Ball()
{
	if (m_SpawnAllBall || !m_SpawnAllObstacle)
		return;

	if (m_Tick + m_BilliardCoolTime < GetTickCount())
	{
		for (int i = 0; i < m_BilliardCount; ++i)
		{
			int size = rand() % 20 + 20;
			int angle = rand() % 360;
			CObj* ball = CAbstractFactory<CBall>::Create(m_Info.X, m_Info.Y, size, size, angle * 180.f / PI);
			m_Ball->push_back(ball);
		}
		m_Tick = GetTickCount();
		++m_RepeatCount;
		if (m_RepeatCount >= 3)
		{
			m_SpawnAllBall = true;
			m_RepeatCount = 0;
		}
	}
}

