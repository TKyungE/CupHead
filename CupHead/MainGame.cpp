#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "EnemyManager.h"
#include "Timer.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
/*
	실습1. 이오리 집에 보내기
	실습2. 배경 바꾸기 (킹오파 애니메이션 배경)
*/



void MainGame::Init()
{
	ImageManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();

	hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
	}
	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/BackGround.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp 생성 실패"), TEXT("경고"), MB_OK);
	}

	// 선생님의 에너미매니저.. 주석풀면 릭 발생 
	//enemyManager = new EnemyManager();
	//enemyManager->Init();

	Objectmanager = ObjectManager::GetInstance();
	Objectmanager->Init();

	collisionManager = CollisionManager::GetInstance();
	collisionManager->Init();
}

void MainGame::Release()
{
	if (enemyManager)
	{
		enemyManager->Release();
		delete enemyManager;
		enemyManager = nullptr;
	}

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

	ReleaseDC(g_hWnd, hdc);

	KeyManager::GetInstance()->Release();
	ImageManager::GetInstance()->Release();
}

void MainGame::Update()
{
	if (Objectmanager)
		Objectmanager->Update();

	if (enemyManager)
		enemyManager->Update();
	if (collisionManager)
	{
		collisionManager->Update();

		//  레이캐스트 사용법		
		FHitResult HitResult;
		bool bCheck = collisionManager->LineTraceByObject(HitResult, OBJTYPE::OBJ_MONSTER, { 0.f,0.f }, mousePos, nullptr, true, true, 0.f, 100);
		if (bCheck)		// 맞았다.
			HitResult.HitObj->TakeDamage();
	}
}

void MainGame::Render()
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backGround->Render(hBackBufferDC);

	wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePos.x, mousePos.y);
	TextOut(hBackBufferDC, 20, 60, szText, (int)wcslen(szText));


	if (Objectmanager)
		Objectmanager->Render(hBackBufferDC);

	if (enemyManager)
		enemyManager->Render(hBackBufferDC);
	if (collisionManager)
		collisionManager->Render(hBackBufferDC);

	TimerManager::GetInstance()->Render(hBackBufferDC);

	// 백버퍼에 있는 내용을 메인 hdc에 복사
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
{
}

MainGame::~MainGame()
{
}
