#include "stdafx.h"
#include "StageFour.h"
#include "Player.h"
#include "Monster.h"
#include "JustAttack.h"
#include "Sunflower.h"
#include "Dispenser.h"
#include "AbstractFactory.h"
#include "Manager.h"
#include "Wall.h"
#include "Pet.h"


StageFour::StageFour()
{
}


StageFour::~StageFour()
{
}

void StageFour::Initialize()
{
	Init_DefaultSetting(GAME::STAGE_THREE);
	Init_ObjList(); 
	Init_Cursor();
	Init_Patterns(); 
}

void StageFour::Update()
{
	Pattern();

	Update_ObjList();

	Cheat_Mode();

	Update_Cursor();
}

void StageFour::Late_Update()
{
	LateUpdate_ObjList();

	CCollisionMgr::Collision_Push(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::OBSTACLE]);
	CCollisionMgr::Collision_Bounce(m_ObjList[OBJID::MISSILE],m_ObjList[OBJID::OBSTACLE]);

	Check_Collision();

	Check_GameState();

	Goto_Menu(); 
}

void StageFour::Render()
{
	BackGround(); 

	Render_ObjList();

	Render_Cursor(); 
}

void StageFour::Release()
{
	Release_Game();
}

void StageFour::Init_ObjList()
{
	m_ObjList[OBJID::PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	static_cast<CPlayer*>(m_ObjList[OBJID::PLAYER].front())->Set_Bullet(&m_ObjList[OBJID::MISSILE]);
	static_cast<CPlayer*>(m_ObjList[OBJID::PLAYER].front())->Set_Satellite(&m_ObjList[OBJID::SATELLITE]);
	m_ObjList[OBJID::SATELLITE].push_back(CAbstractFactory<CPet>::Create());
}

void StageFour::Init_Patterns()
{

	OBJVEC patternA;
	OBJVEC patternB;
	OBJVEC patternC;

	patternA.reserve(7);
	patternA.push_back(CAbstractFactory<CJustAttack>::Create(100, 50, 30, 30, 270 * PI / 180.f));
	static_cast<CJustAttack*>(patternA[0])->Set_isNeed(true);

	patternA.push_back(CAbstractFactory<CJustAttack>::Create(200, 50, 30, 30, 270 * PI / 180.f));
	static_cast<CJustAttack*>(patternA[1])->Set_isNeed(true);	

	patternA.push_back(CAbstractFactory<CJustAttack>::Create(300, 50, 30, 30, 270 * PI / 180.f));
	static_cast<CJustAttack*>(patternA[2])->Set_isNeed(true);

	patternA.push_back(CAbstractFactory<CJustAttack>::Create(400, 50, 30, 30, 270 * PI / 180.f));
	static_cast<CJustAttack*>(patternA[3])->Set_isNeed(true);

	patternA.push_back(CAbstractFactory<CJustAttack>::Create(500, 50, 30, 30, 270 * PI / 180.f));
	static_cast<CJustAttack*>(patternA[4])->Set_isNeed(true);

	patternA.push_back(CAbstractFactory<CJustAttack>::Create(600, 50, 30, 30, 270 * PI / 180.f));
	static_cast<CJustAttack*>(patternA[5])->Set_isNeed(true);

	patternA.push_back(CAbstractFactory<CJustAttack>::Create(700, 50, 30, 30, 270 * PI / 180.f));
	static_cast<CJustAttack*>(patternA[6])->Set_isNeed(true);

	patternB.reserve(3);
	patternB.push_back(CAbstractFactory<CSunflower>::Create(200, 55, 50, 50, 270 * PI / 180.f));
	patternB[0]->Set_Speed(1.0f);

	patternB.push_back(CAbstractFactory<CSunflower>::Create(400, 55, 50, 50, 270 * PI / 180.f));
	patternB[1]->Set_Speed(1.0f);

	patternB.push_back(CAbstractFactory<CSunflower>::Create(600, 55, 50, 50, 270 * PI / 180.f));
	patternB[2]->Set_Speed(1.0f);

	patternC.reserve(1);
	patternC.push_back(CAbstractFactory<CDispenser>::Create(400, 100, 10, 10));

	m_Patterns.push_back(patternA);
	m_Patterns.push_back(patternB);
	m_Patterns.push_back(patternC);
}

void StageFour::Pattern()
{
	DWORD tickCount = GetTickCount();
	switch (selected_Pattern)
	{
	case 1:
		if (spawn_Timer + 3000 < tickCount)
		{
			Add_MonsterList(CAbstractFactory<CJustAttack>::Create(static_cast<CJustAttack*>(m_Patterns[0][0])));
			Add_MonsterList(CAbstractFactory<CJustAttack>::Create(static_cast<CJustAttack*>(m_Patterns[0][1])));
			Add_MonsterList(CAbstractFactory<CJustAttack>::Create(static_cast<CJustAttack*>(m_Patterns[0][2])));
			Add_MonsterList(CAbstractFactory<CJustAttack>::Create(static_cast<CJustAttack*>(m_Patterns[0][3])));
			Add_MonsterList(CAbstractFactory<CJustAttack>::Create(static_cast<CJustAttack*>(m_Patterns[0][4])));
			Add_MonsterList(CAbstractFactory<CJustAttack>::Create(static_cast<CJustAttack*>(m_Patterns[0][5])));
			Add_MonsterList(CAbstractFactory<CJustAttack>::Create(static_cast<CJustAttack*>(m_Patterns[0][6])));
			spawn_Timer = GetTickCount();
			selected_Pattern = 0;
		}
		break;
	case 2:
		if (spawn_Timer + 3000 < tickCount)
		{
			Add_MonsterList(CAbstractFactory<CSunflower>::Create(static_cast<CSunflower*>(m_Patterns[1][0])));
			Add_MonsterList(CAbstractFactory<CSunflower>::Create(static_cast<CSunflower*>(m_Patterns[1][1])));
			Add_MonsterList(CAbstractFactory<CSunflower>::Create(static_cast<CSunflower*>(m_Patterns[1][2])));
			spawn_Timer = GetTickCount();
			selected_Pattern = 0;
		}
		break;
	case 3:
		if (spawn_Timer + 3000 < tickCount)
		{
			Add_MonsterList(CAbstractFactory<CDispenser>::Create(static_cast<CDispenser*>(m_Patterns[2][0])));
			spawn_Timer = GetTickCount();
			selected_Pattern = 0;
		}
		break;
	case 0:
		if (m_ObjList[OBJID::MONSTER].empty())
		{
			++play_Count;

			switch (play_Count)
			{
			case 1:
				selected_Pattern = 2;
				break;
			case 2:
				selected_Pattern = 3;
				break;
			case 3:
				selected_Pattern = 0;
				break;
			case 4:
				Set_Clear(true);
				break;
			}
			break;
		}
	}
}
