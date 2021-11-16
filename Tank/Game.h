#pragma once
class CObj;

class Game
{

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
	const OBJLIST& Get_PlayerList() const { return m_ObjList[OBJID::PLAYER]; }; // 플레이어 리스트 반환
	const OBJLIST& Get_MonsterList() const { return m_ObjList[OBJID::MONSTER]; }; // 몬스터 리스트 반환 
	const OBJLIST& Get_MissileList() const { return m_ObjList[OBJID::MISSILE]; }; // 투사체 리스트 반환

public:
	bool Get_Loaded();

public:
	void Set_Selection(int i); // 스테이지 번호 선택
	const int& Get_Selection() const { return m_Selection; }; // 불러올 스테이지 번호 반환

protected:
	HDC m_DC; // HDC
	INFO m_Info; // 마우스 중점
	RECT m_Rect; // 마우스 RECT
	POINT m_Point; // 마우스 좌표
	OBJLIST m_ObjList[OBJID::END]; // OBJID에 해당하는 소환체 관리
	bool m_isLoaded = false;
	int m_Selection;
};


