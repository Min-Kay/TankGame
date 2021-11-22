#pragma once
#include"Bullet.h"

class St3_ChaseBullet : public CBullet
{
public:
	St3_ChaseBullet();
	~St3_ChaseBullet();

public:
	virtual int 	Update(void) override;
	virtual void	Initialize(void)override;
	virtual void	Render(HDC hDC) override;
	virtual void 	Late_Update(OBJLIST* _objlist) override;
	virtual void	Release(void) override;

private:
	void	Check_Target(OBJLIST* _objlist);
	float	Check_Distance(CObj* _src);
	void	Check_Out();
	bool	Delay();
	void	Render_Body(HDC _hdc);
private:
	bool		m_TaretingVaild=false;
	POINT		m_Target = {};
	CObj*		m_TargetT = nullptr;
	bool		m_Delay;
	short		m_DelayTime=0;
	short		m_BombTime =0;
	bool		m_Bomb = 0;
	short		m_EngineTime=0;
	short		m_EngineBool = 0;
};


