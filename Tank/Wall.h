#pragma once
#include "Bullet.h"
class CWall :
	public CObj
{

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(OBJLIST* _objlist);
	virtual void		Render(HDC _hDC);
	virtual void		Release(void);

public:
	void				MoveDistance();
	bool				Check_Distance();
	void				Set_Angle(); 

public:
	void				Set_Collision();
	void				Set_Distance(float _dis) { m_Distance = _dis; };
	void				Set_InitPos();
	void				Set_Parent(CObj* _parent) { m_Parent = _parent; };

public:
	CObj*				Get_Parent() { return m_Parent; }

private:
	int					m_Distance;
	POINT				m_InitPos; 
	float				m_Angle;
	HBRUSH				brush = NULL;

	CObj*				m_Parent = nullptr; 
	
	int					m_LifeTime;
	DWORD				m_Tick;
};

