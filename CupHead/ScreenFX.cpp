#include "ScreenFX.h"
#include "Image.h"
#include "ImageManager.h"

ScreenFX::ScreenFX()
{
}

void ScreenFX::Init()
{
	FrameSpeed = 10.f;

	// 합치면 너무너무너무 너무너무너무너무 너무너무너무 커서 한장씩 불러요
	for (int i = 0; i < 127; ++i)
	{
		string Key = "cuphead_screen_fx_" + to_string(i);
		string StringFilePath = "Image/CupHead/Screen/FX/" + Key + ".bmp";
		wstring WideString = wstring(StringFilePath.begin(), StringFilePath.end());
		const wchar_t* FilePath = WideString.c_str();
		Images.push_back(ImageManager::GetInstance()->AddImage(Key, FilePath, 1024, 512, 1, 1, true, RGB(255, 0, 255)));
	}
}

void ScreenFX::Update()
{
	UpdateFrame();
}

void ScreenFX::Render(HDC hdc)
{
	if (!Images.empty() && CurFrameIndex < Images.size())
		Images[CurFrameIndex]->FrameRender(hdc, WINSIZE_X * 0.5f, WINSIZE_Y * 0.5f, 0, 0);
}

void ScreenFX::UpdateFrame()
{
	FrameTime += FrameSpeed * TimerManager::GetInstance()->GetDeltaTime();
	CurFrameIndex = (int)FrameTime;

	if (CurFrameIndex >= 127)
		CurFrameIndex = FrameTime = 0.f;
}

void ScreenFX::Release()
{
}

ScreenFX::~ScreenFX()
{
}