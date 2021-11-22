#pragma once
#include "Bullet.h"
class CSrecwBullet :
	public CObj
{
public:
	CSrecwBullet();
	~CSrecwBullet();
public:
	virtual void	Initialize(void) override;
	virtual int 	Update(void) override;
	virtual void 	Late_Update(OBJLIST* _objlist) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

private:
	void			Update_Locate(int _speed);


public:
	void				Set_Ownner(CObj* _ownner) { m_Ownner = _ownner; };
	void			Set_Taget(CObj* _pTaget) { m_Taget = _pTaget; }
private:
	POINTFLOAT		m_CenterPos;
	float			m_RevolutionAngle;
	float			m_CenterSpeed;
	float			m_Distance;
	bool			m_Start;
	OBJLIST*			m_Bullet = nullptr;
	CObj*	m_Ownner;
	OBJLIST m_ObjList[OBJID::END];
	CObj*			m_Taget = nullptr;
	DWORD		m_Timer;
};

