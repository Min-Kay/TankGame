#include "stdafx.h"
#include "St3_Chaser.h"
#include "St3_Func.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "Def_St3.h"

St3_Chaser::St3_Chaser()
{
	m_Target = nullptr;
	m_Bullet = nullptr;
	ZeroMemory(m_Point, sizeof(POINT) * 3);
	m_Once =0;
	m_OnceTime =0;
	m_CurruntTime =0;
	m_Cooltime =0;
	m_HP=0;
	m_ID=0;
	m_Respawn = 0; //리스폰 번호설정
	m_HeadRadian=0;

}

St3_Chaser::~St3_Chaser()
{

}

void St3_Chaser::Initialize(void)
{
	m_Once = true;
	m_OnceTime = 30;
	m_CurruntTime = 600;
	m_Cooltime = St3_CHASER_COOLTIME;
	m_HP = 3;
	m_ID = 0;
	m_Type = OBJID::MONSTER;
	//INFO
	m_Info.Width = St3_CHASER_WIDTH;
	m_Info.Height = St3_CHASER_HEIGHT;
	m_Speed = 0;
	m_Type = OBJID::MONSTER;
	m_Info.X = 300;
	m_Info.Y = 300;


}

int St3_Chaser::Update(void)
{
	--m_CurruntTime;
	--m_Cooltime;
	//respawnm
	if (m_Once)
	{
		Respawn();
	}

	if (m_OnceTime > 0)
	{
		Move_Pos(
			m_Info.X += m_OnceTime / 5 * cosf(m_Radian),
			m_Info.Y += m_OnceTime / 5 * sinf(m_Radian)
		);
		Update_Rect();
				--m_OnceTime;
		return 0;
	}



	POINT temp = { m_Target->Get_Info().X, m_Target->Get_Info().Y };
	POINT temp2 = { m_Info.X, m_Info.Y };

	if (150 <= St3_Function::Distance<POINT>(&temp, &temp2))
	{
		if(m_Speed<10)
			++m_Speed;

		Move_Pos(
			m_Info.X += 3 * cos(m_Radian),
			m_Info.Y += 3 * sin(m_Radian));
	}
	else
	{
		if(m_Speed>0)
			--m_Speed;
	}

	m_Radian = atan2(temp.y - m_Info.Y, temp.x - m_Info.X);



	Update_Rect();

	return 0;
}

void St3_Chaser::Late_Update(OBJLIST* _objlist)
{
	POINT temp = { m_Target->Get_Info().X, m_Target->Get_Info().Y };
	POINT temp2 = { m_Info.X, m_Info.Y };



	if (450 > St3_Function::Distance<POINT>(&temp, &temp2))
	{
		Create_Bullet();
	}
}

