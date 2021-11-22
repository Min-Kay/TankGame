#pragma once
#include"Bullet.h"
class St3_FireBullet : public CBullet
{
	//������
	//1. ��ü����, �̴ϼȶ�����
	//2. ��ġ����
	//3. ��������
	//4. Ÿ�Լ���

public:
	explicit St3_FireBullet();
	virtual ~St3_FireBullet();

public:
	virtual void	Initialize(void) override;
	virtual int 	Update(void) override;
	virtual void 	Late_Update(OBJLIST* _objlist) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;
	virtual void	Set_RangeTime(int _range);

private:
	void	Once();
	void	Render_Body(HDC _hdc);
	void	Check_Out();


private:
	short   m_MaxCize;
	bool	m_Max;
	short	m_RangeTime;
	short	m_MaxtimeMAX=0;
	float	m_RadianCircle;
	bool	m_Once = true;
	int		m_Temp;
};

