#pragma once
#include "Def_St3_Monster.h"
/// WINAPI

#define		WINCX	800
#define		WINCY	600	
#define		PURE	= 0

#define		SAFE_DELETE(p)		if(p) { delete p;  p = nullptr; }

#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1


extern		HWND	g_hWnd;

#define RESPONE_X 400.f
#define RESPONE_Y 500.f

#define	PI		3.141592f


/// KeySetting

#define KEY_UP 'W'
#define KEY_DOWN 'S'
#define KEY_LEFT 'A'
#define KEY_RIGHT 'D'
#define KEY_ATTACK VK_LBUTTON


/// Game

#define OBJLIST list<CObj*>
#define OBJVEC	vector<CObj*>

///PLAYER

#define PLAYER_WIDTH 30
#define PLAYER_HEIGHT 30
#define PLAYER_SPEED 30

#define PLAYER_HP 1
#define PLAYER_ATTACK 5
#define PLAYER_WIDTH 30

#define RESPONE_X 400.f
#define RESPONE_Y 500.f

#define INGAME_LEFT 0
#define INGAME_TOP 0
#define INGAME_RIGHT 800
#define INGAME_BOTTOM 600

#define PLAYER_WIDTH 30
#define PLAYER_HEIGHT 30
#define PLAYER_SPEED 10

#define PLAYER_HP 1
#define PLAYER_ATTACK 5
#define PLAYER_WIDTH 30

#define PLAYER_CANNON_LEN 30


/// BULLET

#define BULLET_WIDTH 5
#define BULLET_HEIGHT 5
#define BULLET_SPEED 5.f

#define BULLET_HP 1
#define BULLET_ATTACK 5

/// Satellite

#define SATELLITE_SPEED 5




