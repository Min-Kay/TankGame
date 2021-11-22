#pragma once
class St3_DeathMotion
{
public:
	explicit St3_DeathMotion(short _size, POINT _locate);
	virtual ~St3_DeathMotion();
public:
	virtual void		Initialize(void) ;
	virtual int			Update(void) ;
	virtual void		Late_Update(void) ;
	virtual void		Render(HDC _hDC) ;
	virtual void		Release(void) ;

public:
	bool Get_Dead() { return m_Dead; }
private:
	void Update_Rect();

private:
	short	m_FPS;
	short	m_Size;
	float	m_Radian;
	bool	m_ReversePoint=false;
	RECT	m_Body;
	POINT	m_Point;
	bool	m_Dead;

};

