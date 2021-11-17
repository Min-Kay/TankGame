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
	Rectangle(m_DC, 0, 0, WINCX, WINCY); // 800 x 600 ũ���� ȭ�� ���
}

void Game::Init_DefaultSetting(int _gameNum)
{
	m_DC = GetDC(g_hWnd); // ȭ�� �޾ƿ���
	Set_Loaded(true); // �ε� �Ϸ�
	Init_Cursor(); // Ŀ�� �ʱ�ȭ
	Set_Selection(_gameNum); // stage ��ȣ��� �ε� ����
}

void Game::Init_Cursor()
{
	ShowCursor(false); // Ŀ�� ����
}

void Game::Update_Cursor()
{
	GetCursorPos(&m_Point);
	ScreenToClient(g_hWnd,&m_Point);

	Update_CursorRect(); 
	
}

void Game::Render_Cursor()
{
	// Ŀ�� ������

	// ���콺 ��ǥ ��
	Ellipse(m_DC,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom);

	// ���콺 ��ǥ ���� �� �߱�
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
	// Ŀ�� ��ġ ��� Ŀ�� RECT ����

	m_Info.X = m_Point.x;
	m_Info.Y = m_Point.y;

	m_Info.Width = 16;
	m_Info.Height = 16;

	m_Rect.left = m_Info.X - (m_Info.Width / 2);
	m_Rect.right = m_Info.X + (m_Info.Width / 2);

	m_Rect.top = m_Info.Y - (m_Info.Height / 2);
	m_Rect.bottom = m_Info.Y + (m_Info.Height / 2);

}
