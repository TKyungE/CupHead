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
	void Init();	// override (�θ�Ŭ������ ���� �Լ��̸�, ������ �ٸ��� �����ϰ� ���� ��)
					// <-> overload (���� �Լ� �̸�, �Ű����� Ÿ�԰� ������ �ٸ��� �ٸ� �Լ��� ó��)
	void Release();	
	void Update();	
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

