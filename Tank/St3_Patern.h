#pragma once
#include "Define.h"
#include "Obj.h"
#include <list>

using namespace std;

class St3_CPatern
{
public:
	explicit St3_CPatern();
	virtual ~St3_CPatern();
	//기본 함수
public:
	virtual void		Initialize(void) PURE;
	virtual int			Add_Monster(OBJLIST* _objlist) PURE;
	virtual void		Release(void) PURE;

public:
	const DWORD	Get_CreateTime() const { return m_CreateTime; }
	void		Set_Vaild(bool _vaild) { m_Vaild = _vaild; }
	const bool	Get_Vaild() { return m_Vaild; }
	void		Set_Reset() { Initialize(); }


protected:
	bool	m_Vaild = true;
	bool	m_MonVaild[20];
	DWORD	m_CreateTime = 0;
};

