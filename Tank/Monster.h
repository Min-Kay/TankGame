#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();


public:
	virtual void		Initialize(void);
	virtual int			Update(void) ;
	virtual void		Late_Update(void) ;
	virtual void		Render(HDC _hDC) ;
	virtual void		Release(void) ;
};

