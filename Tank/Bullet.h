#pragma once
#include "Obj.h"
class CBullet : public CObj
{
public:
	explicit CBullet();
	virtual ~CBullet();

public:
	virtual void	Initialize(void) override;
	virtual int 	Update(void) override;
	virtual void 	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:


private:
	void			Update_Locate(int _speed);

};