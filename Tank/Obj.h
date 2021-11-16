#ifndef __OBJ_H__
#define __OBJ_H__

#include "Enum.h"

class CObj
{
public:
	explicit CObj();
	virtual ~CObj();

	//기본 함수
public:
	virtual void		Initialize(void) = 0;
	virtual int			Update(void) = 0;
	virtual void		Late_Update(void) = 0;
	virtual void		Render(HDC _hDC) = 0;
	virtual void		Release(void) = 0;

	//멤버 함수(Public)
public:
	virtual void				Move_Pos(float _x, float _y);			// 중심좌표 입력
	virtual void				Update_Rect(void);						// 중심좌표로 Body 값 입력

	//데이터 관리 함수
public:
	virtual const RECT&			Get_Body(void) const { return m_Body; }
	virtual const INFO&			Get_Info(void) const { return m_Info; }
	virtual const OBJECT::OBJECT_TYPE&	Get_Type(void) const { return m_Type; }
	virtual const OBJECT::DIRECTION&	Get_Direction(void) const { return m_Dir; }
	virtual const float			Get_Radian(void) const { return m_Radian; }
	virtual const float			Get_Speed(void) const { return m_Speed; }
	virtual const bool			Get_Vaild(void) const { return m_Vaild; }

	virtual void				Set_Hp(int _damage) { m_Info.Hp += _damage; }		// 음수입력시 빼기
	virtual void				Set_Size(const long _cx, const long _cy);
	virtual void				Set_m_Point(const POINT& _src, OBJECT::POINT_TYPE _ptype);	// POINT 배열 수정(수정할 POINT값, 수정될 POINT의 인덱스 )
	virtual void				Set_Dir(OBJECT::DIRECTION _dir) { m_Dir = _dir; }
	virtual void				Set_Radian(float _rad) { m_Radian = _rad; }
	virtual void				Set_Speed(float _speed) { m_Speed = _speed; }
	virtual void				Set_Vaild(bool _vaild) { m_Vaild = _vaild; }

	virtual bool				Get_Dead();
	virtual void				Set_Dead();


	//멤버 함수(Private)
protected:

	//멤버 변수
protected:
	RECT				m_Body;
	INFO				m_Info; 
	OBJECT::OBJECT_TYPE			m_Type;
	POINT				m_Point[OBJECT::POINT_TYPE_END];
	OBJECT::DIRECTION			m_Dir;
	float				m_Radian;
	float				m_Speed;
	bool				m_Vaild;
	bool				m_Dead; // 사망 판정
};

#endif // !__OBJ_H__


