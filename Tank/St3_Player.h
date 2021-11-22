#pragma once
#include "Player.h"
class St3_Player : public CPlayer
{
public:
	St3_Player();
	~St3_Player();

public:
	virtual int	 Update(void) override;
	virtual void Late_Update(OBJLIST* _objlist) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

public:
	virtual void Key_Input_Plus(void);

private:
	void		Create_ChaseBullet(void);
	void		Create_FireBullet(void);

private:
	int			m_FPS = 0;
	int			m_SkillSelect =0;

	DWORD m_CoolTimeZ = 0;
	DWORD m_CoolTimeX = 0;
	DWORD m_CoolTimeC = 0;


private:
	

};

