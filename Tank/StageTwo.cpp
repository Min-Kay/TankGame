#include "stdafx.h"
#include "StageTwo.h"
#include "Player.h"
#include "Monster.h"
#include "St2_Mon_Lv1.h"
#include "St2_Mon_Lv2.h"
#include "AbstractFactory.h"
#include "Manager.h"


StageTwo::StageTwo()
{
}


StageTwo::~StageTwo()
{
}

void StageTwo::Initialize()
{
	Init_DefaultSetting(GAME::STAGE_TWO);
	Init_ObjList();
	Init_Cursor();
	Init_Patterns();
}

void StageTwo::Update()
{
	Pattern();

	Update_ObjList();

	Cheat_Mode();

	Update_Cursor();
}

void StageTwo::Late_Update()
{
	LateUpdate_ObjList();

	Check_Collision();

	Check_GameState();

	Goto_Menu();
}

void StageTwo::Render()
{
	BackGround();

	Render_ObjList();

	Render_Cursor();
}

void StageTwo::Release()
{
	Release_Game();
}

void StageTwo::Init_ObjList()
{
	m_ObjList[OBJID::PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	static_cast<CPlayer*>(m_ObjList[OBJID::PLAYER].front())->Set_Bullet(&m_ObjList[OBJID::MISSILE]);
	static_cast<CPlayer*>(m_ObjList[OBJID::PLAYER].front())->Set_Satellite(&m_ObjList[OBJID::SATELLITE]);
}

void StageTwo::Init_Patterns()
{

	OBJVEC patternA;
	OBJVEC patternB;

	patternA.reserve(5);
	patternA.push_back(CAbstractFactory<St2_Mon_Lv1>::Create(100, 50, 30, 30, 270 * PI / 180.f));
	static_cast<St2_Mon_Lv1*>(patternA[0])->Set_isNeed(true);

	patternA.push_back(CAbstractFactory<St2_Mon_Lv1>::Create(250, 50, 30, 30, 270 * PI / 180.f));
	static_cast<St2_Mon_Lv1*>(patternA[1])->Set_isNeed(true);

	patternA.push_back(CAbstractFactory<St2_Mon_Lv1>::Create(400, 50, 30, 30, 270 * PI / 180.f));
	static_cast<St2_Mon_Lv1*>(patternA[2])->Set_isNeed(true);

	patternA.push_back(CAbstractFactory<St2_Mon_Lv1>::Create(550, 50, 30, 30, 270 * PI / 180.f));
	static_cast<St2_Mon_Lv1*>(patternA[3])->Set_isNeed(true);

	patternA.push_back(CAbstractFactory<St2_Mon_Lv1>::Create(700, 50, 30, 30, 270 * PI / 180.f));
	static_cast<St2_Mon_Lv1*>(patternA[4])->Set_isNeed(true);

	patternB.reserve(3);
	
	patternB.push_back(CAbstractFactory<St2_Mon_Lv2>::Create(700, 100, 30, 30, 180 * PI / 180.f));
	static_cast<St2_Mon_Lv2*>(patternB[0])->Set_isNeed(true);
	patternB.push_back(CAbstractFactory<St2_Mon_Lv2>::Create(700, 200, 30, 30, 180 * PI / 180.f));
	static_cast<St2_Mon_Lv2*>(patternB[1])->Set_isNeed(true);
	patternB.push_back(CAbstractFactory<St2_Mon_Lv2>::Create(700, 300, 30, 30, 180 * PI / 180.f));
	static_cast<St2_Mon_Lv2*>(patternB[2])->Set_isNeed(true);
	m_Patterns.push_back(patternA);
	m_Patterns.push_back(patternB);
}

void StageTwo::Pattern()
{
	DWORD tickCount = GetTickCount();
	switch (selected_Pattern)
	{
	case 0:
		if (spawn_Timer + 3000 < tickCount)
		{
			Add_MonsterList(CAbstractFactory<St2_Mon_Lv1>::Create(static_cast<St2_Mon_Lv1*>(m_Patterns[0][0])));
			Add_MonsterList(CAbstractFactory<St2_Mon_Lv1>::Create(static_cast<St2_Mon_Lv1*>(m_Patterns[0][1])));
			Add_MonsterList(CAbstractFactory<St2_Mon_Lv1>::Create(static_cast<St2_Mon_Lv1*>(m_Patterns[0][2])));
			Add_MonsterList(CAbstractFactory<St2_Mon_Lv1>::Create(static_cast<St2_Mon_Lv1*>(m_Patterns[0][3])));
			Add_MonsterList(CAbstractFactory<St2_Mon_Lv1>::Create(static_cast<St2_Mon_Lv1*>(m_Patterns[0][4])));
			spawn_Timer = GetTickCount();
			selected_Pattern = 3;
		}
		break;
	case 1:
		if (spawn_Timer + 3000 < tickCount)
		{
			Add_MonsterList(CAbstractFactory<St2_Mon_Lv1>::Create(static_cast<St2_Mon_Lv1*>(m_Patterns[1][0])));
			Add_MonsterList(CAbstractFactory<St2_Mon_Lv1>::Create(static_cast<St2_Mon_Lv1*>(m_Patterns[1][1])));
			Add_MonsterList(CAbstractFactory<St2_Mon_Lv1>::Create(static_cast<St2_Mon_Lv1*>(m_Patterns[1][2])));
			spawn_Timer = GetTickCount();
			selected_Pattern = 3;
		}
		break;
	case 2:
		if (spawn_Timer + 3000 < tickCount)
		{
			spawn_Timer = GetTickCount();
			selected_Pattern = 3;
		}
		break;
	case 3:
		if (m_ObjList[OBJID::MONSTER].empty())
		{
			++play_Count;

			switch (play_Count)
			{
			case 1:
				selected_Pattern = 0;
				break;
			case 2:
				selected_Pattern = 1;
				break;
			case 3:
				selected_Pattern = 2;
				break;
			case 4:
				Set_Clear(true);
				break;
			}
			break;
		}
	}
}

