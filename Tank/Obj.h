#ifndef __OBJ_H__
#define __OBJ_H__

#include "Enum.h"

class CObj
{
public:
	explicit CObj();
	virtual ~CObj();

	//�⺻ �Լ�
public:
	virtual void		Initialize(void) = 0;
	virtual int			Update(void) = 0;
	virtual void		Late_Update(void) = 0;
	virtual void		Render(HDC _hDC) = 0;
	virtual void		Release(void) = 0;

	//��� �Լ�(Public)
public:
	virtual void				Move_Pos(float _x, float _y);			// �߽���ǥ �Է�
	virtual void				Update_Rect(void);						// �߽���ǥ�� Body �� �Է�

	//������ ���� �Լ�
public:
	virtual const RECT&			Get_Body(void) const { return m_Body; }
	virtual const INFO&			Get_Info(void) const { return m_Info; }
	virtual const OBJECT::OBJECT_TYPE&	Get_Type(void) const { return m_Type; }
	virtual const OBJECT::DIRECTION&	Get_Direction(void) const { return m_Dir; }
	virtual const float			Get_Radian(void) const { return m_Radian; }
	virtual const float			Get_Speed(void) const { return m_Speed; }
	virtual const bool			Get_Vaild(void) const { return m_Vaild; }

	virtual void				Set_Hp(int _damage) { m_Info.Hp += _damage; }		// �����Է½� ����
	virtual void				Set_Size(const long _cx, const long _cy);
	virtual void				Set_m_Point(const POINT& _src, OBJECT::POINT_TYPE _ptype);	// POINT �迭 ����(������ POINT��, ������ POINT�� �ε��� )
	virtual void				Set_Dir(OBJECT::DIRECTION _dir) { m_Dir = _dir; }
	virtual void				Set_Radian(float _rad) { m_Radian = _rad; }
	virtual void				Set_Speed(float _speed) { m_Speed = _speed; }
	virtual void				Set_Vaild(bool _vaild) { m_Vaild = _vaild; }

	virtual bool				Get_Dead();
	virtual void				Set_Dead();


	//��� �Լ�(Private)
protected:

	//��� ����
protected:
	RECT				m_Body;
	INFO				m_Info; 
	OBJECT::OBJECT_TYPE			m_Type;
	POINT				m_Point[OBJECT::POINT_TYPE_END];
	OBJECT::DIRECTION			m_Dir;
	float				m_Radian;
	float				m_Speed;
	bool				m_Vaild;
	bool				m_Dead; // ��� ����
};

#endif // !__OBJ_H__

