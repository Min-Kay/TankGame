#include "stdafx.h"
#include "St3_CollisionMgr.h"
#include "St3_BossMonster.h"

bool St3_CollisionMgr::Check_Blocking(CObj* _dst, OBJLIST _src)
{
    for (auto i : _src)
    {
        if (Check_Sphere(_dst, i))
        {
            float Dis = Check_Distance(_dst, i);
            float Rad = (_dst->Get_Info().Width + i->Get_Info().Width) * 0.5f;

            float temp = Rad - Dis;

            float Radian = atan2(i->Get_Info().X, i->Get_Info().Y);

            //float Radian = acosf(i->Get_Info().X /Rad);
            //if (i->Get_Info().Y > _dst->Get_Info().Y)
            //    Radian -= 2 * PI - Radian;

            i->Move_Pos(
                i->Get_Info().X+ temp*cosf(Radian),
                i->Get_Info().Y + temp * sinf(Radian)
            );

        }
    }
    return false;
}

bool St3_CollisionMgr::Check_Blocking(OBJLIST _dst, OBJLIST _src)
{
    for (auto j : _dst)
    {
        for (auto i : _src)
        {
            if ( j != i&&Check_Sphere(j, i))
            {
                float Dis = Check_Distance(j, i);
                float Rad = (j->Get_Info().Width + i->Get_Info().Width) * 0.5f;

                float temp = Rad - Dis;

                float Radian = atan2(i->Get_Info().X, i->Get_Info().Y);

                //float Radian = acosf(i->Get_Info().X /Rad);
                //if (i->Get_Info().Y > _dst->Get_Info().Y)
                //    Radian -= 2 * PI - Radian;

                i->Move_Pos(
                    i->Get_Info().X + temp * cosf(Radian),
                    i->Get_Info().Y + temp * sinf(Radian)
                );

            }
        }
    }
    return false;
}

float St3_CollisionMgr::Check_Distance(CObj* _dst, CObj* _src)
{
    if (_src)
    {
        float Width = (_dst->Get_Info().X - _src->Get_Info().X);
        float Height = (_dst->Get_Info().Y - _src->Get_Info().Y);

        return sqrt(Width * Width + Height * Height);
    }
}

void St3_CollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (!Dest->Check_Type(Src) && IntersectRect(&rc, &(Dest->Get_Body()), &(Src->Get_Body())))
			{
                if (Src->Get_Dead() == false)
                {
                    if (Dest->Get_Type() == OBJID::END)
                    {
                        if (static_cast<St3_BossMonster*>(Dest)->Get_Hp() <= 0)
                            Dest->Set_Dead(true);
                        else
                            static_cast<St3_BossMonster*>(Dest)->Set_Hp(-1);

                        Src->Set_Dead(true);
                    }
                    else
                    {
					    Dest->Set_Dead(true);
                    }
                }
			}
		}
	}
}

//bool St3_CollisionMgr::Collision_Sphere_Rect(list<CObj*> _sphere, list<CObj*> rect)
//{
//
//	for (auto& Dest : _sphere)
//	{
//		for (auto& Src : rect)
//		{
//			if (!Dest->Check_Type(Src) && IntersectRect(&rc, &(Dest->Get_Body()), &(Src->Get_Body())))
//			{
//				if (Src->Get_Dead() == false)
//					Dest->Set_Dead(true);
//				Src->Set_Dead(true);
//			}
//		}
//	}
//}

bool St3_CollisionMgr::Check_Blocking_Push(OBJLIST _dst, OBJLIST _src)
{
	RECT rc;
	for (auto j : _dst)
	{
		for (auto i : _src)
		{
			if (j != i&&IntersectRect(&rc,&j->Get_Body(),&i->Get_Body()))
			{
				float Xex = rc.right - rc.left;
				float Yex = rc.top - rc.bottom;

				//오른충돌일때
                if (j->Get_Body().right > i->Get_Body().left)
                {
                    i->Move_Pos(i->Get_Info().X + Xex, i->Get_Info().Y);
                    i->Update_Rect();
                }
					
				//오른쪽 충돌일때
                if (j->Get_Body().left < i->Get_Body().right)
                {
					i->Move_Pos(i->Get_Info().X, i->Get_Info().Y);
                    i->Update_Rect();
                }

				//상단 충돌일때
                if (j->Get_Body().top < i->Get_Body().bottom)
                {
					i->Move_Pos(i->Get_Info().X, i->Get_Info().Y-Yex);
                    i->Update_Rect();
                }

				//하단 충돌일때
                if (j->Get_Body().bottom > i->Get_Body().top)
                {
					i->Move_Pos(i->Get_Info().X + Xex, i->Get_Info().Y+Yex);
                    i->Update_Rect();
                }
			}
		}
	}
	return false;
}

bool St3_CollisionMgr::Check_Blocking_Push(RECT* _dst, RECT* _src)
{
    RECT rc;
 for( int j=0; j<15 ; j++)
    {
        for (int i = 0; i < 15 ; i++)
        {
            if (j != i && IntersectRect(&rc, &_dst[j], &_src[i]))
            {
                float Xex = rc.right - rc.left;
                float Yex = rc.top - rc.bottom;

                //오른충돌일때
                if (_dst[j].right > _src[i].left)
                {
                    _src[i].left += Xex;
                }

                //오른쪽 충돌일때
           
                if (_dst[j].left < _src[i].right)
                {
                    _src[i].right -= Xex;
                }

                //상단 충돌일때
                if (_dst[j].top < _src[i].bottom)
                {
                    _src[i].bottom -= Yex;
                }

                //하단 충돌일때
                if (_dst[j].bottom > _src[i].top)
                {
                    _src[i].top += Yex;
                }

    }
            }
        }
    return false;
}
