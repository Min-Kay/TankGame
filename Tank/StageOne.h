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
	virtual void Init_Patterns(); // m_Patterns ����Ʈ �ʱ�ȭ (Stage)
	void Release_Patterns(); // m_Patterns ����Ʈ ���� (Stage)

public:
	void Set_MonsterList(int i); // m_ObjList[OBJID::MONSTER]�� m_Patterns[i]�� ����

public:
	virtual void Pattern(); //���� ��ȯ �� �ֱ� ���� (Stage)

public:
	void Set_Result(GAMERESULT::RESULT _result); // ���� ���� ���� (Stage)
	const GAMERESULT::RESULT& Get_Result() const { return m_Result; }; // ��� ��ȯ(Stage) 

public:
	virtual void Init_ObjList(); // m_ObjList ����Ʈ �ʱ�ȭ
	virtual void Release_ObjList(); // m_ObjList ����Ʈ ����
};

