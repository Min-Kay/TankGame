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

void Game::Set_Selection(GAME::GAMEID _id) // �������� Ȥ�� �޴� ���� -> ���� ���� �� Release_Game���� �޴� �ڵ� ȣ�� �ϹǷ� Init_DefaultSetting���θ� �����ϼ���
{
	m_Selection = _id; 
}

void Game::BackGround() // ��� ȭ�� ��� - Render ù�ٿ� �ۼ�
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY); // 800 x 600 ũ���� ��� ��� 
}

void Game::Init_DefaultSetting(GAME::GAMEID _id) // Initialize ù �ٿ� �ۼ��ϰ� �ڱ� �������� Enum�� �Ű������� ����ϼ���
{
	m_DC = GetDC(g_hWnd); // ȭ�� �޾ƿ���
	Init_Cursor(); // Ŀ�� �ʱ�ȭ
	Set_Selection(_id); // stage ��ȣ��� �ε� ����
}

void Game::Init_Cursor() // ���콺 �ʱ�ȭ / Initialize �� �ۼ�
{
	ShowCursor(false); // Ŀ�� ����
}

void Game::Update_Cursor() // ���콺 ������Ʈ / Update �� �ۼ�
{
	GetCursorPos(&m_Point);
	ScreenToClient(g_hWnd,&m_Point);

	Update_CursorRect(); 
	
}

void Game::Render_Cursor() // ���콺 ���� / Render ������ �ٿ� �ۼ�
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
