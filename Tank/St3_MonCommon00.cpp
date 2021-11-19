#include "stdafx.h"
#include "St3_MonCommon00.h"
#include "Obj.h"
#include  "CollisionMgr.h"

St3_MonCommon00::St3_MonCommon00()
	: m_Bullet(nullptr)
	, m_Range(NULL)
	, m_Move(MOVEMENT::MOVEMENT_STATUS_STOP)
	, m_Cooltime(NULL)
{
}


St3_MonCommon00::~St3_MonCommon00()
{
}

void St3_MonCommon00::Initialize(void)
{
	m_Info.X = St3_MON_COMMON_RESPON_X;
	m_Info.Y = St3_MON_COMMON_RESPON_Y;
	m_Info.Width =	St3_MON_COMMON_WIDTH;
	m_Info.Height = St3_MON_COMMON_HEIGHT;
	m_Speed =		St3_MON_COMMON_SPEED;
	m_Type =		OBJID::MONSTER;
	m_Point[OBJECT::POINT_TYPE_TARGET] = {(long)St3_MON_COMMON_RESPON_X,(long)St3_MON_COMMON_RESPON_Y };
	m_Range = St3_MON_COMMON_RANGE;
	m_Move = MOVEMENT::MOVEMENT_STATUS_END;
}

int St3_MonCommon00::Update(void)
{
	

	switch (m_Move)
	{
	case MOVEMENT::MOVEMENT_STATUS_STOP:
		break;

	case MOVEMENT::MOVEMENT_STATUS_TARGET:
		Move_To_Point(m_Point[OBJECT::POINT_TYPE_TARGET]);
		m_Move = MOVEMENT::MOVEMENT_STATUS_END;
		break;

	case MOVEMENT::MOVEMENT_STATUS_POINT:
		Update_Radian(m_Point[OBJECT::POINT_TYPE_AIM]);
		m_Info.X += m_Speed*cosf(m_Radian); //x 이동
		m_Info.Y += m_Speed*sinf(m_Radian); //y 이동
		break;

	case MOVEMENT::MOVEMENT_STATUS_CIRCLE:
		break;

	case MOVEMENT::MOVEMENT_STATUS_REBOUND:
		if (m_Cooltime >= GetTickCount())
			Move_Opposite(int(m_Speed+3));
		else
			m_Move = MOVEMENT::MOVEMENT_STATUS_END;
		break;

	case MOVEMENT::MOVEMENT_STATUS_END:
		break;
	default:
		break;
	} 


	Update_Rect();

	if(m_Dead)
		return OBJ_DEAD;
	
	return OBJ_NOEVENT;
}

void St3_MonCommon00::Late_Update(OBJLIST* _objlist)
{
	if(m_Move == MOVEMENT::MOVEMENT_STATUS_END)								//END 처리는 Update 에서해준다
		m_Move = Check_Move(_objlist[OBJID::PLAYER].front());  //이동상태 정하기

}

void St3_MonCommon00::Render(HDC _hDC)
{
	Ellipse(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void St3_MonCommon00::Release(void)
{
}

void St3_MonCommon00::Rebound()
{
	if (m_Cooltime >= GetTickCount())
		Move_Opposite(m_Speed + 10);
	else
		m_Move = MOVEMENT::MOVEMENT_STATUS_END;
}

MOVEMENT::MOVEMENT_STATUS St3_MonCommon00::Check_Move(CObj* _src)
{

	if (CCollisionMgr::Check_Sphere(this, _src)) // 1순위 몸체 충돌
	{
		m_Cooltime = GetTickCount()+500;

		m_Point[OBJECT::POINT_TYPE_TARGET] = { (long)_src->Get_Info().X,(long)_src->Get_Info().Y };
		return MOVEMENT::MOVEMENT_STATUS_REBOUND;
	}

	if (CCollisionMgr::Check_Sphere(this, _src, m_Range)) // 2순위 범위 충돌
	{
		m_Point[OBJECT::POINT_TYPE_TARGET] = { (long)_src->Get_Info().X,(long)_src->Get_Info().Y };
		return MOVEMENT::MOVEMENT_STATUS_TARGET;
	}

	return MOVEMENT::MOVEMENT_STATUS_END;
}

void St3_MonCommon00::Move_Opposite(int _speed)
{
	m_Info.X -= _speed*cosf(m_Radian); //x 이동
	m_Info.Y -= _speed*sinf(m_Radian); //y 이동
}

void St3_MonCommon00::Move_To_Point(POINT _dst)
{
	Update_Radian(_dst);
	m_Info.X += m_Speed*cosf(m_Radian); //x 이동
	m_Info.Y += m_Speed*sinf(m_Radian); //y 이동
}
