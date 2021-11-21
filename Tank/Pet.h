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
	virtual void				Set_Collision() { --m_Hp;  }; // 충돌 시 처리
	virtual bool				Check_Type(CObj* _opponent); // 타입 비교
	virtual void				Copy_Data(CObj* _target); // 데이터 옮기기

	void						Set_Angle_To_Target(POINT dest, POINT src);
	float						Calc_Distance(POINT dest, POINT src);
protected:
	CObj*						m_target = nullptr;
	int							m_Hp;
	float						m_Angle; 

	POINT						m_PetInfo{}, m_TargetInfo{};
};

