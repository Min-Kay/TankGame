#pragma once
class CObj;

class Game
{
public:
	Game();
	virtual ~Game();

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

public:
	// ���콺 RECT ����
	void Update_CursorRect();

public:
	const POINT& Get_Cursor() const { return m_Point; }; // ���콺 �� ��ȯ

public:
	virtual void Set_Selection(GAME::GAMEID _id); // �������� ��ȣ ����
	virtual const GAME::GAMEID Get_Selection() const { return m_Selection; }; // �ҷ��� �������� ��ȣ ��ȯ

public:
	void BackGround(); // ��� �ڽ� �׸���

public:
	void Init_DefaultSetting(GAME::GAMEID  _id); // ���� ���� �ʱ�ȭ �Լ� - ��ӹ��� Stage�� Initialize�� �߰��ϼ���

protected:
	HDC				m_DC; // HDC
	INFO			m_Info; // ���콺 ����
	RECT			m_Rect; // ���콺 RECT
	POINT			m_Point; // ���콺 ��ǥ
	GAME::GAMEID	m_Selection ; // �������� Ȥ�� �޴� ���� ����
};


