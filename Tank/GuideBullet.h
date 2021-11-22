#pragma once
#include "Obj.h"
class CGuideBullet :
	public CObj
{
public:
	CGuideBullet();
	~CGuideBullet();

public:
	virtual void				Initialize(void) override;
	virtual int					Update(void) override;
	virtual void				Late_Update(OBJLIST* _objlist) override;
	virtual void				Render(HDC hDC) override;
	virtual void			    Release(void) override;
			void				Set_Taget(CObj* _pTaget) { m_Taget = _pTaget; }
			void		      	Set_Ownner(CObj* _ownner);
private:
	DWORD				m_Cooltime;
	POINT			m_Objpoint[OBJECT::POINT_TYPE_END];
	CObj*	m_Taget = nullptr;
	float			m_Distance;
	CObj*	m_Ownner = nullptr;
};

