#pragma once
#include "Stage.h"
class StageOne :
	public Stage
{
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;


public:
	virtual void Init_Patterns(); // m_Patterns 리스트 초기화 (Stage)
	void Release_Patterns(); // m_Patterns 리스트 해제 (Stage)

public:
	void Set_MonsterList(int i); // m_ObjList[OBJID::MONSTER]와 m_Patterns[i]를 연결

public:
	virtual void Pattern(); //몬스터 소환 및 주기 관리 (Stage)

public:
	void Set_Result(GAMERESULT::RESULT _result); // 게임 실행 관리 (Stage)
	const GAMERESULT::RESULT& Get_Result() const { return m_Result; }; // 결과 반환(Stage) 

public:
	virtual void Init_ObjList(); // m_ObjList 리스트 초기화
	virtual void Release_ObjList(); // m_ObjList 리스트 해제
};

