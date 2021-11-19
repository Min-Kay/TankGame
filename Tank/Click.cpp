#include "stdafx.h"
#include "Click.h"


CClick::CClick()
	:szStageNum(L"")
{
}


CClick::~CClick()
{
}

void CClick::Initialize(void)
{
	Set_Selection(GAME::GAMEID(int(m_Speed))); // CObj�� �߰� ������ �������� �ʰ� speed�� �̿��� selection�� ������
	Update_Rect();
}

int CClick::Update(void)
{
	return OBJ_NOEVENT;
}

void CClick::Late_Update(OBJLIST* _objlist)
{
}

void CClick::Render(HDC _hDC)
{
	Rectangle(_hDC,m_Body.left,m_Body.top,m_Body.right,m_Body.bottom);

	swprintf_s(szStageNum, L"�������� %d", m_Selection);
	TextOut(_hDC, m_Info.X - 40 , m_Info.Y - 10 , szStageNum, lstrlen(szStageNum));
}

void CClick::Release(void)
{
}

void CClick::Set_Selection(GAME::GAMEID i)
{
	m_Selection = i;
}

GAME::GAMEID CClick::Get_Selection()
{
	return m_Selection;
}
