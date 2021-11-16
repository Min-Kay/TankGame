#pragma once

#define		WINCX	800
#define		WINCY	600	
#define		PURE	= 0

#define		SAFE_DELETE(p)		if(p) { delete p;  p = nullptr; }

#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1

#define OBJLIST list<CObj*>

extern		HWND	g_hWnd;


#define RESPONE_X 400.f
#define RESPONE_Y 500.f

#define PLAYER_WIDTH 30
#define PLAYER_HEIGHT 30
#define PLAYER_SPEED 30

#define PLAYER_HP 1
#define PLAYER_ATTACK 5
#define PLAYER_WIDTH 30