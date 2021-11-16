#include "stdafx.h"
#include "Stage.h"


void Stage::Goto_Menu()
{
	if (m_Result != GAMERESULT::NONE)
		Set_Selection(0);
}

void Stage::Release_Game()
{
	m_isLoaded = false;
	// 패턴 리스트 해제
}
