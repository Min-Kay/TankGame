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
	virtual void		Initialize(void) PURE;
	virtual int			Update(void) PURE;
	virtual void		Late_Update(OBJLIST* _objlist) PURE;
	virtual void		Render(HDC _hDC) PURE;
	virtual void		Release(void) PURE;

	//멤버 함수(Public)
public:
	void				Move_Pos(float _x, float _y);			// 중심좌표 입력
	void				Update_Rect(void);			    // 중심좌표로 Body 값 입력
	float				Update_Radian(POINT _focus);			// 타겟의 좌표로 각도를 반환합니다.
	
public: // 지속 회전 함수(회전 속도)
	void				Rotation_Radian(int _speed);
						
public: //데이터 관리 함수
	const RECT&					Get_Body(void) const { return m_Body; }
	const INFO&					Get_Info(void) const { return m_Info; }
	const OBJID::ID&			Get_Type(void) const { return m_Type; }
	const OBJECT::DIRECTION&	Get_Direction(void) const { return m_Dir; }
	const float					Get_Radian(void) const { return m_Radian; }
	const float					Get_Speed(void) const { return m_Speed; }

	const bool					Get_Dead(void)	const { return m_Dead; } // 사망 여부 반환

	void						Set_Size(const long _cx, const long _cy);
	void						Set_Point(const POINT& _src, OBJECT::POINT_TYPE _ptype);	// POINT 배열 수정(수정할 POINT값, 수정될 POINT의 인덱스 )
	void						Set_Dir(OBJECT::DIRECTION _dir) { m_Dir = _dir; }
	void						Set_Radian(float _rad) { m_Radian = _rad; }
	void						Set_Speed(float _speed) { m_Speed = _speed; }

	void						Set_Type(OBJID::ID _type) { m_Type = _type; }
	void						Set_Dead(bool _bool) { m_Dead = _bool; } // 사망 세팅 

	void						Add_PosX(float _fX);
	void						Add_PosY(float _fY);
	void						Add_Speed(float _speed);

	virtual void				Set_Collision() { Set_Dead(true); }; // 충돌 시 처리
	virtual bool				Check_Type(CObj* _opponent); // 타입 비교
	virtual void				Copy_Data(CObj* _target); // 데이터 옮기기

	bool						Screen_Body_Check();

	//멤버 변수
protected:
	RECT						m_Body;
	INFO						m_Info;
	OBJID::ID					m_Type;
	POINT						m_Point[OBJECT::POINT_TYPE_END];
	OBJECT::DIRECTION			m_Dir;
	float						m_Radian;
	float						m_Speed;

	bool						m_Dead = false; // 사망 여부
};

#endif // !__OBJ_H__


