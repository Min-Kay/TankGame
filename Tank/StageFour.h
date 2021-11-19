#pragma once
#include "Stage.h"
class StageFour :
	public Stage
{
public:
	StageFour();
	~StageFour();

public:
	// Ŭ���� �����ֱ� (Main)
	virtual void Initialize()  override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void Init_Patterns() override; // m_Patterns ����Ʈ �ʱ�ȭ (Stage)

public:
	virtual void Init_ObjList() override; // m_ObjList ����Ʈ �ʱ�ȭ

public:
	virtual void Pattern() override; //���� ��ȯ �� �ֱ� ���� (Stage)


private:
	int selected_Pattern = 0;
	int play_Count = 0;
	DWORD	spawn_Timer = GetTickCount(); 
};

