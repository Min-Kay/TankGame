#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Mouse(RECT& mouse, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Src : _Src)
	{
		if (IntersectRect(&rc, &mouse, &(Src->Get_Body())))
		{

		}
	}
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dest->Get_Body()), &(Src->Get_Body())))
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}

}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dest, Src))			
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSrc)
{
	float		fWidth  = abs(pDest->Get_Info().X - pSrc->Get_Info().X);
	float		fHeight = abs(pDest->Get_Info().Y - pSrc->Get_Info().Y);

	float		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDest->Get_Info().Width + pSrc->Get_Info().Width) * 0.5f;

	return fRadius > fDistance; // 충돌
}

// IntersectRect

// 1. 충돌하여 렉트끼리 겹친 영역의 사각형을 전달
// 2.3 충돌하는 렉트들의 주소값