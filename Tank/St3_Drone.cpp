#include "stdafx.h"
#include "St3_Drone.h"
#include "St3_Func.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "Def_St3.h"

St3_Drone::St3_Drone()
{
	m_Target=nullptr;
	m_Bullet = nullptr;
	ZeroMemory(&m_GunPoint, sizeof(POINT) * 4);


	m_HP=1;
	m_ID=0;
	m_Respawn=0;
	m_HeadRadian=0;

	m_Once= false;
	m_OnceTime=0;

	m_Pattern=false;
	m_PatternCooltime=0;

	m_Cooltime=0;
	m_CurruntTime=0;
	m_PaternCheck = 0;
}

St3_Drone::~St3_Drone()
{
	Release();
}

void St3_Drone::Initialize(void)
{
	m_Once = true;
	m_OnceTime = 30;
	m_CurruntTime = 600;
	m_Cooltime = St3_DRONE_COOLTIME;
	m_HP = 3;
	m_ID = 0;
	m_Type = OBJID::MONSTER;
	m_Pattern = true;
	//INFO
	m_Info.Width = St3_DRONE_HEAD;
	m_Info.Height = St3_DRONE_BODY;
	m_Speed = 10;
	m_Type = OBJID::MONSTER;
	m_Info.X = 900;
	m_Info.Y = 300;
	m_PatternCooltime = 360;
	m_HeadRadian = 0;
}

int St3_Drone::Update(void)
{
	
	--m_Cool;
	


	if (m_Pattern)
	{
		Pattern();
	}


	if (m_PaternCheck==9)
	{
		m_Info.Y += 10;
		if (m_Info.Y > 600)
			m_Dead = true;
	}


	if (m_Once == false)
		--m_Cooltime;


	Update_Points();
	Update_Rect();
	return 0;
}

void St3_Drone::Late_Update(OBJLIST* _objlist)
{
}

