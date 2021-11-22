#include "stdafx.h"
#include "St3_ChaseBullet.h"
#include "CollisionMgr.h"
#include "St3_Func.h"
#include "Def_St3.h"

St3_ChaseBullet::St3_ChaseBullet()
{
}

St3_ChaseBullet::~St3_ChaseBullet()
{
	Release();
}

int St3_ChaseBullet::Update(void)
{

	Update_Rect();

	if (Delay())
	{
		m_Info.X += m_DelayTime/3 * cos(m_Radian+PI*3/4);
		m_Info.Y += m_DelayTime/3 * sin(m_Radian+PI*3/4);
		return 0;
	}


	POINT temp = { m_Info.X,m_Info.Y };


	if (m_Bomb)
	{
		m_Info.Width = m_BombTime*6;
		m_Info.Height = m_BombTime*6;
		--m_BombTime;
		if(m_BombTime<=0)
			m_Dead = true;

		return 0;
	}


	
	if (m_TaretingVaild == true) //타겟이있을때 타겟으로이동(연사력 처리때 겹치면 오류발생)
	{

		Update_Radian({ (long)m_Target.x,(long)m_Target.y });
		m_Info.X += 12* cos(m_Radian);
		m_Info.Y += 12* sin(m_Radian);

		if (15 > St3_Function::Distance<POINT>(&temp, &m_Target))
		{
			m_Bomb = true;
		}

	}
	else if(m_TaretingVaild == false)
	{
		Update_Locate(m_Speed); //타겟이없을때 방향으로이동
	}
	
	return 0;
}

void St3_ChaseBullet::Initialize(void)
{
		m_Info.Width = 10;
		m_Info.Height = 10;
		m_Speed = BULLET_SPEED;
		m_Type = OBJID::MISSILE;
		Update_Rect();
		m_DelayTime = 30;
		m_Dir=OBJECT::DIRECTION_TOP;
		m_BombTime = 20;
		m_EngineTime = 10;
}

