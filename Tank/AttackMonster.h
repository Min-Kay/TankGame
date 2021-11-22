#pragma once
#include "Monster.h"
class CAttackMonster :
	public CMonster
{
public:
	CAttackMonster();
	virtual ~CAttackMonster();

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(OBJLIST* _objlist);
	virtual void		Render(HDC _hDC);
	virtual void		Release(void);



private:
	DWORD				m_Cooltime;
	DWORD				m_Shottime;
	POINT				m_Point;
	float				m_Distance;

	float				m_Radian;

	
	CObj*				m_Taget;



};
