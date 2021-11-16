#pragma once
class CObj;

class Game
{

public:
	// Ŭ���� �����ֱ� (Main)
	virtual void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render();
	virtual void Release();

public:
	// ���콺 Ŀ�� ���� (Main)
	void Init_Cursor();
	void Update_Cursor();
	void Render_Cursor();
	void Release_Cursor();

public:
	void Update_CursorRect();

public:
	const POINT& Get_Cursor() const { return m_Point; }; // ���콺 �� ��ȯ

public:
	const OBJLIST& Get_PlayerList() const { return m_ObjList[OBJID::PLAYER]; }; // �÷��̾� ����Ʈ ��ȯ
	const OBJLIST& Get_MonsterList() const { return m_ObjList[OBJID::MONSTER]; }; // ���� ����Ʈ ��ȯ 
	const OBJLIST& Get_MissileList() const { return m_ObjList[OBJID::MISSILE]; }; // ����ü ����Ʈ ��ȯ

public:
	bool Get_Loaded();

public:
	void Set_Selection(int i); // �������� ��ȣ ����
	const int& Get_Selection() const { return m_Selection; }; // �ҷ��� �������� ��ȣ ��ȯ

protected:
	HDC m_DC; // HDC
	INFO m_Info; // ���콺 ����
	RECT m_Rect; // ���콺 RECT
	POINT m_Point; // ���콺 ��ǥ
	OBJLIST m_ObjList[OBJID::END]; // OBJID�� �ش��ϴ� ��ȯü ����
	bool m_isLoaded = false;
	int m_Selection;
};


