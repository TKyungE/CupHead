// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>
#include <vector>
#include <map>
#include <random>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"


/*
	컴파일러에서 해당 코드를 뒤에 정의된 코드로 변경한다.
*/
#define WINSIZE_X	1280
#define WINSIZE_Y	720
#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)
#define PI 3.141592f

enum OBJTYPE { OBJ_PLAYER,OBJ_MONSTER,OBJ_PLAYER_WEAPON,OBJ_MONSTER_WEAPON,OBJ_UI, OBJ_UPPERUI,OBJ_ETC, OBJ_END };

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

/*
	extern 키워드 : 변수나 함수가 다른 파일에 정의되어 있다 라는
	사실을 알리는 키워드.
*/
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern FPOINT g_MousePos;

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

#endif // _DEBUG

// random
extern random_device rd;
extern default_random_engine dre;
extern uniform_int_distribution<int> uid;