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
	virtual void		Late_Update(OBJLIST* _objlist);
	virtual void		Render(HDC _hDC);
	virtual void		Release(void);

public:
	void Set_Selection(GAME::GAMEID i);
public:
	GAME::GAMEID Get_Selection();

private:
	GAME::GAMEID m_Selection;
	TCHAR	szStageNum[10];
};

