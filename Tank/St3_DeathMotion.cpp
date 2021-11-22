#include "stdafx.h"
#include "St3_DeathMotion.h"

St3_DeathMotion::St3_DeathMotion(short _size, POINT _locate)
    :   m_FPS(0)
    ,   m_Size(_size*0.5f)
    ,   m_Point(_locate)
    ,   m_Dead(false)
    ,   m_Radian(0)
{
    ZeroMemory(&m_Body, sizeof(RECT));
    m_FPS = 0;
    m_Dead = false;
}

St3_DeathMotion::~St3_DeathMotion()
{
}

void St3_DeathMotion::Initialize(void)
{

}

int St3_DeathMotion::Update(void)
{
    if (m_ReversePoint)
    {
        m_FPS-=4;

        if(m_FPS <= 0)
            m_Dead = true;
    }
    else
    {
        if (m_FPS >= 40)
            m_ReversePoint = true;

        m_FPS+=4;
    }


    Update_Rect();

    return 0;
}

void St3_DeathMotion::Late_Update(void)
{
}

void St3_DeathMotion::Render(HDC _hDC)
{
    POINT temp;

	HPEN hpenOld = NULL;


	HPEN hpen = CreatePen(PS_SOLID, 1, RGB(96, 96, 96));
	hpenOld = (HPEN)::SelectObject(_hDC, (HGDIOBJ)hpen);


    //for (int i = 0; i < 8; ++i)                            
    //{                                                      

    //    temp.x = m_Point.x + m_Size/2 * m_FPS / 45 * cosf(m_Radian + (PI / 4 * i));
    //    temp.y = m_Point.y + m_Size/2 * m_FPS / 45 * sinf(m_Radian + (PI / 4 * i));
    //                                                       
    //    MoveToEx(_hDC, temp.x, temp.y, NULL);              
    //                                                       
    //    temp.x = m_Point.x + m_Size/3 * m_FPS / 45 * cosf(m_Radian + (PI / 4 * i));
    //    temp.y = m_Point.y + m_Size/3 * m_FPS / 45 * sinf(m_Radian + (PI / 4 * i));

    //    LineTo(_hDC, temp.x , temp.y);
    //  /*  LineTo(_hDC, temp.x + m_Size * m_FPS / 90, temp.y + m_Size * m_FPS / 90);*/
    //}

	hpen = (HPEN)::SelectObject(_hDC, hpenOld);
	DeleteObject(hpen);	// 생성한 펜 삭제

    Ellipse(_hDC, m_Body.left, m_Body.top, m_Body.right, m_Body.bottom);
}

void St3_DeathMotion::Release(void)
{
}

void St3_DeathMotion::Update_Rect()
{

    m_Body.left = m_Point.x - ((m_Size * m_FPS / 40) * 0.5f);
    m_Body.right = m_Point.x + ((m_Size * m_FPS / 40) * 0.5f);
    m_Body.top = m_Point.y - ((m_Size * m_FPS / 40) * 0.5f);
    m_Body.bottom = m_Point.y + ((m_Size * m_FPS / 40) * 0.5f);
}
