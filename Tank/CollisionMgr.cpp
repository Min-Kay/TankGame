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
				Dest->Set_Collision();
				Src->Set_Collision();
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
				Dest->Set_Collision();
				Src->Set_Collision();
			}
		}
	}
}


bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight)
{
	float		fWidth = abs(pDest->Get_Info().X - pSrc->Get_Info().X);
	float		fHeight = abs(pDest->Get_Info().Y - pSrc->Get_Info().Y);

	float		fCX = (pDest->Get_Info().Width + pSrc->Get_Info().Width) * 0.5f;
	float		fCY = (pDest->Get_Info().Height + pSrc->Get_Info().Height) * 0.5f;

	if (fCX > fWidth&& fCY > fHeight)
	{
		*_pWidth = fCX - fWidth;
		*_pHeight = fCY - fHeight;

		return true;
	}

	return false;
}


void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			float	fWidth = 0.f, fHeight = 0.f;

			if (Check_Rect(Dest, Src, &fWidth, &fHeight))
			{
				// 상 하 충돌
				if (fWidth > fHeight)
				{
					if (Dest->Get_Info().X < Src->Get_Info().Y)
					{
						Src->Add_PosX(fHeight);
					}
					else
						Src->Add_PosY(-fHeight);
				}

				//  좌 우 충돌
				else
				{
					if (Dest->Get_Info().X < Src->Get_Info().X)
					{
						Src->Add_PosX(fWidth);
					}
					else
						Src->Add_PosY(-fWidth);
				}
			}
		}
	}
}


void CCollisionMgr::Collision_Push(list<CObj*> _Dest, list<CObj*> _Src) 
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dest->Get_Body()), &(Src->Get_Body()))) {
				
				POINT size;
				size.x = rc.right - rc.left;
				size.y = rc.bottom - rc.top;

				float up = abs(Dest->Get_Body().top - Src->Get_Body().bottom);
				float down = abs(Dest->Get_Body().bottom - Src->Get_Body().top);
				float left = abs(Dest->Get_Body().left - Src->Get_Body().right);
				float right = abs(Dest->Get_Body().right - Src->Get_Body().left);

				if (up < left && up < right && up < down)
				{
					Dest->Add_PosY(size.y);
				}
				
				if (down < left && down < right && down < up)
				{
					Dest->Add_PosY(-size.y);
				}
				
				if (left < down && left < right && left < up)
				{
					Dest->Add_PosX(size.x);
				}
				
				if (right < left && right < down && right < up)
				{
					
					Dest->Add_PosX(-size.x);
				}
			}
		}
	}
}


void CCollisionMgr::Collision_Bounce(list<CObj*> _Dest, list<CObj*> _Src) // Bullet 튕기기용
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Dest == Src)
				continue; 

			if (IntersectRect(&rc, &(Dest->Get_Body()), &(Src->Get_Body()))) 
			{
				float up = abs(Dest->Get_Body().top - Src->Get_Body().bottom);
				float down = abs(Dest->Get_Body().bottom - Src->Get_Body().top);
				float left = abs(Dest->Get_Body().left - Src->Get_Body().right);
				float right = abs(Dest->Get_Body().right - Src->Get_Body().left);

				int radianToAngle = (int)(Dest->Get_Radian() * 180.f / PI) % 360 ;

				if (up < left && up < right && up < down)
				{
					float radian = (360 - radianToAngle) * PI / 180.f;
					Dest->Set_Radian(radian);
				}
				else if(down < left && down < right && down < up)
				{
					float radian = (360 - radianToAngle) * PI / 180.f;
					Dest->Set_Radian(radian);
				}
				else if (left < down && left < right && left < up)
				{
					float radian = (180 - radianToAngle) * PI / 180.f;
					Dest->Set_Radian(radian);
				}
				else if (right < left && right < down && right < up)
				{
					float radian = (180 - radianToAngle) * PI / 180.f;
					Dest->Set_Radian(radian);
				}
			}
		}
	}
}
