#pragma once

///////////////////////////////////////////////////////////////////////////
// ���� 1ȸ�� �߰��Ѵ�! ���� ÷�� ������ �ڵ� 1ȸ�� �Է�
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
///////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

#endif // _DEBUG
///////////////////////////////////////////////////////////////////////////

#include "Define.h"
#include "Struct.h"
#include "Enum.h"
