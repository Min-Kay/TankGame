#include "stdafx.h"
#include "StageOne.h"
#include "GameHeader.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"

StageOne::StageOne()
{
}

StageOne::~StageOne()
{
}

void StageOne::Initialize()
{
	Init_DefaultSetting(GAME::STAGE_ONE);
	Init_ObjList(); 
	Init_Patterns();

	m_Spawn = false;
}

void StageOne::Update()
{
	Pattern(); // 패턴 진행

	Update_ObjList(); 

	Cheat_Mode();

	Update_Cursor();
}

void StageOne::Late_Update()
{
	LateUpdate_ObjList();
	
	if (m_ObjList[OBJID::MONSTER].empty())
		Set_Clear(true);

	Check_Collision();

	Check_GameState();

	Goto_Menu();
}

void StageOne::Render()
{
	// 배경 - 오브젝트 - 커서 순으로 렌더

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
	// 패턴 초기화 - Initialize 시에 작성
	// 패턴 제약은 따로 없습니다.
	// 패턴 추가는 vector<CObj*>로 만들고 몬스터를 생성 및 할당 한 후 해당 패턴을 m_Patterns에 push_back 하시면 됩니다.
	// 패턴 수행 시 m_Patterns를 2차원 배열 형태로 호출해 몬스터를 소환하시면 됩니다.

	OBJVEC  patternA;
	patternA.push_back(CAbstractFactory<CMonster>::Create(100, 100, 20, 20));

	m_Patterns.push_back(patternA);
	
}

void StageOne::Pattern()
{
	// 패턴 실행
	// 패턴 구성은 자유롭게 설정하되 
	// 모든 패턴을 수행했다면 Set_Clear()를 통해 isClear를 true로 변경해 승리를 설정하시면 됩니다.
	// 플레이어 패배는 Check_GameState() 에서 자동 처리 합니다.
	// 허나 부가적인 패배 요소(기믹 수행 등)를 설정하시려면 Set_Result() 를 통해 Enum값을 NONE을 제외한 다른 값으로 변경하시면 
	// Goto_Menu()가 m_Result의 값을 통해 게임이 종료되도록 처리합니다.

	if (m_Spawn)
		return;

	Add_MonsterList(CAbstractFactory<CMonster>::Create(static_cast<CMonster*>(m_Patterns[0][0])));

	m_Spawn = true;

}

void StageOne::Init_ObjList()
{
	// 오브젝트 리스트 초기화 설정 - Initialize에 작성
	// 자유롭게 m_ObjList에 추가하고자 하는 CObj 추가하시면 됩니다.

	m_ObjList[OBJID::PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	static_cast<CPlayer*>(m_ObjList[OBJID::PLAYER].front())->Set_Bullet(&(m_ObjList[OBJID::MISSILE]));
}



