#pragma once
#include"Def_St3.h"
#include "Define.h"
#include "Obj.h"
#include "St3_Patern.h"
#include <list>
#include <wtypes.h>

class St3_Patern01 : public St3_CPatern
{
public:
	explicit St3_Patern01();
	virtual ~St3_Patern01();

public:
	virtual void		Initialize(void);
	virtual int			Add_Monster(OBJLIST* _objlist) override;
	virtual void		Release(void) override;

};


