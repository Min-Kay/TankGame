#include "stdafx.h"
#include "StageOne.h"
#include "GameHeader.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "AttackMonster.h"
#include "FollowMonster.h"
#include "Satellite.h"

#include "BossMonster.h"
#include "SkillPlayer.h"//����
#include <time.h>


void StageOne::Initialize()
	
{
	srand(unsigned(time(NULL)));
	Init_DefaultSetting(GAME::STAGE_ONE);
	Init_ObjList(); 
	Init_Patterns();
	iCount = 0;
	m_Spawn = false;
}

void StageOne::Update()
{
	Pattern(); // ���� ����

	Update_ObjList(); 


	Cheat_Mode();

	Update_Cursor();


}

void StageOne::Late_Update()
{
	LateUpdate_ObjList();
	
	//if (m_ObjList[OBJID::MONSTER].empty())
	//	Set_Clear(true);



	Check_Collision();

	//::Collision_Rect(m_ObjList[OBJID::MISSILE], m_ObjList[OBJID::FOLLOWMONSTER]);

	Check_GameState();

	Skill();

	Goto_Menu();
}

void StageOne::Render()
{
	// ��� - ������Ʈ - Ŀ�� ������ ����

	BackGround(); 

	Render_ObjList();

	Render_Cursor();
}

void StageOne::Release()
{
	Release_Game();
}

void StageOne::Init_Patterns()
{
	// ���� �ʱ�ȭ - Initialize �ÿ� �ۼ�
	// ���� ������ ���� �����ϴ�.
	// ���� �߰��� vector<CObj*>�� ����� ���͸� ���� �� �Ҵ� �� �� �ش� ������ m_Patterns�� push_back �Ͻø� �˴ϴ�.
	// ���� ���� �� m_Patterns�� 2���� �迭 ���·� ȣ���� ���͸� ��ȯ�Ͻø� �˴ϴ�.

	OBJVEC  patternA;

	
	patternA.reserve(6);
	patternA.push_back(CAbstractFactory<CAttackMonster>::Create(200, 100, 50, 50));
	patternA.push_back(CAbstractFactory<CAttackMonster>::Create(300, 200, 50, 50));
	patternA.push_back(CAbstractFactory<CAttackMonster>::Create(500, 300, 50, 50));
	patternA.push_back(CAbstractFactory<CAttackMonster>::Create(700, 100, 50, 50));
	patternA.push_back(CAbstractFactory<CAttackMonster>::Create(400, 200 ,50, 50));

	patternA.push_back(CAbstractFactory<CAttackMonster>::Create(250, 300, 50, 50));

	OBJVEC patternB;
	patternB.reserve(10);
	patternB.push_back(CAbstractFactory<CFollowMonster>::Create(100, 100, 10, 10));
	static_cast<CFollowMonster*>(patternB[0])->Set_Speed(1);
	patternB.push_back(CAbstractFactory<CFollowMonster>::Create(200, 100, 10, 10));
	static_cast<CFollowMonster*>(patternB[1])->Set_Speed(2);
	patternB.push_back(CAbstractFactory<CFollowMonster>::Create(300, 100, 10, 10));
	static_cast<CFollowMonster*>(patternB[2])->Set_Speed(3);
	patternB.push_back(CAbstractFactory<CFollowMonster>::Create(400, 100, 10, 10));
	static_cast<CFollowMonster*>(patternB[3])->Set_Speed(4);
	patternB.push_back(CAbstractFactory<CFollowMonster>::Create(500, 100, 10, 10));
	static_cast<CFollowMonster*>(patternB[4])->Set_Speed(5);
	patternB.push_back(CAbstractFactory<CFollowMonster>::Create(600, 100, 10, 10));
	static_cast<CFollowMonster*>(patternB[5])->Set_Speed(1);
	patternB.push_back(CAbstractFactory<CFollowMonster>::Create(rand() % 600+100, rand() % 300 + 100, 10, 10));
	patternB.push_back(CAbstractFactory<CFollowMonster>::Create(rand() % 600 + 100, rand() % 300 + 100, 10, 10));
	patternB.push_back(CAbstractFactory<CFollowMonster>::Create(rand() % 600 + 100, rand() % 300 + 100, 10, 10));
	//===========================================================

	//static_cast<CFollowMonster*>(patternB[0])->Set_Taget(m_ObjList[OBJID::PLAYER].front());
	//static_cast<CFollowMonster*>(patternB[0])->Copy_Data(m_ObjList[OBJID::PLAYER].front());

	OBJVEC patternC;
	patternC.reserve(1);
	patternC.push_back(CAbstractFactory<CBossMonster>::Create(100, 100, 30, 30));

	

	m_Patterns.push_back(patternA);
	m_Patterns.push_back(patternB);
	m_Patterns.push_back(patternC);
}

