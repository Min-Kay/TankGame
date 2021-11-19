#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Click.h"
#include "Enum.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

GAME::GAMEID CCollisionMgr::Collision_Mouse(RECT& mouse, list<CObj*> _Src) // 마우스 - 스테이지 선택
{
	RECT	rc{};

	for (auto& Src : _Src)
	{
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && IntersectRect(&rc, &mouse, &(Src->Get_Body())))
		{
				return static_cast<CClick*>(Src)->Get_Selection();
		}
	}
	return GAME::MENU;
}

bool CCollisionMgr::Collision_Mouse_Box(RECT& mouse, RECT& box) // 마우스 - 나가기
{
	RECT	rc{};

	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && IntersectRect(&rc, &mouse, &box))
	{
		return true;
	}

	return false;
}


void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src) // 오브젝트 리스트 간의 RECT 비교
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (!Dest->Check_Type(Src) && IntersectRect(&rc, &(Dest->Get_Body()), &(Src->Get_Body()))) // 오브젝트의 타입을 비교해 서로 다르고 RECT가 충돌됐다고 판단되면 true
			{
				Dest->Set_Dead(true);
				Src->Set_Dead(true);
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSrc, int _range) // 거리에 따른 오브젝트 간 Sphere 비교
{
	float		fWidth = abs(pDest->Get_Info().X - pSrc->Get_Info().X);
	float		fHeight = abs(pDest->Get_Info().Y - pSrc->Get_Info().Y);

	float		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (_range + pSrc->Get_Info().Width) * 0.5f;

	return fRadius > fDistance; // 충돌
}


void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src) // 오브젝트 리스트 간의 Sphere 비교
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dest, Src))			
			{
				Dest->Set_Dead(true);
				Src->Set_Dead(true);
			}
		}
	}
}


