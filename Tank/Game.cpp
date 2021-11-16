#include "stdafx.h"
#include "Game.h"

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

void Game::Init_Cursor()
{
	ShowCursor(false);
}

void Game::Update_Cursor()
{
	GetCursorPos(&m_Point);
	ScreenToClient(g_hWnd,&m_Point);

	Update_CursorRect(); 
	
}

void Game::Render_Cursor()
{
	Ellipse(m_DC,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom);
}

void Game::Release_Cursor()
{
}

void Game::Update_CursorRect()
{
	m_Info.X = m_Point.x;
	m_Info.Y = m_Point.y;

	m_Info.Width = 10;
	m_Info.Height = 10;

	m_Rect.left = m_Info.X - (m_Info.Width / 2);
	m_Rect.right = m_Info.X + (m_Info.Width / 2);

	m_Rect.top = m_Info.Y - (m_Info.Height / 2);
	m_Rect.bottom = m_Info.Y + (m_Info.Height / 2);

}
