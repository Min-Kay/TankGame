#include "stdafx.h"
#include "Game.h"

Game::Game()
	:m_Selection(GAME::MENU)
{
}

Game::~Game()
{
}

void Game::Initialize()
{
}

void Game::Update()
{
}

void Game::Late_Update()
{
}

void Game::Render()
{
}

void Game::Release()
{
}

void Game::Set_Selection(GAME::GAMEID _id) // 스테이지 혹은 메뉴 설정 -> 게임 종료 시 Release_Game에서 메뉴 자동 호출 하므로 Init_DefaultSetting으로만 설정하세요
{
	m_Selection = _id; 
}

void Game::BackGround() // 배경 화면 출력 - Render 첫줄에 작성
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY); // 800 x 600 크기의 배경 출력 
}

void Game::Init_DefaultSetting(GAME::GAMEID _id) // Initialize 첫 줄에 작성하고 자기 스테이지 Enum을 매개변수로 사용하세요
{
	m_DC = GetDC(g_hWnd); // 화면 받아오기
	Init_Cursor(); // 커서 초기화
	Set_Selection(_id); // stage 번호대로 로드 설정
}

void Game::Init_Cursor() // 마우스 초기화 / Initialize 에 작성
{
	ShowCursor(false); // 커서 끄기
}

void Game::Update_Cursor() // 마우스 업데이트 / Update 에 작성
{
	GetCursorPos(&m_Point);
	ScreenToClient(g_hWnd,&m_Point);

	Update_CursorRect(); 
	
}

void Game::Render_Cursor() // 마우스 렌더 / Render 마지막 줄에 작성
{
	// 커서 렌더링

	// 마우스 좌표 원
	Ellipse(m_DC,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom);

	// 마우스 좌표 기준 선 긋기
	MoveToEx(m_DC,(int)m_Info.X, (int)m_Info.Y + 2,nullptr);
	LineTo(m_DC, (int)m_Info.X, (int)m_Info.Y + 12);

	MoveToEx(m_DC, (int)m_Info.X, (int)m_Info.Y - 2, nullptr);
	LineTo(m_DC, (int)m_Info.X, (int)m_Info.Y - 12);

	MoveToEx(m_DC, (int)m_Info.X + 2, (int)m_Info.Y, nullptr);
	LineTo(m_DC, (int)m_Info.X + 12, (int)m_Info.Y);

	MoveToEx(m_DC, (int)m_Info.X - 2, (int)m_Info.Y, nullptr);
	LineTo(m_DC, (int)m_Info.X - 12, (int)m_Info.Y);
}

void Game::Update_CursorRect() 
{
	// 커서 위치 기반 커서 RECT 설정

	m_Info.X = m_Point.x;
	m_Info.Y = m_Point.y;

	m_Info.Width = 16;
	m_Info.Height = 16;

	m_Rect.left = m_Info.X - (m_Info.Width / 2);
	m_Rect.right = m_Info.X + (m_Info.Width / 2);

	m_Rect.top = m_Info.Y - (m_Info.Height / 2);
	m_Rect.bottom = m_Info.Y + (m_Info.Height / 2);

}
