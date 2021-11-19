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
	list<CObj*> m_Select_Box; // �޴� ���� â 

	TCHAR		m_SzTitle[20]; // ���� 
	RECT		m_TitleRect; // ���� �ڽ�

	TCHAR		m_SzEscape[10]; // ������
	RECT		m_EscapeRect; // ������ �ڽ�

	bool		isEscape; // ������ bool ���� 

	HFONT		TitleFont, MenuFont, oldFont; // ��Ʈ ����

	
};

