#pragma once
#include "Stage.h"
class StageFour :
	public Stage
{
public:
	StageFour();
	~StageFour();

public:
	// 클래스 생명주기 (Main)
	virtual void Initialize()  override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void Init_Patterns() override; // m_Patterns 리스트 초기화 (Stage)

public:
	virtual void Init_ObjList() override; // m_ObjList 리스트 초기화

public:
	virtual void Pattern() override; //몬스터 소환 및 주기 관리 (Stage)


private:
	int selected_Pattern = 0;
	int play_Count = 0;
	DWORD	spawn_Timer = GetTickCount(); 
};

