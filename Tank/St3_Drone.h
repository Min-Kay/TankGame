#pragma once
#include "Obj.h"
class St3_Drone : public CObj
{
	//������
//1. �̴ϼȶ���¡
//2. ������ ��ȣ ����
//3. �Ѿ˸���Ʈ �ּ� ����
//4. Ÿ�ټ���

public:
	explicit St3_Drone(); //������ ��ȣ����
	virtual ~St3_Drone();

	//�⺻ �Լ�
public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual void		Late_Update(OBJLIST* _objlist) override;
	virtual void		Render(HDC _hDC) override;
	virtual void		Release(void) override;

public:
	void				Set_Respawn(int _res);
	void				Set_Bullet(OBJLIST* _bullet);
	void				Set_Target(CObj* _target);
	int					Get_ID() { return m_ID; }

private:
	void				Create_Bullet();
	void				Respawn();
	void				Render_Body(HDC _hDC);
	void				Render_Head(HDC _hDC);
	void				Update_Points();

private:
	void				Pattern();
	void				Once();
	int					m_Cool=10;
private:
	CObj*				m_Target;
	OBJLIST*			m_Bullet = nullptr;
	POINT				m_GunPoint[4];

	bool				m_Once;
	short				m_OnceTime;

	bool				m_Pattern;
	short				m_PatternCooltime;

	short				m_CurruntTime;
	short				m_Cooltime;

	bool				m_End = false;;

	short				m_HP;
	short				m_ID;
	short				m_Respawn;
	float				m_HeadRadian;

	int					m_PaternCheck = 0;
};