void StageOne::Pattern()
{
	// ���� ����
	// ���� ������ �����Ӱ� �����ϵ� 
	// ��� ������ �����ߴٸ� Set_Clear()�� ���� isClear�� true�� ������ �¸��� �����Ͻø� �˴ϴ�.
	// �÷��̾� �й�� Check_GameState() ���� �ڵ� ó�� �մϴ�.
	// �㳪 �ΰ����� �й� ���(��� ���� ��)�� �����Ͻ÷��� Set_Result() �� ���� Enum���� NONE�� ������ �ٸ� ������ �����Ͻø� 
	// Goto_Menu()�� m_Result�� ���� ���� ������ ����ǵ��� ó���մϴ�.
/*
	if (m_Spawn)
		return;*/

	DWORD tickCount = GetTickCount();
	switch (selected_Pattern)
	{
	case 0:
		if (spawn_Timer + 3000 < tickCount)
		{
			Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][0])));
			Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][1])));
			Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][2])));
			Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][3])));
			Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][1])));
			Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][4])));
			Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][5])));
			spawn_Timer = GetTickCount();
			selected_Pattern = 3;
		}
		break;
	case 1:
		if (spawn_Timer + 3000 < tickCount)
		{
			Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][0])));
			Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][1])));
			Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][2])));
			Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][3])));
			Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][4])));
			Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][5])));
			spawn_Timer = GetTickCount();
			selected_Pattern = 3;
		}
		break;
	case 2:
		if (spawn_Timer + 3000 < tickCount)
		{
		
			Add_MonsterList(CAbstractFactory<CBossMonster>::Create(static_cast<CBossMonster*>(m_Patterns[2][0])));
			spawn_Timer = GetTickCount();
			selected_Pattern = 3;
		}
		////////////////////////////////////////
		if (m_Timer + 300 < GetTickCount()) {
		Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][1])));
			Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][4])));
				Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][0])));
				Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][1])));
				Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][2])));
				Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][6])));
				Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][7])));
				Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][8])));
			m_Timer = GetTickCount();
			selected_Pattern = 3;
		}
		if (m_Timer + 300 < GetTickCount()) {
			Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][1])));
			Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][4])));
			Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][0])));
			Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][1])));
			Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][2])));
			Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][6])));
			Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][7])));
			Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][8])));

			m_Timer = GetTickCount();
			selected_Pattern = 3;
		}
		////////////////////////////////
		break;
	case 3:
		if (m_ObjList[OBJID::MONSTER].empty())
		{
			play_Count++;

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
	

	/*if (m_Timer+1000 <= GetTickCount()) {
		iCount++;


		m_Timer = GetTickCount();
	}


	
	switch (iCount) {

	case 0:
		Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][0])));
		Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][1])));
		Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][2])));
		break;

	case 1:
		Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][0])));
		Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][1])));
		Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][2])));
		Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][3])));
		Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][4])));
		Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][5])));
		break;

	case 2:
		Add_MonsterList(CAbstractFactory<CBossMonster>::Create(static_cast<CBossMonster*>(m_Patterns[2][0])));
		break;

	}
	if (iCount ==0) {
		
		
		}

		else if ( iCount == 1) {
			
		
			
		
	}
		else 	if ( iCount ==2) {
			
			
		}*/
	
	
	
	//Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][0])));
	/*Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][1])));
	Add_MonsterList(CAbstractFactory<CAttackMonster>::Create(static_cast<CAttackMonster*>(m_Patterns[0][2])));
	Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][0])));
	Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][1])));
	Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][2])));
	Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][3])));
	Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][4])));
	Add_MonsterList(CAbstractFactory<CFollowMonster>::Create(static_cast<CFollowMonster*>(m_Patterns[1][5])));
	Add_MonsterList(CAbstractFactory<CBossMonster>::Create(static_cast<CBossMonster*>(m_Patterns[2][0])));*/

	m_Spawn = true;
	
	

}

void StageOne::Init_ObjList()
{
	// ������Ʈ ����Ʈ �ʱ�ȭ ���� - Initialize�� �ۼ�
	// �����Ӱ� m_ObjList�� �߰��ϰ��� �ϴ� CObj �߰��Ͻø� �˴ϴ�.
	///////////////////////
//	m_ObjList[OBJID::PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	m_ObjList[OBJID::PLAYER].push_back(CAbstractFactory<CSkillPlayer>::Create());
	dynamic_cast<CSkillPlayer*>(m_ObjList[OBJID::PLAYER].front())->Set_Bullet(&m_ObjList[OBJID::MISSILE]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJID::PLAYER].front())->Set_Satellite(&m_ObjList[OBJID::SATELLITE]);
/////////////////////////////


}

void StageOne::Skill()
{
	if ( (m_Timer + 3000 <= GetTickCount()))
	{
		auto& player = m_ObjList[OBJID::PLAYER].front();
		CObj* temp = CAbstractFactory<CSatellite>::Create();
		static_cast<CSatellite*>(temp)->Set_Ownner(player); 
		static_cast<CPlayer*>(player)->Add_Satellite(temp);
		m_Timer = GetTickCount();
	}


}

int StageOne::Set_Cnt(int _Cnt)
{
	_Cnt = 0;
	_Cnt++;
	iCount += _Cnt;

	return iCount;

}



