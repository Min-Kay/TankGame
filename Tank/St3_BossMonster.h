#pragma once
#include "Obj.h"
class St3_BossMonster : public CObj
{
public:
	explicit St3_BossMonster();
	virtual ~St3_BossMonster();

	//기본 함수
public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual void		Late_Update(OBJLIST* _objlist) override;
	virtual void		Render(HDC _hDC) override;
	virtual void		Release(void) override;

public:
	void			Set_Bullet(OBJLIST* _bullet);
	int				Get_ID() { return m_ID; }
	void			Set_Hp(int _att) { m_HP += _att; }
	int				Get_Hp() { return m_HP; };
	void			Set_Target(CObj* _target);

private:
	void			Render_Head(HDC _hDC);
	void			Render_Chain(HDC _hDC);
	void			Update_Chain();

private:
	void			Create_FireBullet();
	void			Create_MineBullet();
private:
	void			Default_Moving();
	void			Patern1();
	void			Pattern2();

private:
	OBJLIST*			m_Bullet = nullptr;
	POINTFLOAT			m_Chain[15];
	RECT				m_ChainBody[15];
	POINTFLOAT			m_Cannon[3];
	CObj*				m_Target=nullptr;

private:
	bool				m_Default;
	short				m_DefaultTime;
	bool				m_DefaultTimeBool;
	int					m_PaternCheck = 0;

private:
	bool				m_Patern1=false;
	short				m_Patern1Cooltime;
	short				m_FireTime = 0;

private:
	bool				m_Patern2;
	short				m_Patern2Cooltime;
	short				m_Delay;
	bool				m_Out;
	bool				m_CountVaild;
	long				m_FPS;
	short				m_Cooltime;
	short				m_HP;
	short				m_ID;
	bool				m_Once = false;
	short				m_OnceTime = 0;
	short				m_OutTime = 0;
};

