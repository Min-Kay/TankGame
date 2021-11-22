#include "stdafx.h"
#include "Stage.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Satellite.h"
#include "Manager.h"

void Stage::Goto_Menu() // 메뉴로 돌아가기
{
	if (m_Result != GAMERESULT::NONE)
	{
		Show_Win_Lose(); // 승패 출력
		Release(); 
	}
}

void Stage::Release_Game() // 공통 릴리스 항목 처리 함수
{
	// 릴리스에다 호출하세요.
	Set_Selection(GAME::MENU); // 게임 번호 메뉴로 변경
	ReleaseDC(g_hWnd, m_DC); // 화면 해제
	Release_Patterns(); // 패턴 리스트 해제
	Release_ObjList(); // 오브젝트 리스트 해제
}

void Stage::Check_Collision() // 게임 공통 충돌처리 - Late_Update에 작성
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

void Stage::Check_GameState() // 게임 승패 처리 함수 
{
	if (true == isClear) // 패턴을 모두 클리어
		Set_Result(GAMERESULT::WIN); // 승리 처리
	else if (m_ObjList[OBJID::PLAYER].empty()|| m_ObjList[OBJID::PLAYER].front()->Get_Dead()) // 플레이어 사망
		Set_Result(GAMERESULT::LOSE); // 패배 처리
}

void Stage::Show_Win_Lose() // 승패 출력 함수
{
	DWORD		showTime = GetTickCount(); 
	TCHAR		szShow[10] = L"";
	RECT		m_BackgroundRect{0,0,WINCX,WINCY}, m_TextRect{ WINCX / 2  - WINCX / 16, WINCY / 2 - WINCY / 16, WINCX - (WINCX / 2), WINCY - (WINCY / 2)};
	HFONT		hFont, oldFont; // 폰트 설정
	HBRUSH		brush = NULL; // 색 설정

	hFont = CreateFont(50,0,0,0,0,0,0,0,HANGEUL_CHARSET,0,0,0,VARIABLE_PITCH|FF_ROMAN,TEXT("굴림체")); // 폰트 제작
	oldFont = (HFONT)SelectObject(m_DC,hFont); // 폰트 변경

	switch (m_Result)
	{
	case GAMERESULT::WIN:
		SetTextColor(m_DC, RGB(0, 255, 0)); // 텍스트 색 설정
		brush = CreateSolidBrush(RGB(0, 150, 0)); // 배경 색 설정
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
	
	FillRect(m_DC, &m_BackgroundRect, brush); // RECT에 색 채우기 
	FillRect(m_DC, &m_TextRect, brush);

	while (showTime + 3000 > GetTickCount())
	{
		TextOut(m_DC, m_TextRect.left, m_TextRect.top, szShow, lstrlen(szShow));
	}

}

void Stage::Cheat_Mode() // Debug에서만 돌아가니 테스트용으로 쓰세요
{
#ifdef _DEBUG
	// 디버깅 모드
	if (Debug_Timer + 1000 < GetTickCount()) // 연속 입력 방지
	{
		if (GetAsyncKeyState(VK_F1) & 0x8000) // 승리
		{
			Set_Clear(true);
			Debug_Timer = GetTickCount();
		}

		if (GetAsyncKeyState(VK_F2) & 0x8000) // 패배
		{
			m_ObjList[OBJID::PLAYER].front()->Set_Dead(true);
			Debug_Timer = GetTickCount();
		}

		if (GetAsyncKeyState(VK_F3) & 0x8000) // 임의 위치 디폴트 몬스터 소환
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

void Stage::Release_Patterns() // 패턴 릴리스 공통 함수 
{
	auto& iter_begin = m_Patterns.begin();
	for (; iter_begin != m_Patterns.end();)
	{
		if (!(*iter_begin).empty())
		{
			for_each(iter_begin->begin(), iter_begin->end(), CDeleteObj()); // CObj* 를 담던 패턴 리스트 해제
			iter_begin->clear();
			iter_begin = m_Patterns.erase(iter_begin);
		}
		else
		{
			++iter_begin;
		}
	}
}

void Stage::Update_ObjList() // 오브젝트 리스트 업데이트 공통 함수
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

void Stage::LateUpdate_ObjList() // 오브젝트 리스트 레이트 업데이트 공통 함수
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& j : m_ObjList[i])
		{
			j->Late_Update(m_ObjList);
		}
	}
}

void Stage::Render_ObjList() // 오브젝트 리스트 렌더 공통 함수
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& j : m_ObjList[i])
		{
			j->Render(m_DC);
		}
	}
}


void Stage::Release_ObjList() // 오브젝트 리스트 릴리스 공통 함수
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj()); // 오브젝트리스트 해제
		m_ObjList[i].clear();
	}

}

void Stage::Add_MonsterList(CObj * _monster) // 몬스터 추가 함수
{
	m_ObjList[OBJID::MONSTER].push_back(_monster);
}

