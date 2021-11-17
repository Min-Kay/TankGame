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
	void Release_Cursor();

public:
	void Update_CursorRect();

public:
	const POINT& Get_Cursor() const { return m_Point; }; // ���콺 �� ��ȯ

public:
	void Set_Loaded(bool _bool) { m_isLoaded = _bool; }
	bool Get_Loaded();

public:
	virtual void Set_Selection(int i); // �������� ��ȣ ����
	virtual const int Get_Selection() const { return m_Selection; }; // �ҷ��� �������� ��ȣ ��ȯ

public:
	void BackGround(); // ��� �ڽ� �׸���

public:
	void Init_DefaultSetting(int _gameNum); // ���� ���� �ʱ�ȭ �Լ� - ��ӹ��� Stage�� Initialize�� �߰��ϼ���

protected:
	HDC m_DC; // HDC
	INFO m_Info; // ���콺 ����
	RECT m_Rect; // ���콺 RECT
	POINT m_Point; // ���콺 ��ǥ
	bool m_isLoaded = false;
	int m_Selection ;
};