void St3_ChaseBullet::Render(HDC hDC)
{
	if (m_EngineBool == false)
	{
		--m_EngineTime;

		if (m_EngineTime <= 0)
			m_EngineBool = true;
	}
	else
	{
		++m_EngineTime;

		if (m_EngineTime >= 20)
			m_EngineBool = false;
	}

	if (m_Bomb)
	{
		HBRUSH oBrush;

		HBRUSH Brush1 = CreateSolidBrush(RGB(221, 254,255));
		oBrush = (HBRUSH)SelectObject(hDC, Brush1);
		Ellipse(hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
		SelectObject(hDC, oBrush);
		DeleteObject(Brush1);

		HBRUSH Brush2 = CreateSolidBrush(RGB(250, 250, 250));
		oBrush = (HBRUSH)SelectObject(hDC, Brush2);
		Ellipse(hDC, m_Body.left+m_Info.Width/2, m_Body.top+m_Info.Width / 2, m_Body.right-m_Info.Width / 2, m_Body.bottom- m_Info.Width / 2);
		SelectObject(hDC, oBrush);
		DeleteObject(Brush2);

	}
	else
		Render_Body(hDC);
}

void St3_ChaseBullet::Late_Update(OBJLIST* _objlist)
{

	Check_Out();				//1. 화면밖 검사

	if (m_DelayTime <=0)
	{
		if (m_TaretingVaild == false) //2. 타겟 검사
			Check_Target(_objlist);
		return;
	}



}

void St3_ChaseBullet::Release(void)
{
}

void St3_ChaseBullet::Check_Target(OBJLIST* _objlist)
{
	CObj* temp=nullptr;


	auto iter = _objlist[OBJID::MONSTER].begin();
	for (; iter != _objlist[OBJID::MONSTER].end();)
	{
		if ((*iter)->Get_Direction() != m_Dir && 
			CCollisionMgr::Check_Sphere(this, (*iter), St3_CHASE_RANGE) &&
			!(*iter)->Get_Dead()
			)
		{
			if (temp == nullptr)
				temp = (*iter);

			if(temp && Check_Distance(temp) > Check_Distance(*iter))
				temp = (*iter);
		}
		++iter;
	}


	if (temp)
	{
		m_TargetT = temp;
		m_Target = { (long)temp->Get_Info().X,(long)temp->Get_Info().Y };
		m_TaretingVaild = true;
	}

	return;
}

float St3_ChaseBullet::Check_Distance(CObj* _src)
{
	if (_src)
	{
		float Width = (_src->Get_Info().X - m_Info.X);
		float Height = (_src->Get_Info().Y - m_Info.Y);

		return sqrt(Width * Width + Height * Height);
	}
	else
		return 350;
}

void St3_ChaseBullet::Check_Out()
{
	if (0 >= m_Body.top - m_Speed || //가장자리 충돌처리
		0 >= m_Body.left - m_Speed ||
		600 <= m_Body.bottom + m_Speed ||
		800 <= m_Body.right + m_Speed
		)
	{
		m_Dead = true;
	}
}

bool St3_ChaseBullet::Delay()
{
	if (m_DelayTime <= 0)
		return false;
	else
		--m_DelayTime;

	return true;
}

void St3_ChaseBullet::Render_Body(HDC _hdc)
{
	POINTFLOAT temp1={ 0.f,0.f };
	POINTFLOAT temp2={ 0.f,0.f };
	int len = m_Info.Width;
	float tempR = 0;
	temp1.x = m_Info.X;
	temp1.y = m_Info.Y;

	MoveToEx(_hdc, m_Info.X, m_Info.Y, NULL);

	//1
	tempR = m_Radian-PI*3/4;
	len = m_Info.Width/2;
	temp1.x = temp1.x +len *cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc,temp1.x,temp1.y);

	// 중간선1
	temp2 = temp1;
	tempR = m_Radian+PI/2;
	len = m_Info.Width / 2;
	temp2.x = temp2.x + len * cosf(tempR);
	temp2.y = temp2.y + len * sinf(tempR);
	LineTo(_hdc, temp2.x, temp2.y);
	MoveToEx(_hdc, temp1.x, temp1.y, NULL);

	//2
	tempR = m_Radian - PI;
	len = m_Info.Width;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	//3
	tempR = m_Radian - PI * 3 / 4;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	//4
	tempR = m_Radian - PI;
	len = m_Info.Width/2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	

	//5
	tempR = m_Radian - PI * 3 / 4 +PI;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);


	//중간선2
	temp2 = temp1;
	tempR = m_Radian;
	len = m_Info.Width / 2;
	temp2.x = temp2.x + len * cosf(tempR);
	temp2.y = temp2.y + len * sinf(tempR);
	LineTo(_hdc, temp2.x, temp2.y);
	MoveToEx(_hdc, temp1.x, temp1.y, NULL);


	//6
	tempR = m_Radian+PI/2;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	//----------------------------------------우------------------------------

	MoveToEx(_hdc, m_Info.X, m_Info.Y, NULL);
	temp1.x = m_Info.X;
	temp1.y = m_Info.Y;

	//1
	tempR = m_Radian + PI * 3 / 4;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	// 중간선1
	temp2 = temp1;
	tempR = m_Radian - PI / 2;
	len = m_Info.Width / 2;
	temp2.x = temp2.x + len * cosf(tempR);
	temp2.y = temp2.y + len * sinf(tempR);
	LineTo(_hdc, temp2.x, temp2.y);
	MoveToEx(_hdc, temp1.x, temp1.y, NULL);

	//2
	tempR = m_Radian + PI;
	len = m_Info.Width;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	//3
	tempR = m_Radian + PI * 3 / 4;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);

	//4
	tempR = m_Radian + PI;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);



	//5
	tempR = m_Radian + PI * 3 / 4 + PI;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);


	//중간선2
	temp2 = temp1;
	tempR = m_Radian;
	len = m_Info.Width / 2;
	temp2.x = temp2.x + len * cosf(tempR);
	temp2.y = temp2.y + len * sinf(tempR);
	LineTo(_hdc, temp2.x, temp2.y);
	MoveToEx(_hdc, temp1.x, temp1.y, NULL);


	//6
	tempR = m_Radian - PI / 2;
	len = m_Info.Width / 2;
	temp1.x = temp1.x + len * cosf(tempR);
	temp1.y = temp1.y + len * sinf(tempR);
	LineTo(_hdc, temp1.x, temp1.y);


	if (m_TargetT)
	{
		RECT rc1;
		HBRUSH Brush1 = CreateSolidBrush(RGB(221, 254, 255));
		HBRUSH oBrush;
				oBrush = (HBRUSH)SelectObject(_hdc, Brush1);

		float x1 = m_Info.X + m_Info.Width * 3 * cosf(m_Radian + PI);
		float y1 = m_Info.Y + m_Info.Height * 3 * sinf(m_Radian + PI);

		rc1.left = long(x1 - (m_EngineTime * 2 / 3 * 0.5f));
		rc1.top = long(y1 - (m_EngineTime * 2 / 3 * 0.5f));
		rc1.right = long(x1 + (m_EngineTime * 2 / 3 * 0.5f));
		rc1.bottom = long(y1 + (m_EngineTime * 2 / 3 * 0.5f));

		Ellipse(_hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);

		SelectObject(_hdc, oBrush);
		DeleteObject(Brush1);

		//

		Brush1 = CreateSolidBrush(RGB(0, 254, 255));
		oBrush;
		oBrush = (HBRUSH)SelectObject(_hdc, Brush1);

		x1 = m_Info.X + m_Info.Width * 4 * cosf(m_Radian + PI);
		y1 = m_Info.Y + m_Info.Width * 4 * sinf(m_Radian + PI);

		rc1.left = long(x1 - (m_EngineTime / 2 * 0.5f));
		rc1.top = long(y1 - (m_EngineTime / 2 * 0.5f));
		rc1.right = long(x1 + (m_EngineTime / 2 * 0.5f));
		rc1.bottom = long(y1 + (m_EngineTime / 2 * 0.5f));

		Ellipse(_hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
		SelectObject(_hdc, oBrush);
		DeleteObject(Brush1);

		//

		Brush1 = CreateSolidBrush(RGB(0, 100, 255));
		oBrush;
		oBrush = (HBRUSH)SelectObject(_hdc, Brush1);

		x1 = m_Info.X + m_Info.Width * 5 * cosf(m_Radian + PI);
		y1 = m_Info.Y + m_Info.Width * 5 * sinf(m_Radian + PI);

		rc1.left = long(x1 - (m_EngineTime / 2 * 0.5f));
		rc1.top = long(y1 - (m_EngineTime / 2 * 0.5f));
		rc1.right = long(x1 + (m_EngineTime / 2 * 0.5f));
		rc1.bottom = long(y1 + (m_EngineTime / 2 * 0.5f));

		Ellipse(_hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);

		SelectObject(_hdc, oBrush);
		DeleteObject(Brush1);

	}



	//x1 = m_Info.X + m_Info.Width*1.5 * cosf(m_Radian + PI);
	//y1 = m_Info.Y + m_Info.Width*1.5 * sinf(m_Radian + PI);

	//rc1.left = long(x1 - (m_EngineTime*2/3 * 0.5f));
	//rc1.top = long(y1 - (m_EngineTime*2/3 * 0.5f));
	//rc1.right = long(x1 + (m_EngineTime*2/3 * 0.5f));
	//rc1.bottom = long(y1 + (m_EngineTime*2/3 * 0.5f));

	//Ellipse(_hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
}

