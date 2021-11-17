#include "stdafx.h"
#include "Stage.h"
#include "Player.h"

void Stage::Goto_Menu()
{
	if (m_Result != GAMERESULT::NONE)
	{
		Show_Win_Lose(); // ���� ���
		Release(); // �迭 ����
	}
}

void Stage::Release_Game() 
{
	// ���������� ȣ���ϼ���.

	ReleaseDC(g_hWnd, m_DC); // ȭ�� ����
	Release_Patterns(); // ���� ����Ʈ ����
	Release_ObjList(); // ������Ʈ ����Ʈ ����
	Set_Result(GAMERESULT::NONE); // ����� �ʱ�ȭ
	Set_Selection(0); // ���� ��ȣ �޴��� ����
	Set_Clear(false); // Ŭ���� �ʱ�ȭ
	Set_Loaded(false); // �ε� �ʱ�ȭ 
}

void Stage::Check_GameState()
{
	if (true == isClear) // ������ ��� Ŭ����
		Set_Result(GAMERESULT::WIN); // �¸� ó��
	else if (true == m_ObjList[OBJID::PLAYER].front()->Get_Dead()) // �÷��̾� ���
		Set_Result(GAMERESULT::LOSE); // �й� ó��
}

void Stage::Show_Win_Lose()
{
	DWORD		showTime = GetTickCount(); 
	TCHAR		szShow[10] = L"";
	RECT		m_BackgroundRect{0,0,WINCX,WINCY},
				m_TextRect{ WINCX / 2  - WINCX / 16, WINCY / 2 - WINCY / 16, WINCX - (WINCX / 2), WINCY - (WINCY / 2)};
	HFONT		hFont, oldFont;
	HBRUSH		brush = NULL;

	hFont = CreateFont(50,0,0,0,0,0,0,0,HANGEUL_CHARSET,0,0,0,VARIABLE_PITCH|FF_ROMAN,TEXT("����ü"));
	oldFont = (HFONT)SelectObject(m_DC,hFont);

	switch (m_Result)
	{
	case GAMERESULT::WIN:
		SetTextColor(m_DC, RGB(0, 255, 0));
		brush = CreateSolidBrush(RGB(0, 150, 0));
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
	FillRect(m_DC, &m_BackgroundRect, brush);
	
	FillRect(m_DC, &m_TextRect, brush);

	while (showTime + 3000 > GetTickCount())
	{
		TextOut(m_DC, m_TextRect.left, m_TextRect.top, szShow, lstrlen(szShow));
	}

}

void Stage::Release_Patterns()
{
	auto& iter_begin = m_Patterns.begin();
	for (; iter_begin != m_Patterns.end();)
	{
		if (!(*iter_begin).empty())
		{
			for_each(iter_begin->begin(), iter_begin->end(),CDeleteObj()); // ���� ����Ʈ ����
			iter_begin->clear();
		}
		else
		{
			++iter_begin;
		}
	}
}

void Stage::Update_ObjList()
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

void Stage::LateUpdate_ObjList()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& j : m_ObjList[i])
		{
			if(!j->Get_Dead())
				j->Late_Update();
		}
	}
}

void Stage::Render_ObjList()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& j : m_ObjList[i])
		{
			if (!j->Get_Dead())
				j->Render(m_DC);
		}
	}
}


void Stage::Release_ObjList()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj()); // ������Ʈ����Ʈ ����
		m_ObjList[i].clear();
	}

}

void Stage::Add_MonsterList(CObj * _monster) 
{
	m_ObjList[OBJID::MONSTER].push_back(_monster);
}



