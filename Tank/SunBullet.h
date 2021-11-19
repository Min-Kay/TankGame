#pragma once
#include "Bullet.h"
class CSunBullet :
	public CBullet
{
public:
	CSunBullet();
	virtual ~CSunBullet();


public:
	virtual void	Initialize(void) override;
	virtual int 	Update(void) override;
	virtual void 	Late_Update(OBJLIST* _objlist) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void			MoveToInitPos();
	void			Spin();
	void			Attack(); 
	void			Set_Parent (CObj* _parent) { m_parent = _parent; }
	void			Set_target (CObj* _target) { m_target = _target; }
	void			Set_Distance(int _distance) { m_distance = _distance; }
	void			Set_SpinCount(int _count) { m_spinCount = _count; }

public:
	const int&		Get_Distance()  const { return m_distance; }
	const CObj*	Get_Parent() { return m_parent;  }
public:
	void			Set_Angle(float _radian );
	bool			Calc_CurrDistance();

private:
	CObj*			m_parent = nullptr;
	CObj*			m_target = nullptr;
	bool			isInit;
	bool			isTurn;
	bool			isAttack;
	POINT			m_targetPoint{};
	int				m_distance;
	int				m_spinCount;
	float			m_Angle = 0.f ;
};

