#include "stdafx.h"
#include "St3_BossMonster.h"
#include "St3_CollisionMgr.h"
#include "St3_FireBullet.h"
#include "St3_MineBullet.h"
#include "AbstractFactory.h"
#include "St3_Func.h"
#include "Def_St3.h"

St3_BossMonster::St3_BossMonster()
{
	m_Bullet =nullptr;
	ZeroMemory(m_Chain, sizeof(POINTFLOAT)*15);
	ZeroMemory(m_Cannon, sizeof(POINTFLOAT) * 3);
	ZeroMemory(m_ChainBody, sizeof(RECT) * 15);
	m_Default = false;
	m_DefaultTime=0;

	m_Patern1=false;
	m_Patern1Cooltime=0;

	m_Patern2=false;
	m_Patern1Cooltime=0;

	m_DefaultTimeBool = false;
	m_Delay = 180;
}

St3_BossMonster::~St3_BossMonster()
{
	Release();
}

void St3_BossMonster::Initialize(void)
{


	//COBJ
	m_Info.X = 400;
	m_Info.Y = 300;
	m_Info.Height = St3_BOSS_HEIGHT;
	m_Info.Width = St3_BOSS_WIDTH;
	m_Speed = St3_BOSS_SPEED;
	m_Type = OBJID::END;
	m_Radian = PI *3/2;
	m_HP = St3_BOSS_HP; //체력

	//BOSS
	m_FPS = 65;
	m_CountVaild = true;
	m_Once = true;

	m_Default= true;
	m_DefaultTime= 0;
	m_DefaultTimeBool = true;

	m_Patern1=false;
	m_Patern1Cooltime=300;
	m_FireTime = 200;

	m_Patern2= false;
	m_Patern2Cooltime= 600;

	m_OnceTime = 0;
	m_OutTime = 60;
	m_Cooltime = St3_LAVA_COOLTIME;

	Update_Rect();
	m_Chain[0].x=m_Info.X ;
	m_Chain[0].y=m_Info.Y;
}

int St3_BossMonster::Update(void)
{
	if (m_Patern1Cooltime <= 0)
	{
		m_Patern1 = true;
	}
	else if(m_Patern1 ==false)
	{
		if (!m_Patern2)
		{
			--m_Patern1Cooltime; //패턴2 쿨타임 변수
		}
	}


	if (m_Patern2Cooltime <= 0)
	{
		m_Patern2 = true;
	}
	else if (m_Patern2 == false)
	{
		if (!m_Patern1)
		{
			--m_Patern2Cooltime; //패턴2 쿨타임 변수
		}
		
	}




	m_Chain[0].x = m_Info.X;
	m_Chain[0].y = m_Info.Y;
	memmove(m_Chain + 1, m_Chain, sizeof(POINTFLOAT) * 14);

	if (m_Once)
	{
		for (int i = 0; i < 15; i++)
		{
			m_Chain[i] = { m_Info.X + 1 * i, m_Info.Y + 1 * i };
		}

		m_Once = false;
	}


	if (m_Patern1)
	{
		Patern1();
	}
	else if (m_Patern2)
	{
		Pattern2();
	}
	else if (m_Default)
	{
		Default_Moving();
	}

	Update_Rect();
	Update_Chain();

	return 0;
}

void St3_BossMonster::Late_Update(OBJLIST* _objlist)
{
	//St3_CollisionMgr::Check_Blocking_Push(m_ChainBody, m_ChainBody);
}

void St3_BossMonster::Render(HDC _hDC)
{
	Render_Head(_hDC);
	Render_Chain(_hDC);

	/*WCHAR Buff[32] = L"";
	swprintf_s(Buff, L" HP : %d ", m_HP);
	TextOut(_hDC, m_Info.X, m_Info.Y, Buff, lstrlenW(Buff));

	WCHAR Buff1[32] = L"";
	swprintf_s(Buff1, L" 좌표 : %f , %f ", m_Info.X,m_Info.Y);
	TextOut(_hDC, 400, 300, Buff1, lstrlenW(Buff1));

	WCHAR Buff2[32] = L"";
	swprintf_s(Buff2, L" 패턴1 : %d ", m_Patern1Cooltime);
	TextOut(_hDC, 400, 400, Buff2, lstrlenW(Buff2));


	WCHAR Buff3[32] = L"";
	swprintf_s(Buff3, L" 패턴2 : %d ", m_Patern1Cooltime);
	TextOut(_hDC, 400, 400, Buff3, lstrlenW(Buff3));*/



}

void St3_BossMonster::Release(void)
{
}

