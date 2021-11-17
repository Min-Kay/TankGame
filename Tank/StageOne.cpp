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
	Release();
}

void StageOne::Initialize()
{
	Init_DefaultSetting(1);
	Init_ObjList(); 
	Init_Patterns();


	m_Spawn = false;
	// ����� ����
#ifdef _DEBUG
	m_CoolTime = GetTickCount();
#endif
}

void StageOne::Update()
{
	Pattern(); // ���� ����

	Update_ObjList(); 


#ifdef _DEBUG
	// ����� ���
	if (m_CoolTime + 1000 < GetTickCount()) // ���� �Է� ����
	{
		if (GetAsyncKeyState(VK_F1) & 0x8000) // �¸�
		{
			Set_Clear(true);
			m_CoolTime = GetTickCount();
		}

		if (GetAsyncKeyState(VK_F2) & 0x8000) // �й�
		{
			m_ObjList[OBJID::PLAYER].front()->Set_Dead(true);
			m_CoolTime = GetTickCount();
		}

		if (GetAsyncKeyState(VK_F3) & 0x8000) // ���� ��ȯ
		{
			int posX = rand() % (WINCX / 2);
			int posY = rand() % (WINCY / 2);
			Add_MonsterList(CAbstractFactory<CMonster>::Create(posX,posY,20,20));
			m_CoolTime = GetTickCount();
		}
	}
#endif

	Update_Cursor();
}

void StageOne::Late_Update()
{
	LateUpdate_ObjList();
	
	if (m_ObjList[OBJID::MONSTER].empty())
		Set_Clear(true);

	CCollisionMgr::Collision_Rect(m_ObjList[OBJID::MISSILE],m_ObjList[OBJID::MONSTER]);

	CCollisionMgr::Collision_Rect(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER]);

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
	// ���� �ʱ�ȭ - ���� �ÿ��� ȣ���ؾ���
	OBJLIST patternA;
	patternA.push_back(CAbstractFactory<CMonster>::Create(100, 100, 20, 20));

	m_Patterns.push_back(patternA);
	
}

void StageOne::Pattern()
{
	// ���� ����

	if (m_Spawn)
		return;

	auto& iter_begin = m_Patterns.begin();
	for (; iter_begin != m_Patterns.end();)
	{
		auto& iter_beginPattern = (*iter_begin).begin();
		for (; iter_beginPattern != (*iter_begin).end();)
		{
				Add_MonsterList(CAbstractFactory<CMonster>::Create(static_cast<CMonster*>(*iter_beginPattern)));
				++iter_beginPattern;
		}
		++iter_begin;
	}

	m_Spawn = true;

}

void StageOne::Init_ObjList()
{
	m_ObjList[OBJID::PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	dynamic_cast<CPlayer*>(m_ObjList[OBJID::PLAYER].front())->Set_Bullet(&(m_ObjList[OBJID::MISSILE]));
}



