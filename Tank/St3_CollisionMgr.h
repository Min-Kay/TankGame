#pragma once

#include "CollisionMgr.h"
#include "Obj.h"

class St3_CollisionMgr : public CCollisionMgr
{
public:
	static bool		Check_Blocking(CObj* _dst, OBJLIST _src);
	static bool		Check_Blocking(OBJLIST _dst, OBJLIST _src);
	static bool		Check_Blocking_Push(OBJLIST _dst, OBJLIST _src);
	static bool		Check_Blocking_Push(RECT* _dst, RECT* _src);
	//static bool		Check_Blocking_Push_Rect(OBJLIST _dst, OBJLIST _src);

public:
	static float	Check_Distance(CObj* _dst, CObj* _src);
	static void		Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src);

	static bool		Collision_Sphere_Rect(list<CObj*> _Dest, list<CObj*> _Src);

public:
	static int		m_CoolTime;

};

