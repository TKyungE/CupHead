#pragma once
#include "GameObject.h"

class Timer;
class Image;
class EnemyManager;
class CollisionManager;
class ObjectManager;
class EffectManager;
class MainGame : public GameObject
{
private:
	HDC hdc;
	PAINTSTRUCT ps;
	FPOINT mousePos;
	wchar_t szText[128];

	Image* backBuffer;
	Image* backGround;
	EnemyManager* enemyManager;
	CollisionManager* collisionManager;
	ObjectManager* Objectmanager;
	EffectManager* EffectManager;
	Timer* timer;

	bool bPause;
public:
	void Init();	// override (부모클래스와 같은 함수이름, 로직을 다르게 구현하고 싶을 때)
					// <-> overload (같은 함수 이름, 매개변수 타입과 갯수가 다르면 다른 함수로 처리)
	void Release();	
	void Update();	
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

