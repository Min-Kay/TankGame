#pragma once
#include "Monster.h"
#include "Enum.h"

class CDispenser :
	public CMonster
{


public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(OBJLIST* _objlist);
	virtual void		Render(HDC _hDC);
	virtual void		Release(void);



public:
	virtual void		Copy_Data(CObj* _target);
	virtual void		Set_Collision();

public:
	void				StateMachine(); 
	void				Idle();
	void				Punch(); 
	void				Billiard();
	void				Groggy();
	void				Check_Hp(); 

	void				Spawn_Ball();
	void				Spawn_Obstacle();

private:
	MONSTER::LEESIN		m_State;
	int					m_Hp;
	int					m_CurrCount;
	CObj*				m_Target = nullptr;
	OBJLIST*			m_Obstacle = nullptr;
	OBJLIST*			m_Ball = nullptr;
	float				m_Angle; 

	DWORD				m_Tick;

	float				m_IdleSpeed;

	int					m_PunchCoolTime;
	int					m_PunchCount;
	int					m_PunchGauge;
	float				m_PunchSpeed;

	int					m_BilliardCoolTime;
	int					m_BilliardCount;
	int					m_RepeatCount;
	int					m_BilliardGauge;
	bool				m_SpawnAllObstacle;
	bool				m_SpawnAllBall;
	

	int					m_GroggyCoolTime;
};

