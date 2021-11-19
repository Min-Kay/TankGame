#pragma once

#include "Monster.h"
#include "Enum_St3.h"

class St3_MonCommon00 : public CObj
{
public:
	explicit St3_MonCommon00();
	virtual ~St3_MonCommon00();

public:
	virtual void					Initialize(void);
	virtual int						Update(void);
	virtual void					Late_Update(OBJLIST* _objlist);
	virtual void					Render(HDC _hDC);
	virtual void					Release(void);

private:
	virtual void					Rebound(); // 

private:
	MOVEMENT::MOVEMENT_STATUS		Check_Move(CObj* _src);
	virtual void					Move_Opposite(int _speed);
	virtual void					Move_To_Point(POINT _dst);


private:
	list<CObj*>*						m_Bullet;
	MOVEMENT::MOVEMENT_STATUS			m_Move;
	float								m_Range;
	DWORD								m_Cooltime;
};

