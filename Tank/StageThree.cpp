#include "stdafx.h"
#include "StageThree.h"
#include "GameHeader.h"
#include "Obj.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "Monster.h"
#include "St3_MonCommon00.h"
#include "Manager.h"

StageThree::StageThree()
{
}

StageThree::~StageThree()
{
}

void StageThree::Initialize()
{
	Init_DefaultSetting(GAME::STAGE_THREE); 
	Init_ObjList();
	Init_Patterns();
}

void StageThree::Update()
{
	Pattern(); // ���� ����

	Update_ObjList(); // ��ü�� ������Ʈ ����

	Cheat_Mode();	// �׽�Ʈ��

	Update_Cursor();
}

void StageThree::Late_Update()
{
	LateUpdate_ObjList(); // ��ü�� ���� ������Ʈ ����

	CCollisionMgr::Collision_Rect(m_ObjList[OBJID::MISSILE], m_ObjList[OBJID::MONSTER]);

	CCollisionMgr::Collision_Rect(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER]);

	Check_GameState();

	Goto_Menu();
}

void StageThree::Render()
{
	// ��� - ������Ʈ - Ŀ�� ������ ����

	BackGround();
	Render_ObjList(); // ��ü�� ������ ����
	Render_Cursor();

}


void StageThree::Release()
{
	Release_Game();
}

//Initalise ���
void StageThree::Init_ObjList()
{
	m_ObjList[OBJID::PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	static_cast<CPlayer*>(m_ObjList[OBJID::PLAYER].front())->Set_Bullet(&m_ObjList[OBJID::MISSILE]);
}

//�����Լ�

void StageThree::Init_Patterns()
{
	OBJVEC Pattern1;
	Pattern1.push_back(CAbstractFactory<St3_MonCommon00>::Create());

	m_Patterns.push_back(Pattern1);

	for (auto& i : m_Patterns)
	{
		for (auto& temp : i)
		{
			m_ObjList[OBJID::MONSTER].push_back(temp);
			temp = nullptr;
		}
	}
}

void StageThree::Pattern()
{

}




