#include "stdafx.h"
#include "Dispenser.h"
#include "Wall.h"
#include "Ball.h"
#include <time.h>
#include "AbstractFactory.h"

void CDispenser::Initialize(void)
{
	srand(unsigned(time(NULL)));
	m_Info.Height = 60;
	m_Info.Width = 40;

	m_Type = OBJID::MONSTER; 

	m_State = MONSTER::IDLE;
	m_Hp = 100;
	m_CurrCount = 0;
	m_Angle = 0;

	m_Tick = GetTickCount();

	m_IdleSpeed = 1.0f;

	m_PunchCoolTime = 2000;
	m_PunchCount = 5;
	m_PunchGauge = 0;
	m_PunchSpeed = 30.f;

	m_BilliardCoolTime = 1000; 
	m_BilliardCount = 7;
	m_BilliardGauge = 0;

	m_GroggyCoolTime = 5000;
	
	m_RepeatCount = 0; 

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
	Ellipse(_hDC,m_Body.left,m_Body.top, m_Body.right, m_Body.bottom);
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
	//m_PunchGauge += rand() % 50;
	m_BilliardGauge += rand() % 50;

	if (m_PunchGauge > 1000)
	{
		m_State = MONSTER::PUNCH;
		m_PunchGauge = 0;
		return;
	}
	
	if (m_BilliardGauge > 1000)
	{
		m_State = MONSTER::BILLIARD;
		m_BilliardGauge = 0;
		return;
	}

	// 움직이기

	if (m_Target)
	{
		float	fX = m_Target->Get_Info().X - m_Info.X;
		float	fY = m_Target->Get_Info().Y - m_Info.Y;

		float	fDistance = sqrtf(fX * fX + fY * fY);

		float	fRadian = acosf(fX / fDistance);

		m_Angle = fRadian * 180.f / PI;

		if (m_Target->Get_Info().Y > m_Info.Y)
			m_Angle *= -1.f;

		m_Info.X += cosf(m_Angle * PI / 180.f) * m_IdleSpeed;
		m_Info.Y -= sinf(m_Angle * PI / 180.f) * m_IdleSpeed;
	}
}

void CDispenser::Punch()
{
	// count만큼 진행
	// 타겟을 향해 돌진
		
	/*if (m_CurrCount >= m_PunchCount)
	{
		m_State = MONSTER::GROGGY;
		m_CurrCount = 0;
		m_Tick = GetTickCount();
	}*/
}

void CDispenser::Billiard()
{
		// count만큼 진행
		// 먼저 공을 흩뿌림
		// 그 공들을 향해 쏘는 장애물들 발사

	Spawn_Obstacle();
	Spawn_Ball();

	if (m_SpawnAllBall && m_SpawnAllObstacle)
	{
		m_State = MONSTER::GROGGY;
		m_SpawnAllBall = false;
		m_SpawnAllObstacle = false; 
		m_Tick = GetTickCount();
	}
}

void CDispenser::Groggy()
{
	if (m_Tick + m_GroggyCoolTime < GetTickCount())
		m_State = MONSTER::IDLE;
}

void CDispenser::Check_Hp()
{
	if (m_Hp <= 0)
		m_State = MONSTER::DEAD;
}

void CDispenser::Spawn_Obstacle()
{
	if (m_SpawnAllObstacle)
		return;

	if (m_Tick + m_BilliardCoolTime < GetTickCount())
	{
		for (int i = 0; i < m_BilliardCount  /  2; ++i)
		{
			int size = rand() % 30 + 20;
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
			int size = rand() % 30 + 20;
			int angle = rand() % 360;
			CObj* ball = CAbstractFactory<CBall>::Create(m_Info.X, m_Info.Y, size, size, angle * 180.f / PI);
			static_cast<CBall*>(ball)->Set_Angle();
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

