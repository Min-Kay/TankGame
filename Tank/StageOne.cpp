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
	Pattern(); // ���� ����

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
	patternA.push_back(CAbstractFactory<CMonster>::Create(100, 100, 20, 20));

	m_Patterns.push_back(patternA);
	
}

void StageOne::Pattern()
{
	// ���� ����
	// ���� ������ �����Ӱ� �����ϵ� 
	// ��� ������ �����ߴٸ� Set_Clear()�� ���� isClear�� true�� ������ �¸��� �����Ͻø� �˴ϴ�.
	// �÷��̾� �й�� Check_GameState() ���� �ڵ� ó�� �մϴ�.
	// �㳪 �ΰ����� �й� ���(��� ���� ��)�� �����Ͻ÷��� Set_Result() �� ���� Enum���� NONE�� ������ �ٸ� ������ �����Ͻø� 
	// Goto_Menu()�� m_Result�� ���� ���� ������ ����ǵ��� ó���մϴ�.

	if (m_Spawn)
		return;

	Add_MonsterList(CAbstractFactory<CMonster>::Create(static_cast<CMonster*>(m_Patterns[0][0])));

	m_Spawn = true;

}

void StageOne::Init_ObjList()
{
	// ������Ʈ ����Ʈ �ʱ�ȭ ���� - Initialize�� �ۼ�
	// �����Ӱ� m_ObjList�� �߰��ϰ��� �ϴ� CObj �߰��Ͻø� �˴ϴ�.

	m_ObjList[OBJID::PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	static_cast<CPlayer*>(m_ObjList[OBJID::PLAYER].front())->Set_Bullet(&(m_ObjList[OBJID::MISSILE]));
}



