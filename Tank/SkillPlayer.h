#pragma once
#include "Player.h"
class CSatellite;
class CSkillPlayer :
	public CPlayer
{
public:
	CSkillPlayer();
	virtual ~CSkillPlayer();


public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void Late_Update(OBJLIST* _objlist) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
	void		Create_Bullet(void);


public:
	const POINT		Get_Focus();
	void			Set_Bullet(list<CObj*>*  _pBullet);
	void			Set_Satellite(list<CObj*>*  _Satellite) { m_Satellite = _Satellite; }
	void			Add_Satellite(CObj* _satellite) { m_Satellite->push_back(_satellite); }
	void			Update_Aim(int _cannonsize);			// Ÿ���� ��ǥ�� ������ ��ȯ�մϴ�.

protected:
	OBJLIST*		m_Bullet;
	OBJLIST*		m_Satellite;
	OBJLIST*		m_ScrewBullet;

	CObj*			m_Bullet1;
private:
	DWORD			m_CoolTime;
	DWORD			m_InitTime;

};

