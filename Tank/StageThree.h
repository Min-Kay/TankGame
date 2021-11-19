#ifndef __STAGETHREE_H__
#define __STAGETHREE_H__

#include "Stage.h"
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


};

#endif // !__STAGETHREE_H__



