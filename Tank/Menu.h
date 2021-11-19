#pragma once
#include "Game.h"

class CObj;

class Menu :
	public Game
{
public:
	Menu();
	virtual ~Menu();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	list<CObj*> m_Select_Box; // 메뉴 선택 창 

	TCHAR		m_SzTitle[20]; // 제목 
	RECT		m_TitleRect; // 제목 박스

	TCHAR		m_SzEscape[10]; // 나가기
	RECT		m_EscapeRect; // 나가기 박스

	bool		isEscape; // 나가기 bool 변수 

	HFONT		TitleFont, MenuFont, oldFont; // 폰트 설정

	
};

