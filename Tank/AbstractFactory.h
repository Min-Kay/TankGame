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

	static CObj*		Create(T* t) // 패턴 활용을 위한 데이터 복사 용도
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

	static CObj*		Create(float _fX, float _fY, float _fCX, float _fCY, GAME::GAMEID _Selection) // Click용
	{
		CObj* pObj = new T;
		pObj->Set_Speed(int(_Selection));
		pObj->Move_Pos(_fX, _fY);
		pObj->Set_Size(long(_fCX), long(_fCY));
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(POINT _aim, OBJECT::POINT_TYPE _ptype, float _rad) // 투사체 용
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Move_Pos(float(_aim.x), float(_aim.y));
		pObj->Set_Radian(_rad);

		return pObj;
	}


	static CObj*		Create(POINT _aim, OBJECT::POINT_TYPE _ptype, float _rad, OBJID::ID _motherType) // 투사체 생성자의 타입을 가져오기 위함
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Move_Pos(float(_aim.x), float(_aim.y));
		pObj->Set_Radian(_rad);
		pObj->Set_Type(_motherType);

		return pObj;
	}

	static CObj*		Create(POINT _aim, float _rad, OBJID::ID _motherType) // 투사체에게 입력된 좌표값을 통한 생성 및 각도, 모객체의 타입으로 설정
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Move_Pos(float(_aim.x), float(_aim.y));
		pObj->Set_Radian(_rad);
		pObj->Set_Type(_motherType);
		pObj->Update_Rect(); // 생성 시점이 Late_Update 라 Late_Update 때 갱신된 정보를 토대로 Update_Rect가 실행되어있지않아 삭제될 수 있어 한번더 갱신

		return pObj;
	}



};

