#include "stdafx.h"
#include "Menu.h"

void Menu::Initialize()
{
	m_DC = GetDC(g_hWnd);
	m_isLoaded = true;
	Init_Cursor();

	int pos = 200;
	for (auto& i : m_Select_Rect)
	{
		i.left = 100;
		i.right = 300;
		i.bottom = pos;
		i.top = pos - 50;
		
		pos += 60;

	}
}

void Menu::Update()
{
	Update_Cursor();
}

void Menu::Late_Update()
{
	
}

void Menu::Render()
{

	Rectangle(m_DC,0,0,WINCX,WINCY);

	//º±≈√¡ˆ
	for (auto& i : m_Select_Rect)
	{
		Rectangle(m_DC, i.left, i.top, i.right, i.bottom);
	}

	Render_Cursor();
}

void Menu::Release()
{
}
