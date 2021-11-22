#pragma once
#include"Obj.h"
class St3_Chaser : public CObj
{

	//사용순서
	//1. 이니셜라이징
	//2. 리스폰 번호 설정
	//3. 총알리스트 주소 전당
	//4. 타겟설정

public:
	explicit St3_Chaser(); //리스폰 번호설정
	virtual ~St3_Chaser();

	//기본 함수
public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual void		Late_Update(OBJLIST* _objlist) override;
	virtual void		Render(HDC _hDC) override;
	virtual void		Release(void) override;

public:
	void			Set_Respawn(int _res);
	void			Set_Bullet(OBJLIST* _bullet);
	void			Set_Target(CObj*	_target);
	static int		Get_Count() { return LavaCount; }
	int				Get_ID() { return m_ID; }

private:
	void			Create_Bullet();
	void			Respawn();
	void			Render_Body(HDC _hDC);
	void			Render_Head(HDC _hDC);

private:
	CObj*				m_Target;
	OBJLIST*			m_Bullet = nullptr;
	POINT				m_Point[3];
	bool				m_Once;
	short				m_OnceTime;
	short				m_CurruntTime;
	short				m_Cooltime;

	short				m_HP;
	short				m_ID;
	short				m_Respawn;
	float				m_HeadRadian;

public:
	static short LavaCount;
};

