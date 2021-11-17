#pragma once
#include "Stage.h"
class StageOne :
	public Stage
{

public:
	StageOne();
	~StageOne();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void Init_Patterns(); // m_Patterns 리스트 초기화 (Stage)

public:
	virtual void Pattern(); //몬스터 소환 및 주기 관리 (Stage)

public:
	virtual void Init_ObjList(); // m_ObjList 리스트 초기화

private:
	DWORD m_CoolTime;

};

