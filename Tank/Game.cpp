#include "stdafx.h"
#include "Game.h"

Game::Game()
	:m_Selection(0)
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

bool Game::Get_Loaded()
{
	return m_isLoaded;
}

void Game::Set_Selection(int i)
{
	m_Selection = i; 
}

void Game::BackGround()
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY); // 800 x 600 크기의 화면 출력
}

void Game::Init_DefaultSetting(int _gameNum)
{
	m_DC = GetDC(g_hWnd); // 화면 받아오기
	Set_Loaded(true); // 로딩 완료
	Init_Cursor(); // 커서 초기화
	Set_Selection(_gameNum); // stage 번호대로 로드 설정
}

void Game::Init_Cursor()
{
	ShowCursor(false); // 커서 끄기
}

void Game::Update_Cursor()
{
	GetCursorPos(&m_Point);
	ScreenToClient(g_hWnd,&m_Point);

	Update_CursorRect(); 
	
}

void Game::Render_Cursor()
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

void Game::Release_Cursor()
{
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
