#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	explicit CMonster();
	virtual ~CMonster();


public:
	virtual void		Initialize(void);
	virtual int			Update(void) ;
	virtual void		Late_Update(OBJLIST* _objlist) ;
	virtual void		Render(HDC _hDC) ;
	virtual void		Release(void) ;


protected:
	DWORD				m_Cooltime; 

};

