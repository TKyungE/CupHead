#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "BackGround.h"
#include "ScreenFX.h"
#include "LevelManager.h"

void MainGame::Init()
{
	ImageManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();

	hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		/*MessageBox(g_hWnd,
			TEXT("ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½"), TEXT("ï¿½ï¿½ï¿?"), MB_OK);*/
	}
	// C:\Programming\Git\CupHead\CupHead\CupHead\Image\CupHead\BackGround

	LevelManager = LevelManager::GetInstance();
	LevelManager->Init();

	ScreenFx = new ScreenFX();
	ScreenFx->Init();
}

void MainGame::Release()
{
	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	if (ScreenFx)
	{
		ScreenFx->Release();
		delete ScreenFx;
		ScreenFx = nullptr;
	}

	if (LevelManager)
	{
		LevelManager->Release();
		LevelManager = nullptr;
	}

	ReleaseDC(g_hWnd, hdc);

	KeyManager::GetInstance()->Release();
	ImageManager::GetInstance()->Release();
}

void MainGame::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_ESCAPE))
		bPause = !bPause;

	if (bPause)
		return;

	if (LevelManager)
		LevelManager->Update();

	if (ScreenFx)
		ScreenFx->Update();
}

void MainGame::Render()
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	BitBlt(hBackBufferDC, 0, 0, WINSIZE_X, WINSIZE_Y, hBackBufferDC, 0, 0, WHITENESS);

	if (LevelManager)
		LevelManager->Render(hBackBufferDC);

#ifdef _DEBUG 
	wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), (int)g_MousePos.x, (int)g_MousePos.y);
	TextOut(hBackBufferDC, 20, 60, szText, (int)wcslen(szText));
#endif 

	TimerManager::GetInstance()->Render(hBackBufferDC);

	if (ScreenFx && LevelManager->GetLevelState() != ELevelState::Logo)
		ScreenFx->Render(hBackBufferDC);

	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		g_MousePos.x = LOWORD(lParam);
		g_MousePos.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
	:backBuffer(nullptr), ScreenFx(nullptr), LevelManager(nullptr), bPause(false)
{
}

MainGame::~MainGame()
{
}
