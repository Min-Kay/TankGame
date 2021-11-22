#include "stdafx.h"
#include "StageThree.h"
#include "GameHeader.h"
#include "Obj.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "Monster.h"
#include "Manager.h"
#include "St3_Player.h"
#include "St3_Patern01.h"
#include "St3_CollisionMgr.h"
#include "St3_Larva.h"
#include "St3_Chaser.h"
#include "St3_BossMonster.h"
#include "St3_Drone.h"
#include "St3_MineBullet.h"

StageThree::StageThree()
{
}

StageThree::~StageThree()
{
}

void StageThree::Initialize()
{
	Init_DefaultSetting(GAME::STAGE_FOUR); 
	Init_ObjList();
	Init_Patterns();
	m_FPS = 0;
	m_Mon0_Vaild = true;
	m_PaternVec.reserve(10);
	m_Result = GAMERESULT::NONE;
	m_Mon1Cooltime = St3_LAVA_MAX;
	m_Mon0_Kill_Count = 0;
}

void StageThree::Update()
{
	Kill_ObjList();
	--m_BossRes;
	--m_DroneCool;

	if (m_FPS <= 0)
		m_FPS = 65;
	else
		--m_FPS;

	Cheat_Mode();
	Update_Cursor();


	Pattern();				// 패턴 진행

	Update_ObjList_ALL();	// 객체들 업데이트 진행

							//UPDATE_DEADMOTION
	for (auto& i : m_DeathMotionList)
		i->Update();

}

void StageThree::Late_Update()
{
	LateUpdate_ObjList(); // 객체들 늦은 업데이트 진행
	--m_BossRes;


	St3_CollisionMgr::Check_Blocking(m_ObjList[OBJID::PLAYER].front(), m_ObjList[OBJID::MONSTER]);
	St3_CollisionMgr::Check_Blocking_Push(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER]);
	//CCollisionMgr::Collision_Rect(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MISSILE]);
	St3_CollisionMgr::Collision_Rect(m_ObjList[OBJID::SATELLITE], m_ObjList[OBJID::MONSTER]);
	St3_CollisionMgr::Collision_Rect(m_ObjList[OBJID::SATELLITE], m_ObjList[OBJID::MISSILE]);
	St3_CollisionMgr::Collision_Rect(m_ObjList[OBJID::MONSTER], m_ObjList[OBJID::MISSILE]);
	St3_CollisionMgr::Collision_Rect(m_ObjList[OBJID::MONSTER], m_ObjList[OBJID::PLAYER]);
	St3_CollisionMgr::Check_Blocking_Push(m_ObjList[OBJID::MONSTER], m_ObjList[OBJID::MONSTER]);
	
	Check_GameState();
	Goto_Menu();
	
	/*St3_CollisionMgr::Check_Blocking_Push(m_ObjList[OBJID::MONSTER], m_ObjList[OBJID::MISSILE]);*/

	//St3_CollisionMgr::Check_Blocking_Push(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MISSILE]);
	//CCollisionMgr::Collision_Rect(m_ObjList[OBJID::MISSILE], m_ObjList[OBJID::MONSTER]);

	Kill_DeadMoition();
}

void StageThree::Render()
{
	if (m_Result != GAMERESULT::NONE)
		return;

	// 배경 - 오브젝트 - 커서 순으로 렌더

	BackGround();


	WCHAR Buff[32] = L"";
	swprintf_s(Buff, L" 개체수 : %d ", m_ObjList[OBJID::MONSTER].size());
	TextOut(m_DC,50,50,Buff,lstrlenW(Buff));

	swprintf_s(Buff, L" 죽인수 : %d ", m_Mon0_Kill_Count);
	TextOut(m_DC, 200, 50, Buff, lstrlenW(Buff));

	//Render_DEADMOTION


	Render_ObjList(); // 객체들 랜더링 진행

	for (auto iter = m_DeathMotionList.begin(); iter != m_DeathMotionList.end();)
	{
		(*iter)->Render(m_DC);
		++iter;
	}

	Render_Cursor();
}



void StageThree::Release()
{
	for (auto i : m_PaternVec)
		SAFE_DELETE(i);

	for (auto i : m_DeathMotionList)
		SAFE_DELETE(i);

	Release_Game();
}

//Initalise 요약
void StageThree::Init_ObjList()
{
	m_ObjList[OBJID::PLAYER].push_back(CAbstractFactory<St3_Player>::Create());
	static_cast<CPlayer*>(m_ObjList[OBJID::PLAYER].front())->Set_Bullet(&m_ObjList[OBJID::MISSILE]);
}

//패턴함수

void StageThree::Init_Patterns()
{
	m_PaternVec.push_back(new St3_Patern01);

}

