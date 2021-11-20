#pragma once
#include "Bullet.h"
class CBall :
	public CBullet
{

public:
	virtual void	Initialize(void) override;
	virtual int 	Update(void) override;
	virtual void 	Late_Update(OBJLIST* _objlist) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void			Set_Angle();

private:
	float			m_Angle;

};

