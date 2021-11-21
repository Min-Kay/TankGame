#pragma once
#include "stdafx.h"
#include "Obj.h"

class CPet :
	public CObj
{
public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		Late_Update(OBJLIST* _objlist);
	virtual void		Render(HDC _hDC);
	virtual void		Release(void);

public:
	virtual void				Set_Collision() { --m_Hp;  }; // �浹 �� ó��
	virtual bool				Check_Type(CObj* _opponent); // Ÿ�� ��
	virtual void				Copy_Data(CObj* _target); // ������ �ű��

	void						Set_Angle_To_Target(POINT dest, POINT src);
	float						Calc_Distance(POINT dest, POINT src);
protected:
	CObj*						m_target = nullptr;
	int							m_Hp;
	float						m_Angle; 

	POINT						m_PetInfo{}, m_TargetInfo{};
};