void St3_Chaser::Render(HDC _hDC)
{
	MoveToEx(_hDC, m_Info.X, m_Info.Y, NULL);

	Render_Body(_hDC);
	Render_Head(_hDC);

	Ellipse(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void St3_Chaser::Release(void)
{
}

void St3_Chaser::Set_Respawn(int _res)
{
	m_Respawn = _res;
}

void St3_Chaser::Set_Bullet(OBJLIST* _bullet)
{
	m_Bullet = _bullet;
}

void St3_Chaser::Set_Target(CObj* _target)
{
	m_Target = _target;
}

void St3_Chaser::Create_Bullet()
{
	if (m_Cooltime == 40 ||
		m_Cooltime == 25 ||
		m_Cooltime == 10)
	{
		POINT temp = { 
			m_Info.X+10*cosf(m_Radian)
			, m_Info.Y+10*sinf(m_Radian)
		};
		m_Bullet->push_back(CAbstractFactory<CBullet>::Create(temp,m_Radian,m_Type));
	}
		

	if (m_Cooltime <= 0)
	{
		m_Cooltime = St3_CHASER_COOLTIME;
	}
}

void St3_Chaser::Respawn()
{

	m_Once = false;

	//respawn
	switch (m_Respawn)
	{
	case 0:
		m_Info.X = 400;
		m_Info.Y = -100;
		m_Radian = PI * 3 / 4;
		break;
	case 1:
		m_Info.X = 50;
		m_Info.Y = -100;
		m_Radian = PI * 7/8 ;
		break;
	case 2:
		m_Info.X = 800;
		m_Info.Y = -100;
		m_Radian = PI * 1 / 8;
		break;
	case 3:
		m_Info.X = 800;
		m_Info.Y = -650;
		m_Radian = PI * 1 / 4;
		break;

	default:
		break;
	}

}

void St3_Chaser::Render_Body(HDC _hDC)
{
	POINTFLOAT temp1={ 0.f,0.f };
	int len = m_Info.Width;

	MoveToEx(_hDC, m_Info.X, m_Info.Y, NULL);

	//1
	len = m_Info.Width;
	temp1.x = m_Info.X + len * cosf(m_Radian);
	temp1.y = m_Info.Y + len * sinf(m_Radian);
	LineTo(_hDC, temp1.x, temp1.y);

	//2
	len = m_Info.Width * 6 / 7;
	temp1.x = m_Info.X + len * cosf(m_Radian + PI / 8);
	temp1.y = m_Info.Y + len * sinf(m_Radian + PI / 8);
	LineTo(_hDC, temp1.x, temp1.y);

	//3
	len = m_Info.Width / 2;
	temp1.x = m_Info.X + len * cosf(m_Radian + PI / 2);
	temp1.y = m_Info.Y + len * sinf(m_Radian + PI / 2);
	LineTo(_hDC, temp1.x, temp1.y);

	//4 꼬리 끝
	len = m_Info.Width;
	temp1.x = m_Info.X + 50 * cosf(m_Radian + PI);
	temp1.y = m_Info.Y + 50 * sinf(m_Radian + PI);
	LineTo(_hDC, temp1.x, temp1.y);

	//5 얼굴로잇기
	len = m_Info.Width;
	temp1.x = m_Info.X + len * cosf(m_Radian);
	temp1.y = m_Info.Y + len * sinf(m_Radian);
	LineTo(_hDC, temp1.x, temp1.y);



	//2
	len = m_Info.Width * 6 / 7;
	temp1.x = m_Info.X + len * cosf(m_Radian - PI / 8);
	temp1.y = m_Info.Y + len * sinf(m_Radian - PI / 8);
	LineTo(_hDC, temp1.x, temp1.y);

	//3
	len = m_Info.Width / 2;
	temp1.x = m_Info.X + len * cosf(m_Radian - PI / 2);
	temp1.y = m_Info.Y + len * sinf(m_Radian - PI / 2);
	LineTo(_hDC, temp1.x, temp1.y);

	//4 꼬리 끝
	len = m_Info.Width;
	temp1.x = m_Info.X + 50 * cosf(m_Radian - PI);
	temp1.y = m_Info.Y + 50 * sinf(m_Radian - PI);
	LineTo(_hDC, temp1.x, temp1.y);
}

void St3_Chaser::Render_Head(HDC _hDC)
{
	POINTFLOAT temp1={ 0.f,0.f };
	int len = m_Info.Width;
	float temp = 0;

	m_HeadRadian += 7 * (PI / 180);

	if (m_HeadRadian > 2 * PI)
		m_HeadRadian -= 2 * PI;


	for (int i = 0; i < 4; ++i)
	{
		float temr =0;

		MoveToEx(_hDC, m_Info.X, m_Info.Y, NULL);
		//1 
		temr = m_HeadRadian+PI/2*i;
		len = m_Info.Width * 2;
		temp1.x = m_Info.X + len * cosf(temr);
		temp1.y = m_Info.Y + len * sinf(temr);
		MoveToEx(_hDC, temp1.x, temp1.y, NULL);

		//2
		temr = m_HeadRadian + PI / 2 + (PI / 2 * i);
		len = m_Info.Width / 10;
		temp1.x = temp1.x - len * cosf(temr);
		temp1.y = temp1.y - len * sinf(temr);
		LineTo(_hDC, temp1.x, temp1.y);

		//3
		temr = m_HeadRadian + (PI / 2 * i);
		len = m_Info.Width * 2;
		temp1.x = temp1.x - len * cosf(temr);
		temp1.y = temp1.y - len * sinf(temr);
		LineTo(_hDC, temp1.x, temp1.y);

		//3
		temr = m_HeadRadian + PI * 3 / 2 + (PI / 2 * i);
		len = m_Info.Width / 10;
		temp1.x = temp1.x - len * cosf(temr);
		temp1.y = temp1.y - len * sinf(temr);
		LineTo(_hDC, temp1.x, temp1.y);

		//아래날개

		//1 
		temr = m_HeadRadian + (PI / 2 * i);
		len = m_Info.Width * 2;
		temp1.x = m_Info.X + len * cosf(temr);
		temp1.y = m_Info.Y + len * sinf(temr);
		MoveToEx(_hDC, temp1.x, temp1.y, NULL);

		//2
		temr = m_HeadRadian + (PI / 2 * i) + PI * 3 / 2;
		len = m_Info.Width / 10;
		temp1.x = temp1.x - len * cosf(temr);
		temp1.y = temp1.y - len * sinf(temr);
		LineTo(_hDC, temp1.x, temp1.y);

		//3
		temr = m_HeadRadian + (PI / 2 * i) ;
		len = m_Info.Width * 2;
		temp1.x = temp1.x - len * cosf(temr);
		temp1.y = temp1.y - len * sinf(temr);
		LineTo(_hDC, temp1.x, temp1.y);

		//3
		temr = m_HeadRadian + (PI / 2 * i) + PI / 2;
		len = m_Info.Width / 10;
		temp1.x = temp1.x - len * cosf(temr);
		temp1.y = temp1.y - len * sinf(temr);
		LineTo(_hDC, temp1.x, temp1.y);


	}






}
