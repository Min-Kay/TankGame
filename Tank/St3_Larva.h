#pragma once
#include "Obj.h"
class St3_Larva : public CObj
{
public:
	explicit St3_Larva();
	virtual ~St3_Larva();

	//기본 함수
public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual void		Late_Update(OBJLIST* _objlist) override;
	virtual void		Render(HDC _hDC) override;
	virtual void		Release(void) override;

public:
	void			Set_Bullet(OBJLIST* _bullet );
	static int		Get_Count() { return LavaCount; }
	static void		Set_Count() {  --LavaCount; }
	int				Get_ID() { return m_ID; }
private:
	void	Pattern();

private:
	OBJLIST*			m_Bullet=nullptr;
	POINTFLOAT			m_Chain[10];
	bool				m_Out;
	bool				m_CountVaild;
	long				m_FPS;
	short				m_Cooltime;
	short				m_HP;
	short				m_ID;
	bool				m_Once=false;
	short				m_OnceTime = 0;
	short				m_OutTime=0;

public:
	static short LavaCount;
};

