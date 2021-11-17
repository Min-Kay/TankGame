#pragma once
class CObj;

class Game
{
public:
	Game();
	virtual ~Game();

public:
	// 클래스 생명주기 (Main)
	virtual void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render();
	virtual void Release();

public:
	// 마우스 커서 관리 (Main)
	void Init_Cursor();
	void Update_Cursor();
	void Render_Cursor();
	void Release_Cursor();

public:
	void Update_CursorRect();

public:
	const POINT& Get_Cursor() const { return m_Point; }; // 마우스 값 반환

public:
	void Set_Loaded(bool _bool) { m_isLoaded = _bool; }
	bool Get_Loaded();

public:
	virtual void Set_Selection(int i); // 스테이지 번호 선택
	virtual const int Get_Selection() const { return m_Selection; }; // 불러올 스테이지 번호 반환

public:
	void BackGround(); // 배경 박스 그리기

public:
	void Init_DefaultSetting(int _gameNum); // 게임 공통 초기화 함수 - 상속받은 Stage의 Initialize에 추가하세요

protected:
	HDC m_DC; // HDC
	INFO m_Info; // 마우스 중점
	RECT m_Rect; // 마우스 RECT
	POINT m_Point; // 마우스 좌표
	bool m_isLoaded = false;
	int m_Selection ;
};


