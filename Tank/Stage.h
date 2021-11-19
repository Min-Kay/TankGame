#pragma once
#include "Menu.h"
#include "Enum.h"

class Stage :
	public Game
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
	virtual void Release_Patterns(); // m_Patterns ����Ʈ ���� (Stage)

public:
	virtual void Init_ObjList() PURE; // m_ObjList ����Ʈ �ʱ�ȭ
	void Update_ObjList(); // m_ObjList ����Ʈ ������Ʈ 
	void LateUpdate_ObjList(); // m_ObjList ����Ʈ ��Ʈ ������Ʈ
	void Render_ObjList(); // m_ObjList ����Ʈ ����
	virtual void Release_ObjList(); // m_ObjList ����Ʈ ����

public:
	void Add_MonsterList(CObj* _monster);// m_ObjList[OBJID::MONSTER]�� m_Patterns���� ��ȯ�ϰ����ϴ� ���� �߰�

public:
	virtual void Pattern()PURE; //���� ��ȯ �� �ֱ� ���� (Stage)

public:
	void Set_Result(GAMERESULT::RESULT _result) { m_Result = _result; } // ���� ���� ���� (Stage)
	const GAMERESULT::RESULT& Get_Result() const { return m_Result; }; // ��� ��ȯ(Stage) 

public:
	const OBJLIST& Get_PlayerList() const { return m_ObjList[OBJID::PLAYER]; }; // �÷��̾� ����Ʈ ��ȯ
	const OBJLIST& Get_MonsterList() const { return m_ObjList[OBJID::MONSTER]; }; // ���� ����Ʈ ��ȯ 
	const OBJLIST& Get_MissileList() const { return m_ObjList[OBJID::MISSILE]; }; // ����ü ����Ʈ ��ȯ

public:
	void Set_Clear(bool _bool) { isClear = _bool; } // �ۼ��� ��� ���� ���� ���� ����
	void Goto_Menu(); // m_Result�� ���¿� ���� ������� ���� �޴��� ���ư���
	void Release_Game(); // ���� ���� ������ �۾� ���� - Release�� �߰��ϸ� �⺻������ �������� Stage ���� ����

public:
	void Check_Collision(); // ���� ���� �浹 ó�� - Late_Update�� �ۼ�

public:
	void Check_GameState(); // ���� ���� ��Ȳ Ȯ�� (����)
	void Show_Win_Lose(); // ���� �� �� ��� ȭ�� ����

public:
	void Cheat_Mode(); // ����� ���� 

protected:
	OBJLIST m_ObjList[OBJID::END]; // OBJID�� �ش��ϴ� ��ȯü ����
	vector <OBJVEC> m_Patterns; // ���Ͽ� ���� ���� �迭 ȣ�� ���� ����
	GAMERESULT::RESULT m_Result = GAMERESULT::RESULT::NONE; //������� ���� ó��
	bool		isClear = false;


	DWORD Debug_Timer = GetTickCount(); // ����� ���� Ÿ�̸�
};

