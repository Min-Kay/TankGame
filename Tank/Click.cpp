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
	Set_Selection(int(m_Speed));
	Update_Rect();
}

int CClick::Update(void)
{
	return OBJ_NOEVENT;
}

void CClick::Late_Update(void)
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

void CClick::Set_Selection(int i)
{
	m_Selection = i;
}

int CClick::Get_Selection()
{
	return m_Selection;
}
