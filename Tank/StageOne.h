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

public:
	virtual void Pattern(); //���� ��ȯ �� �ֱ� ���� (Stage)

public:
	virtual void Init_ObjList(); // m_ObjList ����Ʈ �ʱ�ȭ
public :
	void		Skill();
	int			Set_Cnt(int _Cnt);
private:
	DWORD						m_Timer = GetTickCount();
	POINT						m_Point[OBJECT::POINT_TYPE_END];
	bool						m_Spawn;
	int							selected_Pattern = 0;
	int							play_Count = 0;
	OBJLIST*					m_Bullet = nullptr;
	int								 iCount;;
	DWORD	spawn_Timer = GetTickCount();
};

