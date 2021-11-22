#pragma once
#include "St3_Skill.h"

class St3_Skill01 : public St3_Skill
{
public:
	explicit St3_Skill01();
	virtual ~St3_Skill01();

public:
	virtual void Initialize(void) override;
	virtual void Attraction(OBJLIST* _bullet, CObj* _ownner)override;
	 void		 Attraction_Chase(OBJLIST* _bullet, CObj* _ownner);

private:
	int m_Count = 0;
};

