#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Timer.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "EffectManager.h"

#include "LaughProjectile.h"
#include "StarProjectile.h"
#include "Tornado.h"

void MainGame::Init()
{
	ImageManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();

	hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		/*MessageBox(g_hWnd,
			TEXT("����� ���� ����"), TEXT("���"), MB_OK);*/
	}
	// C:\Programming\Git\CupHead\CupHead\CupHead\Image\CupHead\BackGround

	backGround = new Image();
	//if (FAILED(backGround->Init(TEXT("Image/BackGround.bmp"), WINSIZE_X, WINSIZE_Y)))
	if (FAILED(backGround->Init(TEXT("Image/background1.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		/*MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp ���� ����"), TEXT("���"), MB_OK);*/
	}

	Objectmanager = ObjectManager::GetInstance();
	Objectmanager->Init();

	collisionManager = CollisionManager::GetInstance();
	collisionManager->Init();

	EffectManager = EffectManager::GetInstance();
	EffectManager->Init();
}

void MainGame::Release()
{
	if (backGround)
	{
		backGround->Release();
		delete backGround;
		backGround = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	if (collisionManager)
	{
		collisionManager->Release();
		collisionManager = nullptr;
	}

	if (Objectmanager)
	{
		Objectmanager->Release();
		Objectmanager = nullptr;
	}

	if (EffectManager)
	{
		EffectManager->Release();
		EffectManager = nullptr;
	}

	ReleaseDC(g_hWnd, hdc);

	KeyManager::GetInstance()->Release();
	ImageManager::GetInstance()->Release();

}

void MainGame::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
		bPause = !bPause;

	if (bPause)
		return;

	// Test. Tornado
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RBUTTON))
	{
		Tornado* tornado = new Tornado();
		tornado->Init(mousePos);
		Objectmanager->AddObject(tornado, OBJTYPE::OBJ_MONSTER_WEAPON);
	}

	// Test Star
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RETURN))
	{
		for (int i = 0; i < 3; ++i)
		{
			StarProjectile* star = new StarProjectile(StarType(i));
			star->Init({ mousePos.x, float(mousePos.y + (i - 1) * 150) });
			Objectmanager->AddObject(star, OBJTYPE::OBJ_MONSTER_WEAPON);
		}
	}

	// Test Laugh
	//if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RETURN))
	//{
	//	LaughProjectile* Laugh = new LaughProjectile();
	//	Laugh->Init(mousePos);
	//	ObjectManager::GetInstance()->AddObject(Laugh, OBJTYPE::OBJ_MONSTER_WEAPON);
	//}


	if (Objectmanager)
		Objectmanager->Update();
	if (collisionManager)
		collisionManager->Update();

	if (nullptr != EffectManager)
	{
		EffectManager->Update();
	}
}

void MainGame::Render()
{
	// ����ۿ� ���� ����
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backGround->Render(hBackBufferDC);

	wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), (int)mousePos.x, (int)mousePos.y);
	TextOut(hBackBufferDC, 20, 60, szText, (int)wcslen(szText));


	if (Objectmanager)
		Objectmanager->Render(hBackBufferDC);

	if (collisionManager)
		collisionManager->Render(hBackBufferDC);

	if (EffectManager)
	{
		EffectManager->Render(hBackBufferDC);
	}
		

	TimerManager::GetInstance()->Render(hBackBufferDC);

	// ����ۿ� �ִ� ������ ���� hdc�� ����
	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		mousePos.x = LOWORD(lParam);
		mousePos.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
	:bPause(false)
{
}

MainGame::~MainGame()
{
}
