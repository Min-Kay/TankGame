#pragma once

class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src);
	static int	Collision_Mouse(RECT& mouse, list<CObj*> _Src);
	static void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src);
	static bool Collision_Mouse_Box(RECT& mouse, RECT& box);

private:
	static bool Check_Sphere(CObj* pDest, CObj* pSrc);

};

