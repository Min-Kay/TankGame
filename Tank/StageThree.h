#ifndef __STAGETHREE_H__
#define __STAGETHREE_H__

#include "Stage.h"
#include <vector>
#include "St3_DeathMotion.h"

class St3_CPatern;

class StageThree : public Stage
{
public:
	explicit StageThree();
	virtual ~StageThree();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void Init_Patterns(); // m_Patterns 리스트 초기화 (Stage)

public:
	virtual void Init_ObjList(); // m_ObjList 리스트 초기화

public:
	virtual void Pattern(); //몬스터 소환 및 주기 관리 (Stage)

private:
	void Update_ObjList_ALL();
	void Kill_ObjList();
	void Kill_DeadMoition();

private:
	int						m_FPS=0;
	bool					m_Mon0_Vaild = false;
	int						m_Mon0_Kill_Count = 0;
	int						m_DroneCool;
private:
	list<St3_DeathMotion*> m_DeathMotionList;

private:
	vector<St3_CPatern*>	m_PaternVec;
	int						m_iSelect = 0;
	bool					m_BossBool = 0;
private:
	int						m_Mon1Count = 0;
	int						m_Mon1Cooltime = 0;
	int						m_BossRes=600;
	

};

#endif // !__STAGETHREE_H__



