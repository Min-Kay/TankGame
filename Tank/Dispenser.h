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

public:
	void				Ready_To_Play();
	float				Calc_Distance(POINT dest, POINT src); 
	void				Set_Angle_To_Target(POINT dest, POINT src);
	void				Check_Hp(); 

public:
	void				LockOn(); 
	void				Shoot(); 

public:
	void				Spawn_Ball();
	void				Spawn_Obstacle();

private:
	MONSTER::LEESIN		m_State;
	int					m_InitHp;
	int					m_Hp = 0;
	int					m_CurrCount;
	CObj*				m_Target = nullptr;
	OBJLIST*			m_Obstacle = nullptr;
	OBJLIST*			m_Ball = nullptr;
	float				m_Angle; 
	HBRUSH				m_brush = NULL;
	HGDIOBJ				ori = NULL;
	HGDIOBJ				pen = NULL;


	DWORD				m_Tick;

	float				m_IdleSpeed;


	POINT				target_Point;
	POINT				info_Point;

	bool				m_Enrage;

	int					m_ReadyTime;
	bool				m_Ready;

	int					m_PunchCoolTime;
	int					m_PunchCount;
	int					m_PunchGauge;
	float				m_PunchSpeed;
	int					m_LockTime;
	POINT				m_LockPoint;
	float				m_LockSpeed; 
	float				m_ShootSpeed;
	HBRUSH				m_LockBrush = NULL;
	bool				m_InitLock;
	bool				m_LockOn;
	bool				m_SetAngle; 
	bool				m_Shoot; 

	int					m_BilliardCoolTime;
	int					m_BilliardCount;
	int					m_RepeatCount;
	int					m_BilliardGauge;
	bool				m_SpawnAllObstacle;
	bool				m_SpawnAllBall;
	
	int					m_GroggyCoolTime;

};

