#include "stdafx.h"
#include "St3_Patern01.h"
#include "AbstractFactory.h"

St3_Patern01::St3_Patern01()
{
	m_CreateTime = GetTickCount();
}

St3_Patern01::~St3_Patern01()
{
}

void St3_Patern01::Initialize(void)
{
	for (auto i : m_MonVaild)
		i = true;
}

int St3_Patern01::Add_Monster(OBJLIST* _objlist)
{
	if (m_Vaild == true)
	{
		for (int i = 0; i < 20; ++i)
		{
		}
	}

	if (m_CreateTime + 5000 < GetTickCount())
	{
		for (auto i : m_MonVaild)
			i = true;
	}

	return 0;
}

void St3_Patern01::Release(void)
{
}


