#pragma once
#include "Monster.h"
class CSunflower :
	public CMonster
{
public:
	CSunflower();
	virtual ~CSunflower();

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(OBJLIST* _objlist);
	virtual void		Render(HDC _hDC);
	virtual void		Release(void);

public:
	virtual void		Copy_Data(CObj* _target);

public:
	void				Move();
	void				SunShine();
	void				Jet();
public:
	void				Set_FinMoveDis(float _dis) { finMoveDis = _dis; }
	float&				Get_FinMoveDis() { return finMoveDis;  }
	void				Set_Delay(DWORD _time) { m_Delay = _time; }
	DWORD&				Get_Delay() { return m_Delay; }
	void				Set_BulletCount(int count) { bulletCount = count;  }
	int					Get_BulletCount() { return bulletCount; }

public:
	bool				Check_My_Kids();

private:
	OBJLIST*			m_BulletList = nullptr; 
	POINT				InitPos{};
	float				totalMoveDis = 0.f; 
	float				finMoveDis;
	bool				reach_Dis;
	int					bulletCount;
	int					currCount = 0;
	DWORD				m_CoolTime;
	DWORD				m_Delay;
};

