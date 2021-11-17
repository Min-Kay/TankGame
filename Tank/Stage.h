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
	virtual void Release_Patterns(); // m_Patterns 리스트 해제 (Stage)

public:
	virtual void Init_ObjList()PURE; // m_ObjList 리스트 초기화
	void Update_ObjList(); // m_ObjList 리스트 업데이트 
	void LateUpdate_ObjList(); // m_ObjList 리스트 라스트 업데이트
	void Render_ObjList(); // m_ObjList 리스트 렌더
	virtual void Release_ObjList(); // m_ObjList 리스트 해제

public:
	void Add_MonsterList(CObj* _monster);// m_ObjList[OBJID::MONSTER]에 m_Patterns에서 소환하고자하는 몬스터 추가

public:
	virtual void Pattern()PURE; //몬스터 소환 및 주기 관리 (Stage)

public:
	void Set_Result(GAMERESULT::RESULT _result) { m_Result = _result; } // 게임 실행 관리 (Stage)
	const GAMERESULT::RESULT& Get_Result() const { return m_Result; }; // 결과 반환(Stage) 

public:
	const OBJLIST& Get_PlayerList() const { return m_ObjList[OBJID::PLAYER]; }; // 플레이어 리스트 반환
	const OBJLIST& Get_MonsterList() const { return m_ObjList[OBJID::MONSTER]; }; // 몬스터 리스트 반환 
	const OBJLIST& Get_MissileList() const { return m_ObjList[OBJID::MISSILE]; }; // 투사체 리스트 반환

public:
	void Set_Clear(bool _bool) { isClear = _bool; } // 모든 패턴 수행 여부
	void Goto_Menu(); // 메뉴로 돌아가기
	void Release_Game(); // 게임 공통 릴리스 작업 수행

public:
	void Check_GameState(); // 현재 게임 상황 확인 (승패)
	void Show_Win_Lose();

protected:
	OBJLIST m_ObjList[OBJID::END]; // OBJID에 해당하는 소환체 관리
	list <OBJLIST> m_Patterns; // 패턴에 따른 몬스터 배열 호출 순서 관리
	GAMERESULT::RESULT m_Result = GAMERESULT::RESULT::NONE; //결과값에 따른 처리
	bool		isClear; // 모든 패턴을 성공적으로 수행 했는지에 대한 결과값
};

