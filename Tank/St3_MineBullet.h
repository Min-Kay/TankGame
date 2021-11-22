#pragma once
#include "Obj.h"
class St3_MineBullet : public CObj
{
public:
	St3_MineBullet();
	~St3_MineBullet();

public:
	virtual int 	Update(void) override;
	virtual void	Initialize(void)override;
	virtual void	Render(HDC hDC) override;
	virtual void 	Late_Update(OBJLIST* _objlist) override;
	virtual void	Release(void) override;
private:
	bool	Delay();
	void	Render_Body(HDC _hdc);
private:
	RECT		m_Rect1;
	bool		m_Delay=0;
	short		m_DelayTime = 0;
	short		m_BombTime = 0;
	bool		m_Bomb = 0;
	bool		m_Once=true;
	int			m_Maxtime=0;
};

