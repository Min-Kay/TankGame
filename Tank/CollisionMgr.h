#pragma once

class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src);
	static GAME::GAMEID	Collision_Mouse(RECT& mouse, list<CObj*> _Src);
	static void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src);
	static bool Collision_Mouse_Box(RECT& mouse, RECT& box);
	static void	Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src);
	static bool Check_Rect(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight);
	static bool	Check_Sphere(CObj* pDest, CObj* pSrc, int _range = 0);


	static void Collision_Push(list<CObj*> _Dest, list<CObj*> _Src);
	static void Collision_Bounce(list<CObj*> _Dest, list<CObj*> _Src);
};

