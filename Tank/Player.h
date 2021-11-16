#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Obj.h"

using namespace std;

class CPlayer : public CObj
{
public:
	explicit CPlayer();
	virtual ~CPlayer();


public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	void		Update_Radian(void);			// 타겟의 좌표로 각도를 반환합니다.
	void		Update_Aim(void);
	void		Key_Input(void);
	CObj*		Create_Bullet(void);

public:
	const POINT Get_Focus();
	void		Set_Bullet(list<CObj*>*  _pBullet);

private:
	list<CObj*>* m_Bullet;

};
#endif
