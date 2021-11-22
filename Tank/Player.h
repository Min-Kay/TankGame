#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Obj.h"

class CSatellite;

class CPlayer : public CObj
{
public:
	explicit CPlayer();
	virtual ~CPlayer();


public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void Late_Update(OBJLIST* _objlist) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

protected:
	void		Key_Input(void);
	void		Create_Bullet(void);


public:
	const POINT		Get_Focus();
	void			Set_Bullet(list<CObj*>*  _pBullet);
	void			Set_Satellite(list<CObj*>*  _Satellite) { m_Satellite = _Satellite; }
	void			Add_Satellite(CObj* _satellite) { m_Satellite->push_back(_satellite); }
	void			Update_Aim(int _cannonsize);			// 타겟의 좌표로 각도를 반환합니다.

protected:
	OBJLIST*		m_Bullet;
	OBJLIST*		m_Satellite;

private:
	DWORD			m_CoolTime;
	DWORD			m_InitTime; 
};
#endif