void St3_Drone::Render(HDC _hDC)
{
	Ellipse(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
	MoveToEx(_hDC, m_GunPoint[0].x, m_GunPoint[0].y, NULL);
	LineTo(_hDC, m_GunPoint[1].x, m_GunPoint[1].y);
	LineTo(_hDC, m_GunPoint[2].x, m_GunPoint[2].y);
	LineTo(_hDC, m_GunPoint[3].x, m_GunPoint[3].y);
	LineTo(_hDC, m_GunPoint[0].x, m_GunPoint[0].y);


	WCHAR Buff1[32] = L"";
	swprintf_s(Buff1, L" 좌표 : %f , %f ", m_Info.X, m_Info.Y);
	TextOut(_hDC, 400, 300, Buff1, lstrlenW(Buff1));

	WCHAR Buff2[32] = L"";
	swprintf_s(Buff2, L" 시퀀스 : %d ", m_PaternCheck);
	TextOut(_hDC, 400, 400, Buff2, lstrlenW(Buff2));


}

void St3_Drone::Release(void)
{
}

void St3_Drone::Set_Bullet(OBJLIST* _bullet)
{
	m_Bullet = _bullet;
}

void St3_Drone::Update_Points()
{
	for (int i = 0; i < 4; i++)
	{
		m_GunPoint[i].x = m_Info.X + 10*cosf(m_HeadRadian+ PI/2*i);
		m_GunPoint[i].y = m_Info.Y + 10*sinf(m_HeadRadian + PI / 2*i);
	}
}

void St3_Drone::Pattern()
{
	POINT temp;
	switch (m_PaternCheck)
	{
	case 0:
	

		if (m_Info.X <= 700)
		{
			m_Once = false; //시간초시작

			if (m_Cooltime % St3_DRONE_SHOOT_SPEED == 0)
				Create_Bullet();

			if(m_Cooltime<=0)
			{
				m_Cooltime = 360;
				++m_PaternCheck;
				m_Once = true;
			}
		}
		else
		{
			temp.x = 700;
			temp.y = 300;
			Update_Radian(temp);
			m_Info.X += 5 * cosf(m_Radian);
			m_Info.Y += 5 * sinf(m_Radian);
		}

		break;
	case 1:

		if (m_Info.Y <= 200)
		{
			m_Once = false; //시간초시작

			if (m_Cooltime % St3_DRONE_SHOOT_SPEED == 0)
				Create_Bullet();

			if (m_Cooltime <= 0)
			{
				m_Cooltime = 360;
				++m_PaternCheck;
				m_Once = true;
			}
		}
		else
		{
			temp.x = 600;
			temp.y = 200;
			Update_Radian(temp);
			m_Info.X += 5 * cosf(m_Radian);
			m_Info.Y += 5 * sinf(m_Radian);
		}
		break;
	case 2:

		if (m_Info.Y <= 100)
		{
			m_Once = false; //시간초시작

			if (m_Cooltime % St3_DRONE_SHOOT_SPEED == 0)
				Create_Bullet();

			if (m_Cooltime <= 0)
			{
				m_Cooltime = 360;
				++m_PaternCheck;
				m_Once = true;
			}
		}
		else
		{
			temp.x = 400;
			temp.y = 100;
			Update_Radian(temp);
			m_Info.X += 5 * cosf(m_Radian);
			m_Info.Y += 5 * sinf(m_Radian);
		}
		break;

	case 3:

		if (m_Info.Y >= 200)
		{
			m_Once = false; //시간초시작

			if (m_Cooltime % St3_DRONE_SHOOT_SPEED == 0)
				Create_Bullet();

			if (m_Cooltime <= 0)
			{
				m_Cooltime = 360;
				++m_PaternCheck;
				m_Once = true;
			}
		}
		else
		{
			temp.x = 200;
			temp.y = 200;
			Update_Radian(temp);
			m_Info.X += 5 * cosf(m_Radian);
			m_Info.Y += 5 * sinf(m_Radian);
		}

		break;

	case 4:
		if (m_Info.Y >= 400)
		{
			m_Once = false; //시간초시작

			if (m_Cooltime % St3_DRONE_SHOOT_SPEED == 0)
				Create_Bullet();

			if (m_Cooltime <= 0)
			{
				m_Cooltime = 360;
				++m_PaternCheck;
				m_Once = true;
			}
		}
		else
		{
			temp.x = 100;
			temp.y = 400;
			Update_Radian(temp);
			m_Info.X += 5 * cosf(m_Radian);
			m_Info.Y += 5 * sinf(m_Radian);
		}
		break;

	case 5: 

		if (m_Info.Y >= 400)
		{
			m_Once = false; //시간초시작

			if (m_Cooltime % St3_DRONE_SHOOT_SPEED == 0)
				Create_Bullet();

			if (m_Cooltime <= 0)
			{
				m_Cooltime = 360;
				++m_PaternCheck;
				m_Once = true;
			}
		}
		else
		{
			temp.x = 200;
			temp.y = 400;
			Update_Radian(temp);
			m_Info.X += 5 * cosf(m_Radian);
			m_Info.Y += 5 * sinf(m_Radian);
		}
		break;

	case 6:
		if (m_Info.Y >= 500)
		{
			m_Once = false; //시간초시작

			if (m_Cooltime % St3_DRONE_SHOOT_SPEED == 0)
				Create_Bullet();

			if (m_Cooltime <= 0)
			{
				m_Cooltime = 360;
				++m_PaternCheck;
				m_Once = true;
			}
		}
		else
		{
			temp.x = 400;
			temp.y = 500;
			Update_Radian(temp);
			m_Info.X += 5 * cosf(m_Radian);
			m_Info.Y += 5 * sinf(m_Radian);
		}
		break;

	case 7:
		if (m_Info.Y <= 400)
		{
			m_Once = false; //시간초시작

			if (m_Cooltime % St3_DRONE_SHOOT_SPEED == 0)
				Create_Bullet();

			if (m_Cooltime <= 0)
			{
				m_Cooltime = 360;
				++m_PaternCheck;
				m_Once = true;
			}
		}
		else
		{
			temp.x = 600;
			temp.y = 400;
			Update_Radian(temp);
			m_Info.X += 5 * cosf(m_Radian);
			m_Info.Y += 5 * sinf(m_Radian);
		}
		break;

	case 8:
		if (m_Info.Y <= 300)
		{
			m_Once = false; //시간초시작

			if (m_Cooltime % St3_DRONE_SHOOT_SPEED == 0)
				Create_Bullet();

			if (m_Cooltime <= 0)
			{
				m_Cooltime = 360;
				++m_PaternCheck;
				m_Once = true;
			}
		}
		else
		{
			temp.x = 700;
			temp.y = 300;
			Update_Radian(temp);
			m_Info.X += 5 * cosf(m_Radian);
			m_Info.Y += 5 * sinf(m_Radian);
		}
		break;


	}

}

void St3_Drone::Once()
{
	m_Once = false;
}

void St3_Drone::Create_Bullet()
{
	if (m_Cool <= 0)
	{
		m_HeadRadian += PI / 20;
		for (int i = 0; i < 4; ++i)
		{
			float rad = atan2(m_GunPoint[i].y - m_Info.Y, m_GunPoint[i].x - m_Info.X);
			CObj* temp = CAbstractFactory<CBullet>::Create(
				m_GunPoint[i],
				m_HeadRadian + PI / 2 * i,
				OBJID::MONSTER
			);
			m_Bullet->push_back(temp);
		}
	}


}
