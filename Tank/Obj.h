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
	virtual void		Initialize(void) PURE;
	virtual int			Update(void) PURE;
	virtual void		Late_Update(OBJLIST* _objlist) PURE;
	virtual void		Render(HDC _hDC) PURE;
	virtual void		Release(void) PURE;

	//��� �Լ�(Public)
public:
	void				Move_Pos(float _x, float _y);			// �߽���ǥ �Է�
	void				Update_Rect(void);			    // �߽���ǥ�� Body �� �Է�
	float				Update_Radian(POINT _focus);			// Ÿ���� ��ǥ�� ������ ��ȯ�մϴ�.
	
public: // ���� ȸ�� �Լ�(ȸ�� �ӵ�)
	void				Rotation_Radian(int _speed);
						
public: //������ ���� �Լ�
	const RECT&					Get_Body(void) const { return m_Body; }
	const INFO&					Get_Info(void) const { return m_Info; }
	const OBJID::ID&			Get_Type(void) const { return m_Type; }
	const OBJECT::DIRECTION&	Get_Direction(void) const { return m_Dir; }
	const float					Get_Radian(void) const { return m_Radian; }
	const float					Get_Speed(void) const { return m_Speed; }

	const bool					Get_Dead(void)	const { return m_Dead; } // ��� ���� ��ȯ

	void						Set_Size(const long _cx, const long _cy);
	void						Set_Point(const POINT& _src, OBJECT::POINT_TYPE _ptype);	// POINT �迭 ����(������ POINT��, ������ POINT�� �ε��� )
	void						Set_Dir(OBJECT::DIRECTION _dir) { m_Dir = _dir; }
	void						Set_Radian(float _rad) { m_Radian = _rad; }
	void						Set_Speed(float _speed) { m_Speed = _speed; }

	void						Set_Type(OBJID::ID _type) { m_Type = _type; }
	void						Set_Dead(bool _bool) { m_Dead = _bool; } // ��� ���� 

	void						Add_PosX(float _fX);
	void						Add_PosY(float _fY);
	void						Add_Speed(float _speed);

	virtual void				Set_Collision() { Set_Dead(true); }; // �浹 �� ó��
	virtual bool				Check_Type(CObj* _opponent); // Ÿ�� ��
	virtual void				Copy_Data(CObj* _target); // ������ �ű��

	bool						Screen_Body_Check();

	//��� ����
protected:
	RECT						m_Body;
	INFO						m_Info;
	OBJID::ID					m_Type;
	POINT						m_Point[OBJECT::POINT_TYPE_END];
	OBJECT::DIRECTION			m_Dir;
	float						m_Radian;
	float						m_Speed;

	bool						m_Dead = false; // ��� ����
};

#endif // !__OBJ_H__