void StageThree::Pattern()
{
	if (m_BossBool)
	{
		return;
	}

	int iSelect = rand() % 2;

	if (m_Mon0_Kill_Count >= 30)
	{
		CObj* temp = CAbstractFactory<St3_BossMonster>::Create();
		static_cast<St3_BossMonster*>(temp)->Set_Bullet(&m_ObjList[OBJID::MISSILE]);
		static_cast<St3_BossMonster*>(temp)->Set_Target(m_ObjList[OBJID::PLAYER].front());
		m_ObjList[OBJID::MONSTER].push_back(temp);
		m_BossBool = true;
	}

	switch (iSelect)
	{
	case 0:
		if (m_FPS <= 0 && m_ObjList[OBJID::MONSTER].size() < St3_LAVA_MAX)
		{
			CObj * temp = CAbstractFactory<St3_Larva>::Create();
			static_cast<St3_Larva*>(temp)->Set_Bullet(&m_ObjList[OBJID::MISSILE]);

			int iSelect = rand() % 4;
			switch (iSelect)
			{
			case 1:
				temp->Move_Pos(200, 200);
				break;
			case 2:
				temp->Move_Pos(600, 200);
				break;
			case 3:
				temp->Move_Pos(200, 400);
				break;
			case 4:
				temp->Move_Pos(600, 200);
				break;
			default:
				break;
			}
			m_ObjList[OBJID::MONSTER].push_back(temp);
			++m_Mon0_Kill_Count;
		}
		break;
	case 1:
		if (m_FPS <= 0 && m_ObjList[OBJID::MONSTER].size() < St3_LAVA_MAX)
		{
			int spawn = rand()%4;
			CObj* temp = CAbstractFactory<St3_Chaser>::Create();
			static_cast<St3_Chaser*>(temp)->Set_Respawn(spawn);
			static_cast<St3_Chaser*>(temp)->Set_Bullet(&m_ObjList[OBJID::MISSILE]);
			static_cast<St3_Chaser*>(temp)->Set_Target(m_ObjList[OBJID::PLAYER].front());
			m_ObjList[OBJID::MONSTER].push_back(temp);
			++m_Mon0_Kill_Count;
		}
		break;
	case 2:
		if (m_DroneCool <= 0 && m_ObjList[OBJID::MONSTER].size() < St3_LAVA_MAX)
		{
			CObj* temp = CAbstractFactory<St3_Drone>::Create();
			static_cast<St3_Drone*>(temp)->Set_Bullet(&m_ObjList[OBJID::MISSILE]);
			m_ObjList[OBJID::MONSTER].push_back(temp);
			m_DroneCool = 360;
			++m_Mon0_Kill_Count;
		}

		break;

		break;
	default:
		break;
	}

	//Larva
	//if ( m_FPS <=0 && m_ObjList[OBJID::MONSTER].size() < St3_LAVA_MAX)
	//{


	//	CObj * temp = CAbstractFactory<St3_Larva>::Create();
	//	static_cast<St3_Larva*>(temp)->Set_Bullet(&m_ObjList[OBJID::MISSILE]);

	//	int iSelect = rand()%4;
	//	switch (iSelect)
	//	{
	//	case 1:		
	//		temp->Move_Pos(200, 200);
	//		break;
	//	case 2:
	//		temp->Move_Pos(600, 200);
	//		break;
	//	case 3:
	//		temp->Move_Pos(200, 400);
	//		break;
	//	case 4:
	//		temp->Move_Pos(600, 200);
	//		break;
	//	default:
	//		break;
	//	}

	//	m_ObjList[OBJID::MONSTER].push_back(temp);
	//	++m_Mon1Cooltime;
	//}

	//Chaser
	if (GetAsyncKeyState(VK_NUMPAD0) & 0x8000 && m_FPS <= 0) //실험용
	{

		CObj* temp = CAbstractFactory<St3_Chaser>::Create();
		static_cast<St3_Chaser*>(temp)->Set_Respawn(1);
		static_cast<St3_Chaser*>(temp)->Set_Bullet(&m_ObjList[OBJID::MISSILE]);
		static_cast<St3_Chaser*>(temp)->Set_Target(m_ObjList[OBJID::PLAYER].front());
		m_ObjList[OBJID::MONSTER].push_back(temp);
	}

	//Boss
	if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000 && m_FPS <= 0) //실험용
	{
		CObj* temp = CAbstractFactory<St3_BossMonster>::Create();
		static_cast<St3_BossMonster*>(temp)->Set_Bullet(&m_ObjList[OBJID::MISSILE]);
		static_cast<St3_BossMonster*>(temp)->Set_Target(m_ObjList[OBJID::PLAYER].front());
		m_ObjList[OBJID::MONSTER].push_back(temp);
	}

	//Drone
	if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000 && m_FPS <= 0) //실험용
	{
		CObj* temp = CAbstractFactory<St3_Drone>::Create();
		static_cast<St3_Drone*>(temp)->Set_Bullet(&m_ObjList[OBJID::MISSILE]);
		m_ObjList[OBJID::MONSTER].push_back(temp);
	}

	//Trap
	if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000 && m_FPS <= 0) //실험용
	{
		CObj* temp = CAbstractFactory<St3_MineBullet>::Create();
		temp->Move_Pos(400,300);
		m_ObjList[OBJID::MISSILE].push_back(temp);
	}


}

void StageThree::Update_ObjList_ALL()
{

	for (int i = 0; i < OBJID::END; ++i)
	{
		auto iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end();)
		{
			(*iter)->Update();
			++iter;
		}
	}
}

void StageThree::Kill_ObjList()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		auto& iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end();)
		{
			if ((*iter)->Get_Dead())
			{

				short tempC = (*iter)->Get_Info().Width;
				POINT temp = { (*iter)->Get_Info().X ,(*iter)->Get_Info().Y };
				m_DeathMotionList.push_back(new St3_DeathMotion(tempC, temp)); //사망모션추가

				SAFE_DELETE((*iter));
				iter = m_ObjList[i].erase(iter);
			}
			else
			++iter;
		}
	}
}

void StageThree::Kill_DeadMoition()
{
	for (auto iter = m_DeathMotionList.begin();iter!=m_DeathMotionList.end();)
	{
		if ((*iter)->Get_Dead()==1)
		{
			SAFE_DELETE((*iter));
			iter = m_DeathMotionList.erase(iter);
		}
		else
			++iter;
	}
}




