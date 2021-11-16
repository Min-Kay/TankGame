#pragma once
#include "Menu.h"
#include "Enum.h"

class Stage :
	public Menu
{
public:
	// 클래스 생명주기 (Main)
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

public:
	virtual void Init_Patterns() PURE; // m_Patterns 리스트 초기화 (Stage)
	void Release_Patterns(); // m_Patterns 리스트 해제 (Stage)

public:
	void Set_MonsterList(int i); // m_ObjList[OBJID::MONSTER]와 m_Patterns[i]를 연결

public:
	virtual void Pattern()PURE; //몬스터 소환 및 주기 관리 (Stage)

public:
	void Set_Result(GAMERESULT::RESULT _result); // 게임 실행 관리 (Stage)
	const GAMERESULT::RESULT& Get_Result() const { return m_Result; }; // 결과 반환(Stage) 

public:
	virtual void Init_ObjList()PURE; // m_ObjList 리스트 초기화
	virtual void Release_ObjList()PURE; // m_ObjList 리스트 해제

public:
	void Goto_Menu();
	void Release_Game();

protected:
	list <OBJLIST> m_Patterns; // 패턴에 따른 몬스터 배열 호출 순서 관리
	GAMERESULT::RESULT m_Result = GAMERESULT::RESULT::NONE; //결과값에 따른 처리

};

