#pragma once
#include "Menu.h"
#include "Enum.h"

class Stage :
	public Menu
{
public:
	// Ŭ���� �����ֱ� (Main)
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

public:
	virtual void Init_Patterns() PURE; // m_Patterns ����Ʈ �ʱ�ȭ (Stage)
	void Release_Patterns(); // m_Patterns ����Ʈ ���� (Stage)

public:
	void Set_MonsterList(int i); // m_ObjList[OBJID::MONSTER]�� m_Patterns[i]�� ����

public:
	virtual void Pattern()PURE; //���� ��ȯ �� �ֱ� ���� (Stage)

public:
	void Set_Result(GAMERESULT::RESULT _result); // ���� ���� ���� (Stage)
	const GAMERESULT::RESULT& Get_Result() const { return m_Result; }; // ��� ��ȯ(Stage) 

public:
	virtual void Init_ObjList()PURE; // m_ObjList ����Ʈ �ʱ�ȭ
	virtual void Release_ObjList()PURE; // m_ObjList ����Ʈ ����

public:
	void Goto_Menu();
	void Release_Game();

protected:
	list <OBJLIST> m_Patterns; // ���Ͽ� ���� ���� �迭 ȣ�� ���� ����
	GAMERESULT::RESULT m_Result = GAMERESULT::RESULT::NONE; //������� ���� ó��

};

