#pragma once
#include "Monster.h"
class CJustAttack :
	public CMonster
{
public:
	CJustAttack();
	virtual ~CJustAttack();


public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(OBJLIST* _objlist);
	virtual void		Render(HDC _hDC);
	virtual void		Release(void);

public:
	virtual void		Copy_Data(CObj* _target);

public:
	virtual void		Shoot();
	virtual void		MoveFoward();
	virtual void		NeedToCheckScreen();
	float				Calc_Distance(POINT dest, POINT src);
	void				Set_Angle_To_Target(POINT dest, POINT src);

public:
	const bool& 		Get_isNeed() const { return isNeed; };
	void				Set_isNeed(bool _bool) { isNeed = _bool;  };
public:
	void				Set_ScreenCheck(bool _bool);

protected:
	OBJLIST*			m_BulletList = nullptr;
	POINT				m_BarrelPos{};
	float				m_Angle = 0;
	bool				isNeed;

	CObj*				m_Target = nullptr;

};

