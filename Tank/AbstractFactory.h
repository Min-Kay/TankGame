#pragma once

#include "Obj.h"
#include "Enum.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(T* t)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Move_Pos(dynamic_cast<CObj*>(t)->Get_Info().X, dynamic_cast<CObj*>(t)->Get_Info().Y);
		pObj->Set_Size(dynamic_cast<CObj*>(t)->Get_Info().Width, dynamic_cast<CObj*>(t)->Get_Info().Height);

		return pObj;
	}


	static CObj*		Create(float _fX, float _fY, float _fCX, float _fCY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Move_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, float _fCX, float _fCY, int _Selection)
	{
		CObj* pObj = new T;
		pObj->Set_Speed(_Selection);
		pObj->Move_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(POINT _aim, OBJECT::POINT_TYPE _ptype, float _rad)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Move_Pos(long(_aim.x), long(_aim.y));
		pObj->Set_Radian(_rad);

		return pObj;
	}

};

