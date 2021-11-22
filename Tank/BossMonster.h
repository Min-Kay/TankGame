#pragma once
#include "Monster.h"
class CBossMonster :
	public CMonster
{
public:
	CBossMonster();
	virtual ~CBossMonster();

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(OBJLIST* _objlist);
	virtual void		Render(HDC _hDC);
	virtual void		Release(void);

private:
	list<CObj*>*			m_pBullet = nullptr;
	POINT					m_tGun;
	POINT					m_Boss[10];
	DWORD					m_Time;

	DWORD				m_Cooltime;
	DWORD				m_Shottime;
	float				m_Distance;
	float				m_X;
	float				m_Y;
	float				m_Radian;
	float				m_Angle;

	CObj*				m_Taget;

};

