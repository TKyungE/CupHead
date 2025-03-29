#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "EnemyManager.h"
#include "Timer.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "EffectManager.h"
/*
	�ǽ�1. �̿��� ���� ������
	�ǽ�2. ��� �ٲٱ� (ŷ���� �ִϸ��̼� ���)
*/


#include "SagittariusStar.h"
#include "SagittariusArrow.h"

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
	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/BackGround.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		/*MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp ���� ����"), TEXT("���"), MB_OK);*/
	}

	// �������� ���ʹ̸Ŵ���.. �ּ�Ǯ�� �� �߻� 
	//enemyManager = new EnemyManager();
	//enemyManager->Init();

	Objectmanager = ObjectManager::GetInstance();
	Objectmanager->Init();

	collisionManager = CollisionManager::GetInstance();
	collisionManager->Init();

	EffectManager = EffectManager::GetInstance();
	EffectManager->Init();
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
	// ���°� �׽�Ʈ �ڵ�
	{
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
		{
			SagittariusStar* star = new SagittariusStar(mousePos, 10.f, 180.f);
			star->Init();
			Objectmanager->AddObject(star, OBJTYPE::OBJ_MONSTER_WEAPON);

			SagittariusStar* star1 = new SagittariusStar(mousePos, 10.f, 125.f);
			star1->Init();
			Objectmanager->AddObject(star1, OBJTYPE::OBJ_MONSTER_WEAPON);

			SagittariusStar* star2 = new SagittariusStar(mousePos, 10.f, 225.f);
			star2->Init();
			Objectmanager->AddObject(star2, OBJTYPE::OBJ_MONSTER_WEAPON);

			SagittariusArrow* arrow = new SagittariusArrow(mousePos, { 50.f,50.f });
			arrow->Init();
			Objectmanager->AddObject(arrow, OBJTYPE::OBJ_MONSTER_WEAPON);
		}
	}

	if (Objectmanager)
		Objectmanager->Update();

	if (enemyManager)
		enemyManager->Update();
	if (collisionManager)
	{
		collisionManager->Update();

		//  ����ĳ��Ʈ ����		
		//FHitResult HitResult;
		//bool bCheck = collisionManager->LineTraceByObject(HitResult, OBJTYPE::OBJ_MONSTER, { 0.f,0.f }, mousePos, nullptr, true, true, 0.f, 100);
		//if (bCheck)		// �¾Ҵ�.
		//	HitResult.HitObj->TakeDamage();
	}

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

	if (enemyManager)
		enemyManager->Render(hBackBufferDC);
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
{
}

MainGame::~MainGame()
{
}
