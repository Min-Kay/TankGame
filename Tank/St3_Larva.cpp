#include "stdafx.h"
#include "St3_Larva.h"
#include "St3_Skill01.h"
#include "Bullet.h"
#include "Def_St3.h"
#include "AbstractFactory.h"
#include "St3_MineBullet.h"
short St3_Larva::LavaCount = 0;

St3_Larva::St3_Larva()
{
	ZeroMemory(&m_Chain, sizeof(POINT) * 10);
	m_Cooltime = 0;
	m_ID = 1;
	++LavaCount;
}


St3_Larva::~St3_Larva()
{
}

void St3_Larva::Initialize(void)
{

	m_Info.X = 0;
	m_Info.Y = 0;
	m_Speed = 0.5f;
	m_Type = OBJID::MONSTER;
	m_Out = false;
	m_Radian =PI/(rand()%20);
	m_FPS = 0;
	m_CountVaild = true;
	m_Once = true;

	m_HP = rand() % 5 + 1; //Ã¼·Â·£´ý
	m_Info.Height = St3_LAVA_HEAD + 5 * m_HP;
	m_Info.Width = St3_LAVA_HEAD + 5 * m_HP;

	m_OnceTime = 0;
	m_OutTime = 60;
	m_Cooltime = St3_LAVA_COOLTIME;
}

int St3_Larva::Update(void)
{
	

	--m_Cooltime;
	++m_OnceTime;

	if (m_CountVaild)
	{
		++m_FPS;
		if (m_FPS >= 30)
			m_CountVaild = false;
	}
	else
	{
		--m_FPS;
		if (m_FPS <= 0)
			m_CountVaild = true;
	}

	if (m_Once)
	{ 
		for (int i = 0; i < 10; i++)
		{
			m_Chain[i] = { m_Info.X + 1 * i, m_Info.Y + 1 * i };
		}

		m_Once = false;
	}

	if (m_OutTime <= 0)
		m_Dead = true;


	memmove(m_Chain+1, m_Chain, sizeof(POINTFLOAT)*9);

	float temp = m_FPS ;							//¿ë¼öÃ¶ ÀÌµ¿		

	//m_Chain[0].x += (m_Speed+temp/6)*cosf(m_Radian);
	//m_Chain[0].y += (m_Speed+temp/6)*sinf(m_Radian);

	m_Info.X += (m_Speed + temp / 6) * cosf(m_Radian);
	m_Info.Y += (m_Speed + temp / 6) * sinf(m_Radian);

	m_Chain[0].x = m_Info.X ;
	m_Chain[0].y = m_Info.Y ;
	
	Pattern();
	Update_Rect();
	return 0;
}

void St3_Larva::Late_Update(OBJLIST * _objlist)
{
	if (0 >= m_Body.top - m_Speed ||
		0 >= m_Body.left - m_Speed ||
		600 <= m_Body.bottom + m_Speed ||
		800 <= m_Body.right + m_Speed
		)
	{
		--m_OutTime;
		m_Radian += PI/2;
	}
	else
	{
		m_OutTime = 30;
	}
}

void St3_Larva::Render(HDC _hDC)
{
	//if (m_OnceTime<=30)
	//{
	//	RECT rc;

	//	rc.left = m_Info.X - m_Info.Width*m_OnceTime/30;
	//	rc.top = m_Info.Y - m_Info.Width * m_OnceTime / 30;
	//	rc.right = m_Info.X + m_Info.Width * m_OnceTime / 30;
	//	rc.bottom = m_Info.Y - m_Info.Width * m_OnceTime / 30;

	//	Ellipse(_hDC, rc.left, rc.top, rc.right, rc.bottom);

	//	return;
	//}

	POINT temp = {}; // ÆÈ ¿ë

	m_Info.Height = St3_LAVA_HEAD + 5 * m_HP;
	m_Info.Width = St3_LAVA_HEAD + 5 * m_HP;

	int BWIDTH = St3_LAVA_BODY +4* m_HP;
	int HWIDTH = St3_LAVA_HEAD  +5* m_HP;
	int LWIDTH = St3_LAVA_LEG + 3* m_HP;

	for (int i = 19; i > 0; --i)
	{
		Ellipse(_hDC, m_Chain[i].x - BWIDTH, m_Chain[i].y - BWIDTH, m_Chain[i].x + BWIDTH, m_Chain[i].y + BWIDTH);
		temp.x = m_Chain[i].x + LWIDTH * cosf(m_Radian + PI / 2);
		temp.y = m_Chain[i].y + LWIDTH * sinf(m_Radian + PI / 2);
		MoveToEx(_hDC, m_Chain[i].x, m_Chain[i].y, NULL);
		LineTo(_hDC, temp.x, temp.y);

		temp.x = m_Chain[i].x + LWIDTH * cosf(m_Radian - PI / 2);
		temp.y = m_Chain[i].y + LWIDTH * sinf(m_Radian - PI / 2);
		MoveToEx(_hDC, m_Chain[i].x, m_Chain[i].y, NULL);
		LineTo(_hDC, temp.x, temp.y);
	}


	// ¿ìÃøÆÈ
	temp.x = m_Chain[0].x + LWIDTH *1.5 * cosf(m_Radian+PI/4);
	temp.y = m_Chain[0].y + LWIDTH *1.5 * sinf(m_Radian + PI / 4);
	MoveToEx(_hDC, m_Chain[0].x, m_Chain[0].y, NULL);
	LineTo(_hDC, temp.x, temp.y);

	temp.x = temp.x + LWIDTH /2 * cosf(m_Radian + PI*2/6 );
	temp.y = temp.y + LWIDTH /2 * sinf(m_Radian + PI*2/6);
	LineTo(_hDC, temp.x, temp.y);

	//ÁÂÃøÆÈ
	temp.x = m_Chain[0].x + LWIDTH * 1.5 * cosf(m_Radian - PI / 4);
	temp.y = m_Chain[0].y + LWIDTH * 1.5 * sinf(m_Radian - PI / 4);
	MoveToEx(_hDC, m_Chain[0].x, m_Chain[0].y, NULL);
	LineTo(_hDC, temp.x, temp.y);

	temp.x = temp.x + LWIDTH / 2 * cosf(m_Radian - PI * 2 / 6);
	temp.y = temp.y + LWIDTH / 2 * sinf(m_Radian - PI * 2 / 6);
	LineTo(_hDC, temp.x, temp.y);


	Ellipse(_hDC, m_Chain[0].x - HWIDTH, m_Chain[0].y - HWIDTH, m_Chain[0].x + HWIDTH, m_Chain[0].y + HWIDTH);




}

void St3_Larva::Release(void)
{
	
}

void St3_Larva::Set_Bullet(OBJLIST* _bullet)
{
	m_Bullet = _bullet;
}

void St3_Larva::Pattern()
{
	if (m_Cooltime <= 0)
	{
		CObj* temp = CAbstractFactory<St3_MineBullet>::Create();
		temp->Set_Type(OBJID::MONSTER);
		temp->Move_Pos(m_Info.X , m_Info.Y );
		m_Bullet->push_back(temp);
		m_Cooltime = 180;
	}

	if (m_Cooltime <=30 )
	{
		m_Radian += PI / (rand() %120+90);
	}
}
