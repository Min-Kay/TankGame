#include "stdafx.h"
#include "Stage.h"
#include "Player.h"

void Stage::Goto_Menu()
{
	if (m_Result != GAMERESULT::NONE)
	{
		Show_Win_Lose(); // 승패 출력
		Release(); // 배열 해제
	}
}

void Stage::Release_Game() 
{
	// 릴리스에다 호출하세요.

	ReleaseDC(g_hWnd, m_DC); // 화면 해제
	Release_Patterns(); // 패턴 리스트 해제
	Release_ObjList(); // 오브젝트 리스트 해제
	Set_Result(GAMERESULT::NONE); // 결과값 초기화
	Set_Selection(0); // 게임 번호 메뉴로 변경
	Set_Clear(false); // 클리어 초기화
	Set_Loaded(false); // 로드 초기화 
}

void Stage::Check_GameState()
{
	if (true == isClear) // 패턴을 모두 클리어
		Set_Result(GAMERESULT::WIN); // 승리 처리
	else if (true == m_ObjList[OBJID::PLAYER].front()->Get_Dead()) // 플레이어 사망
		Set_Result(GAMERESULT::LOSE); // 패배 처리
}

void Stage::Show_Win_Lose()
{
	DWORD		showTime = GetTickCount(); 
	TCHAR		szShow[10] = L"";
	RECT		m_BackgroundRect{0,0,WINCX,WINCY},
				m_TextRect{ WINCX / 2  - WINCX / 16, WINCY / 2 - WINCY / 16, WINCX - (WINCX / 2), WINCY - (WINCY / 2)};
	HFONT		hFont, oldFont;
	HBRUSH		brush = NULL;

	hFont = CreateFont(50,0,0,0,0,0,0,0,HANGEUL_CHARSET,0,0,0,VARIABLE_PITCH|FF_ROMAN,TEXT("굴림체"));
	oldFont = (HFONT)SelectObject(m_DC,hFont);

	switch (m_Result)
	{
	case GAMERESULT::WIN:
		SetTextColor(m_DC, RGB(0, 255, 0));
		brush = CreateSolidBrush(RGB(0, 150, 0));
		swprintf_s(szShow, L"승리");
		break;
	case GAMERESULT::LOSE:
		SetTextColor(m_DC, RGB(255, 0, 0));
		brush = CreateSolidBrush(RGB(150, 0, 0));
		swprintf_s(szShow, L"패배");
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
			for_each(iter_begin->begin(), iter_begin->end(),CDeleteObj()); // 패턴 리스트 해제
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
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj()); // 오브젝트리스트 해제
		m_ObjList[i].clear();
	}

}

void Stage::Add_MonsterList(CObj * _monster) 
{
	m_ObjList[OBJID::MONSTER].push_back(_monster);
}



