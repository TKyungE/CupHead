#include "Effect.h"
#include "EffectManager.h"

void EffectManager::Init()
{

}

void EffectManager::Update()
{
	for (auto& iter : Effects)
	{
		iter->Update();
	}
}

void EffectManager::Release()
{
	for (auto& iter : Effects)
	{
		iter->Release();
		delete iter;
	}

	Effects.clear();
}

void EffectManager::AddEffect(string _ImageName, void* _Desc)
{
	Effect* Temp = new Effect(*(EffectDesc*)_Desc);
	Image* Dest = ImageManager::GetInstance()->FindImage(_ImageName);
	
	if (nullptr == Dest)
	{	
		MessageBox(g_hWnd, TEXT("AddEffect 실패, 이미지가 존재하지 않습니다."), L"경고", MB_OK);
		return;
	}

	Temp->SetImage(Dest);
	Effects.push_back(Temp);
	
}

void EffectManager::AddEffect(string _ImageName, float _LifeTime, int _MaxLoopCnt, bool _IsTraceTarget, GameObject* TraceTarget)
{
	EffectDesc Desc;
	memset(&Desc, 0, sizeof(Desc));
	Desc.MaxLifeTime = _LifeTime;
	Desc.MaxLoopCnt = _MaxLoopCnt;
	Desc.IsTraceTarget = _IsTraceTarget;
	Desc.TraceTarget = TraceTarget;

	Effect* Temp = new Effect(Desc);
	Image* Dest = ImageManager::GetInstance()->FindImage(_ImageName);

	if (nullptr == Dest)
	{
		MessageBox(g_hWnd, TEXT("AddEffect 실패, 이미지가 존재하지 않습니다."), L"경고", MB_OK);
		return;
	}

	Temp->SetImage(Dest);
	Effects.push_back(Temp);

}


