#pragma once
#include "Obj.h"
class CClick :
	public CObj
{
public:
	CClick();
	virtual ~CClick();

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(void);
	virtual void		Render(HDC _hDC);
	virtual void		Release(void);

public:
	void Set_Selection(int i); 
public:
	int Get_Selection();

private:
	int m_Selection;
	TCHAR	szStageNum[10];
};

