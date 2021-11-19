#include "stdafx.h"
#include "Menu.h"
#include "Obj.h"
#include "Click.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"

Menu::Menu()
	:m_SzTitle(L""), m_SzEscape(L""), isEscape(false)
{
}

Menu::~Menu()
{
	Release();
}

void Menu::Initialize()
{
	Init_DefaultSetting(GAME::MENU);

	int pos = 250;
	for (int i = 0; i < 4; ++i)
	{
		m_Select_Box.push_back(CAbstractFactory<CClick>::Create(400, pos,250,50,GAME::GAMEID(i+1)));
		pos += 70;
	}
	
	m_TitleRect.top = 50;
	m_TitleRect.bottom = 150;
	m_TitleRect.left = 100;
	m_TitleRect.right = 700;

	m_EscapeRect.top = 500;
	m_EscapeRect.bottom = 550;
	m_EscapeRect.left = 600;
	m_EscapeRect.right = 700;

	swprintf_s(m_SzEscape, L"나가기");
	swprintf_s(m_SzTitle, L"탱크 게임");

	MenuFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림체"));
	TitleFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림체"));
}

void Menu::Update()
{
	for (auto& i : m_Select_Box)
	{
		i->Update();
	}

	Update_Cursor();
}

void Menu::Late_Update()
{
	m_Selection = CCollisionMgr::Collision_Mouse(m_Rect, m_Select_Box);

	if (CCollisionMgr::Collision_Mouse_Box(m_Rect, m_EscapeRect))
	{
		isEscape = true;
		PostQuitMessage(0);
	}
}

void Menu::Render()
{
	BackGround();

	oldFont = (HFONT)SelectObject(m_DC, MenuFont);

	//선택지
	for (auto& i : m_Select_Box)
	{
		i->Render(m_DC);
	}

	Rectangle(m_DC, m_EscapeRect.left, m_EscapeRect.top, m_EscapeRect.right, m_EscapeRect.bottom);
	TextOut(m_DC, m_EscapeRect.left + 15, m_EscapeRect.top + 15, m_SzEscape, lstrlen(m_SzEscape));

	oldFont = (HFONT)SelectObject(m_DC, TitleFont);

	Rectangle(m_DC, m_TitleRect.left, m_TitleRect.top, m_TitleRect.right, m_TitleRect.bottom);
	TextOut(m_DC, m_TitleRect.left + 175, m_TitleRect.top + 20 , m_SzTitle, lstrlen(m_SzTitle));

	Render_Cursor();
}

void Menu::Release()
{
	ReleaseDC(g_hWnd,m_DC);
	for_each(m_Select_Box.begin(), m_Select_Box.end(),CDeleteObj()); // 메뉴 창 지움
}
