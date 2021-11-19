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
	virtual void Init_Patterns(); // m_Patterns ����Ʈ �ʱ�ȭ (Stage)


public:
	virtual void Init_ObjList(); // m_ObjList ����Ʈ �ʱ�ȭ

public:
	virtual void Pattern(); //���� ��ȯ �� �ֱ� ���� (Stage)


};

#endif // !__STAGETHREE_H__



