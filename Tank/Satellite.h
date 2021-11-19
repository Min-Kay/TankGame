#pragma once
#include "Obj.h"

class CSatellite : public CObj
{
public:
	explicit CSatellite();
	virtual ~CSatellite();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void)override;
	virtual void		Late_Update(OBJLIST* _objlist) override;
	virtual void		Render(HDC _hDC)override;
	virtual void		Release(void)override;

public:
	void				Set_Ownner(CObj* _ownner);

protected:
	CObj*	m_Ownner;
};

