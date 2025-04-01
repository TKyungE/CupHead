#pragma once
#include "GameObject.h"

class Image;
class ScreenFX;
class LevelManager;
class MainGame : public GameObject
{
public:
	MainGame();
	~MainGame();

	void Init();	// override (�θ�Ŭ������ ���� �Լ��̸�, ������ �ٸ��� �����ϰ� ���� ��)
	// <-> overload (���� �Լ� �̸�, �Ű����� Ÿ�԰� ������ �ٸ��� �ٸ� �Լ��� ó��)
	void Release();
	void Update();
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	HDC hdc;
	wchar_t szText[128];

	Image* backBuffer;
	ScreenFX* ScreenFx;
	LevelManager* LevelManager;

	bool bPause;
};

