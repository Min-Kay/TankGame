#pragma once

#include "Define.h"
#include "Obj.h"
#include <list>

using namespace std;

class St3_Skill
{
public:
	explicit St3_Skill();
	virtual ~St3_Skill();

public:
	virtual void Initialize(void) PURE;
	virtual void Attraction(OBJLIST* _objlist, CObj* _ownner)PURE;

protected:
	CObj*		 m_OWnner=nullptr;
	DWORD		 m_FinishTimer = 0;
	DWORD		 m_CoolTimer = 0;
	bool		 m_Vaild = false;
	int			 m_Limit = 0;

};

