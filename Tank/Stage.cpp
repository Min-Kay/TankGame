#include "stdafx.h"
#include "Stage.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Satellite.h"
#include "Manager.h"

void Stage::Goto_Menu() // �޴��� ���ư���
{
	if (m_Result != GAMERESULT::NONE)
	{
		Show_Win_Lose(); // ���� ���
		Release(); 
	}
}

void Stage::Release_Game() // ���� ������ �׸� ó�� �Լ�
{
	// ���������� ȣ���ϼ���.
	Set_Selection(GAME::MENU); // ���� ��ȣ �޴��� ����
	ReleaseDC(g_hWnd, m_DC); // ȭ�� ����
	Release_Patterns(); // ���� ����Ʈ ����
	Release_ObjList(); // ������Ʈ ����Ʈ ����
}

void Stage::Check_Collision() // ���� ���� �浹ó�� - Late_Update�� �ۼ�
{
	CCollisionMgr::Collision_Rect(m_ObjList[OBJID::MISSILE], m_ObjList[OBJID::MONSTER]);
	/*
	CCollisionMgr::Collision_Rect(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJID::MISSILE], m_ObjList[OBJID::PLAYER]);
	*/
	CCollisionMgr::Collision_Rect(m_ObjList[OBJID::MISSILE], m_ObjList[OBJID::MISSILE]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJID::SATELLITE], m_ObjList[OBJID::MONSTER]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJID::MISSILE], m_ObjList[OBJID::SATELLITE]);
}

void Stage::Check_GameState() // ���� ���� ó�� �Լ� 
{
	if (true == isClear) // ������ ��� Ŭ����
		Set_Result(GAMERESULT::WIN); // �¸� ó��
	else if (m_ObjList[OBJID::PLAYER].empty()|| m_ObjList[OBJID::PLAYER].front()->Get_Dead()) // �÷��̾� ���
		Set_Result(GAMERESULT::LOSE); // �й� ó��
}

void Stage::Show_Win_Lose() // ���� ��� �Լ�
{
	DWORD		showTime = GetTickCount(); 
	TCHAR		szShow[10] = L"";
	RECT		m_BackgroundRect{0,0,WINCX,WINCY}, m_TextRect{ WINCX / 2  - WINCX / 16, WINCY / 2 - WINCY / 16, WINCX - (WINCX / 2), WINCY - (WINCY / 2)};
	HFONT		hFont, oldFont; // ��Ʈ ����
	HBRUSH		brush = NULL; // �� ����

	hFont = CreateFont(50,0,0,0,0,0,0,0,HANGEUL_CHARSET,0,0,0,VARIABLE_PITCH|FF_ROMAN,TEXT("����ü")); // ��Ʈ ����
	oldFont = (HFONT)SelectObject(m_DC,hFont); // ��Ʈ ����

	switch (m_Result)
	{
	case GAMERESULT::WIN:
		SetTextColor(m_DC, RGB(0, 255, 0)); // �ؽ�Ʈ �� ����
		brush = CreateSolidBrush(RGB(0, 150, 0)); // ��� �� ����
		swprintf_s(szShow, L"�¸�");
		break;
	case GAMERESULT::LOSE:
		SetTextColor(m_DC, RGB(255, 0, 0));
		brush = CreateSolidBrush(RGB(150, 0, 0));
		swprintf_s(szShow, L"�й�");
		break;
	default:
		break;
	}

	Rectangle(m_DC, m_BackgroundRect.left, m_BackgroundRect.top, m_BackgroundRect.right, m_BackgroundRect.bottom);
	
	FillRect(m_DC, &m_BackgroundRect, brush); // RECT�� �� ä��� 
	FillRect(m_DC, &m_TextRect, brush);

	while (showTime + 3000 > GetTickCount())
	{
		TextOut(m_DC, m_TextRect.left, m_TextRect.top, szShow, lstrlen(szShow));
	}

}

void Stage::Cheat_Mode() // Debug������ ���ư��� �׽�Ʈ������ ������
{
#ifdef _DEBUG
	// ����� ���
	if (Debug_Timer + 1000 < GetTickCount()) // ���� �Է� ����
	{
		if (GetAsyncKeyState(VK_F1) & 0x8000) // �¸�
		{
			Set_Clear(true);
			Debug_Timer = GetTickCount();
		}

		if (GetAsyncKeyState(VK_F2) & 0x8000) // �й�
		{
			m_ObjList[OBJID::PLAYER].front()->Set_Dead(true);
			Debug_Timer = GetTickCount();
		}

		if (GetAsyncKeyState(VK_F3) & 0x8000) // ���� ��ġ ����Ʈ ���� ��ȯ
		{
			int posX = rand() % (WINCX / 2);
			int posY = rand() % (WINCY / 2);
			Add_MonsterList(CAbstractFactory<CMonster>::Create(float(posX), float(posY), float(20), float(20)));
			Debug_Timer = GetTickCount();
		}

		if (GetAsyncKeyState(VK_F6) & 0x8000)
		{
			auto& player = m_ObjList[OBJID::PLAYER].front();
			CObj* temp = CAbstractFactory<CSatellite>::Create();
			static_cast<CSatellite*>(temp)->Set_Ownner(player);
			static_cast<CPlayer*>(player)->Add_Satellite(temp);
			Debug_Timer = GetTickCount();
		}
	}

#endif
}

void Stage::Release_Patterns() // ���� ������ ���� �Լ� 
{
	auto& iter_begin = m_Patterns.begin();
	for (; iter_begin != m_Patterns.end();)
	{
		if (!(*iter_begin).empty())
		{
			for_each(iter_begin->begin(), iter_begin->end(), CDeleteObj()); // CObj* �� ��� ���� ����Ʈ ����
			iter_begin->clear();
			iter_begin = m_Patterns.erase(iter_begin);
		}
		else
		{
			++iter_begin;
		}
	}
}

void Stage::Update_ObjList() // ������Ʈ ����Ʈ ������Ʈ ���� �Լ�
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		auto& iter_begin = m_ObjList[i].begin();
		for ( ;iter_begin != m_ObjList[i].end() ; )
		{
			(*iter_begin)->Update();

			if ((*iter_begin)->Get_Dead())
			{
				SAFE_DELETE((*iter_begin));
				iter_begin = m_ObjList[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}
}

void Stage::LateUpdate_ObjList() // ������Ʈ ����Ʈ ����Ʈ ������Ʈ ���� �Լ�
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& j : m_ObjList[i])
		{
			j->Late_Update(m_ObjList);
		}
	}
}

void Stage::Render_ObjList() // ������Ʈ ����Ʈ ���� ���� �Լ�
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& j : m_ObjList[i])
		{
			j->Render(m_DC);
		}
	}
}


void Stage::Release_ObjList() // ������Ʈ ����Ʈ ������ ���� �Լ�
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj()); // ������Ʈ����Ʈ ����
		m_ObjList[i].clear();
	}

}

void Stage::Add_MonsterList(CObj * _monster) // ���� �߰� �Լ�
{
	m_ObjList[OBJID::MONSTER].push_back(_monster);
}

