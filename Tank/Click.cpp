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
	Set_Selection(GAME::GAMEID(int(m_Speed))); // CObj에 추가 변수를 선언하지 않고 speed를 이용해 selection을 변경함
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

	swprintf_s(szStageNum, L"스테이지 %d", m_Selection);
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
