#pragma once
#include "Monster.h"

class CFollowMonster :
	public  CMonster
{
public:
	CFollowMonster();
	virtual ~CFollowMonster();

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(OBJLIST* _objlist);
	virtual void		Render(HDC _hDC);
	virtual void		Release(void);
public:
	void			fllow_Player(OBJLIST* _objlist);
	void			Set_Taget(CObj* _pTaget) { m_Taget = _pTaget; }
	bool			Confined_Monster();
public:
	virtual void		Copy_Data(CObj* _target);
	//void			Set_Bullet(list<CObj*>*  _pBullet);
private:
	list<CObj*>*		m_objlist[OBJID::END];
	float				m_Distance;
	float				m_X;
	float				m_Y;
	float				m_Radian;
	float				m_Angle;
	OBJLIST*			m_BulletList = nullptr;
	CObj*				m_Taget  = nullptr;


};
