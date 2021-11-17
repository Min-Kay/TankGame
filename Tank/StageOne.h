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
	virtual void Init_Patterns(); // m_Patterns ����Ʈ �ʱ�ȭ (Stage)

public:
	virtual void Pattern(); //���� ��ȯ �� �ֱ� ���� (Stage)

public:
	virtual void Init_ObjList(); // m_ObjList ����Ʈ �ʱ�ȭ

private:
	DWORD m_CoolTime;

};

