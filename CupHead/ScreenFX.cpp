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
		string number = "";
		for (int j = 0; j < 4 - to_string(i).size(); ++j)
			number += '0';
	
		string Key = "cuphead_screen_fx_" + number + to_string(i);
		string StringFilePath = "Image/CupHead/UI/Screen/FX/" + Key + ".bmp";
		wstring WideString = wstring(StringFilePath.begin(), StringFilePath.end());
		const wchar_t* FilePath = WideString.c_str();
		Image* Image = ImageManager::GetInstance()->AddImage(Key, FilePath, 1024, 512, 1, 1, true, RGB(255, 0, 255));
		Image->SetScale(2.f, 2.f);
		Images.push_back(Image);
	}
}

void ScreenFX::Update()
{
	UpdateFrame();
}

void ScreenFX::Render(HDC hdc)
{
	if (!Images.empty() && CurFrameIndex < Images.size())
		Images[CurFrameIndex]->FrameRenderAlpha(hdc, WINSIZE_X * 0.5f, WINSIZE_Y * 0.5f, 0, 0,false,30);
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