void St3_BossMonster::Set_Bullet(OBJLIST* _bullet)
{
	m_Bullet = _bullet;
}

void St3_BossMonster::Set_Target(CObj* _target)
{
	m_Target = _target;
}

void St3_BossMonster::Render_Head(HDC _hDC)
{
	Rectangle(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void St3_BossMonster::Render_Chain(HDC _hDC)
{
	for (auto& i : m_ChainBody)
	{
		Ellipse(_hDC, i.left, i.top, i.right, i.bottom);
	}
}

void St3_BossMonster::Update_Chain()
{
	for (int i = 0; i < 15; ++i)
	{
		m_ChainBody[i].left = long(m_Chain[i].x - (St3_BOSS_CHAIN_SIZE * 0.5f));
		m_ChainBody[i].top = long(m_Chain[i].y - (St3_BOSS_CHAIN_SIZE * 0.5f));
		m_ChainBody[i].right = long(m_Chain[i].x + (St3_BOSS_CHAIN_SIZE * 0.5f));
		m_ChainBody[i].bottom = long(m_Chain[i].y + (St3_BOSS_CHAIN_SIZE * 0.5f));
	}
}

void St3_BossMonster::Create_FireBullet()
{
	m_Point[OBJECT::POINT_TYPE_AIM] = { m_Body.left,(long)m_Info.Y };
	CObj* temp =CAbstractFactory<St3_FireBullet>::Create(
		m_Point[OBJECT::POINT_TYPE_AIM],
		m_Radian,
		OBJID::MONSTER
	);
	static_cast<St3_FireBullet*>(temp)->Set_RangeTime(80);
	m_Bullet->push_back(temp);
}

void St3_BossMonster::Create_MineBullet()
{
	CObj* temp = CAbstractFactory<St3_MineBullet>::Create();
	temp->Set_Type(OBJID::END);
	temp->Move_Pos(m_Info.X + (rand() % 300) - 150, m_Info.Y + (rand() % 300) - 150);
	m_Bullet->push_back(temp);
}

void St3_BossMonster::Default_Moving()
{
	if (m_DefaultTimeBool == true)
	{
		++m_DefaultTime;
		if (m_DefaultTime >= 22)
			m_DefaultTimeBool = false;
	}
	else
	{
		--m_DefaultTime;
		if (m_DefaultTime <= -22)
			m_DefaultTimeBool = true;
	}

	m_Radian = PI * 3 / 2;;
	m_Info.X += (m_DefaultTime /6) * cosf(m_Radian);
	m_Info.Y += (m_DefaultTime / 6) * sinf(m_Radian);

}

void St3_BossMonster::Patern1()
{
	POINT temp;
	switch (m_PaternCheck)
	{
	case 0:

		
		temp.x = 400;
		temp.y = -200;
		Update_Radian(temp);
		m_Info.X += 5 * cosf(m_Radian);
		m_Info.Y += 5 * sinf(m_Radian);

		if (m_Info.Y <= -200)
			++m_PaternCheck;

		break;
	case 1:

		 temp;
		temp.x = -200;
		temp.y = 300;
		Update_Radian(temp);
		m_Info.X += 10 * cosf(m_Radian);
		m_Info.Y += 10 * sinf(m_Radian);

		if (m_Info.X <= -200)
			++m_PaternCheck;
		break;

	case 2:

		 temp;
		temp.x = 400;
		temp.y = 800;
		Update_Radian(temp);
		m_Info.X += 10 * cosf(m_Radian);
		m_Info.Y += 10 * sinf(m_Radian);

		if (m_Info.Y >= 800)
			++m_PaternCheck;
		break;

	case 3:

		 temp;
		temp.x = 1000;
		temp.y = 300;
		Update_Radian(temp);
		m_Info.X += 10 * cosf(m_Radian);
		m_Info.Y += 10 * sinf(m_Radian);

		if (m_Info.X >= 1000)
			++m_PaternCheck;
		break;

	case 4: //화염방사기 위치 선정
		if (true)
		{
			temp.x = 700;
			temp.y = 50;
			Update_Radian(temp);
			m_Info.X += 3 * cosf(m_Radian);
			m_Info.Y += 3 * sinf(m_Radian);

			if (m_Info.Y <= 150)
				++m_PaternCheck;
		}
		else
		{
			 temp;
			temp.x = 400;
			temp.y = 800;
			Update_Radian(temp);
			m_Info.X += 3 * cosf(m_Radian);
			m_Info.Y += 3 * sinf(m_Radian);

			if (m_Info.Y <= 200)
				++m_PaternCheck;

		}
		break;

	case 5: //화염방사

		m_Radian = PI;
		Create_FireBullet();
		m_Info.Y += 1;
		--m_FireTime;
		if (m_FireTime <= 0)
		{
			m_FireTime = 120;
			++m_PaternCheck;
		}
		break;

	case 6:
		temp;
		temp.x = 400;
		temp.y = 300;
		Update_Radian(temp);
		m_Info.X += 5 * cosf(m_Radian);
		m_Info.Y += 5 * sinf(m_Radian);

		POINT temp2;
		temp2.x = m_Info.X;
		temp2.y = m_Info.Y;

		if (20 > St3_Function::Distance<POINT>(&temp, &temp2))
		{
			m_DefaultTimeBool = true;
			m_PaternCheck = 0;
			m_Patern1 = false;
			m_Patern1Cooltime = 300;
		}

	default:
		break;
	}

}

void St3_BossMonster::Pattern2()
{
	POINT temp;
	switch (m_PaternCheck)
	{
	case 0:


		temp.x = 400;
		temp.y = -200;
		Update_Radian(temp);
		m_Info.X += 5 * cosf(m_Radian);
		m_Info.Y += 5 * sinf(m_Radian);

		if (m_Info.Y <= -200)
			++m_PaternCheck;

		break;
	case 1:// 출발 지점

		temp;
		temp.x = -100;
		temp.y = -100;
		Update_Radian(temp);
		m_Info.X += 10 * cosf(m_Radian);
		m_Info.Y += 10 * sinf(m_Radian);

		if (m_Info.X <= -100)
			++m_PaternCheck;
		break;

	case 2: //폭격1

		temp;
		temp.x = 900;
		temp.y = 700;
		Update_Radian(temp);
		m_Info.X += 10 * cosf(m_Radian);
		m_Info.Y += 10 * sinf(m_Radian);

		if (m_Body.left > 50
			&& m_Body.top > 30
			&& m_Body.right < 780
			&& m_Body.bottom < 600)
		{
			Create_MineBullet();
		}

		if (m_Info.X >= 900)
			++m_PaternCheck;
		break;

	case 3:

		temp;
		temp.x = -50;
		temp.y = 650;
		Update_Radian(temp);
		m_Info.X += 10 * cosf(m_Radian);
		m_Info.Y += 10 * sinf(m_Radian);

		if (m_Info.X <= -50)
			++m_PaternCheck;
		break;

	case 4: // 폭격2
		if (true)
		{
			temp.x = 850;
			temp.y = -50;
			Update_Radian(temp);

			if (m_Body.left > 50
				&& m_Body.top > 30
				&& m_Body.right < 780
				&& m_Body.bottom < 600)
			{
				Create_MineBullet();
			}
			m_Info.X += 10 * cosf(m_Radian);
			m_Info.Y += 10 * sinf(m_Radian);

			if (m_Info.Y <= -50)
				++m_PaternCheck;
		}

		break;

	case 5:
	


			temp;
			temp.x = 850;
			temp.y = 300;
			Update_Radian(temp);
			m_Info.X += 10 * cosf(m_Radian);
			m_Info.Y += 10 * sinf(m_Radian);

			if (m_Info.Y >= 300)
			{
				++m_PaternCheck;
				m_Delay = 180;
			}
			break;


	case 6: // 폭격3
		--m_Delay;
		if (m_Delay <= 0)
		{
			temp.x = -50;
			temp.y = 300;
			Update_Radian(temp);

			if (m_Body.left > 50
				&& m_Body.top > 30
				&& m_Body.right < 780
				&& m_Body.bottom < 600)
			{
				Create_MineBullet();
			}
			m_Info.X += 15 * cosf(m_Radian);
			m_Info.Y += 15 * sinf(m_Radian);

			if (m_Info.X <= -50)
			{
				++m_PaternCheck;
				m_Delay = 180;
			}
		}

		break;

	case 7:
		--m_Delay;
		if (m_Delay <= 0)
		{
			temp;
			temp.x = 400;
			temp.y = 300;
			Update_Radian(temp);
			m_Info.X += 5 * cosf(m_Radian);
			m_Info.Y += 5 * sinf(m_Radian);

			POINT temp2;
			temp2.x = m_Info.X;
			temp2.y = m_Info.Y;

			if (m_Info.X > 400)
			{
				m_DefaultTimeBool = true;
				m_PaternCheck = 0;
				m_Patern2 = false;
				m_Patern2Cooltime = 300;
				m_Delay = 180;
			}
		}
		

	default:
		break;
	}
}



