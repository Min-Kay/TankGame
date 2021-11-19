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

	static CObj*		Create(T* t) // ���� Ȱ���� ���� ������ ���� �뵵
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Copy_Data(static_cast<CObj*>(t));
		return pObj;
	}


	static CObj*		Create(float _fX, float _fY, float _fCX, float _fCY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Move_Pos(_fX, _fY);
		pObj->Set_Size(long(_fCX), long(_fCY));

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, float _fCX, float _fCY, float _rad)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Move_Pos(_fX, _fY);
		pObj->Set_Size(long(_fCX), long(_fCY));
		pObj->Set_Radian(_rad);

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, float _fCX, float _fCY, GAME::GAMEID _Selection) // Click��
	{
		CObj* pObj = new T;
		pObj->Set_Speed(int(_Selection));
		pObj->Move_Pos(_fX, _fY);
		pObj->Set_Size(long(_fCX), long(_fCY));
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(POINT _aim, OBJECT::POINT_TYPE _ptype, float _rad) // ����ü ��
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Move_Pos(float(_aim.x), float(_aim.y));
		pObj->Set_Radian(_rad);

		return pObj;
	}


	static CObj*		Create(POINT _aim, OBJECT::POINT_TYPE _ptype, float _rad, OBJID::ID _motherType) // ����ü �������� Ÿ���� �������� ����
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Move_Pos(float(_aim.x), float(_aim.y));
		pObj->Set_Radian(_rad);
		pObj->Set_Type(_motherType);

		return pObj;
	}

	static CObj*		Create(POINT _aim, float _rad, OBJID::ID _motherType) // ����ü���� �Էµ� ��ǥ���� ���� ���� �� ����, ��ü�� Ÿ������ ����
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Move_Pos(float(_aim.x), float(_aim.y));
		pObj->Set_Radian(_rad);
		pObj->Set_Type(_motherType);
		pObj->Update_Rect(); // ���� ������ Late_Update �� Late_Update �� ���ŵ� ������ ���� Update_Rect�� ����Ǿ������ʾ� ������ �� �־� �ѹ��� ����

		return pObj;
	}



};

