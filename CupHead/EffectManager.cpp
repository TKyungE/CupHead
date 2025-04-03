#include "Effect.h"
#include "Image.h"
#include "EffectManager.h"

void EffectManager::Init()
{

}

void EffectManager::Update()
{
	for (auto iter = Effects.begin(); iter != Effects.end();)
	{
		(*iter)->Update();
		if (true == (*iter)->IsDead())
		{
			(*iter)->Release();
			delete (*iter);
			iter = Effects.erase(iter);
		}

		else
		{
			++iter;
		}
	}


	//for(auto iter = TraceEffects.begin(); iter != TraceEffects.end();)
	//{
	//	if (true == (*iter).first->IsDead())
	//	{
	//		for (auto iter2 = (*iter).second.begin(); iter2 != (*iter).second.end();)
	//		{
	//			(*iter2)->Release();
	//			delete (*iter2);
	//			(iter2) = (*iter).second.erase(iter2);
	//		}

	//		iter = TraceEffects.erase(iter);
	//	}

	//	else
	//	{
	//		for (auto iter2 = (*iter).second.begin(); iter2 != (*iter).second.end();)
	//		{
	//			(*iter2)->Update();

	//			if (true == (*iter2)->IsDead())
	//			{
	//				(*iter2)->Release();
	//				delete (*iter2);
	//				(iter2) = (*iter).second.erase(iter2);
	//			}

	//			else
	//			{
	//				++iter2;
	//			}
	//		}

	//		++iter;
	//	}
	//}

}

void EffectManager::Render(HDC hdc)
{
	for (auto& iter : Effects)
	{
		iter->Render(hdc);
	}

	//for (auto& iter : TraceEffects)
	//{
	//	for (auto& iter2 : iter.second)
	//	{
	//		iter2->Render(hdc);
	//	}
	//}
}

void EffectManager::Release()
{
	for (auto& iter : Effects)
	{
		iter->Release();
		delete iter;
	}

	//for (auto& iter : TraceEffects)
	//{
	//	for (auto& iter2 : iter.second)
	//	{
	//		iter2->Release();
	//		delete iter2;
	//	}
	//}
	//TraceEffects.clear();

	Effects.clear();
	ReleaseInstance();
}

void EffectManager::AddEffect(string _ImageName, FPOINT _Pos, void* _Desc)
{
	Image* Dest = ImageManager::GetInstance()->FindImage(_ImageName);

	if (nullptr == Dest)
	{
		MessageBox(g_hWnd, TEXT("AddEffect 실패, 이미지가 존재하지 않습니다."), L"경고", MB_OK);
		return;
	}

	Effect* Temp = new Effect(_Pos,*(EffectDesc*)_Desc);
	Temp->SetImage(Dest);
	Temp->Init();
	Effects.push_back(Temp);

	//if ((*(EffectDesc*)_Desc).IsTraceTarget && nullptr != (*(EffectDesc*)_Desc).TraceTarget)
	//{
	//	TraceEffects[(*(EffectDesc*)_Desc).TraceTarget].push_back(Temp);
	//}

	//else
	//{
	//	Effects.push_back(Temp);
	//}
}

void EffectManager::AddEffect(string _ImageName, FPOINT _Pos, float _MaxLifeTime, FPOINT _Offset, int _MaxLoopCnt, bool _IsTraceTarget, GameObject* TraceTarget)
{
	Image* Dest = ImageManager::GetInstance()->FindImage(_ImageName);

	if (nullptr == Dest)
	{
		MessageBox(g_hWnd, TEXT("AddEffect 실패, 이미지가 존재하지 않습니다."), L"경고", MB_OK);
		return;
	}

	EffectDesc Desc;
	memset(&Desc, 0, sizeof(Desc));
	Desc.MaxLifeTime = _MaxLifeTime;
	Desc.OffsetPos = _Offset;
	Desc.MaxLoopCnt = _MaxLoopCnt;
	Desc.IsTraceTarget = _IsTraceTarget;
	Desc.TraceTarget = TraceTarget;

	Effect* Temp = new Effect(_Pos, Desc);

	// SetFlip 필요해보임
	Temp->SetImage(Dest);
	Temp->Init();
	Effects.push_back(Temp);

	//if (Desc.IsTraceTarget && nullptr != Desc.TraceTarget)
	//{
	//	TraceEffects[Desc.TraceTarget].push_back(Temp);
	//}

	//else
	//{
	//	Effects.push_back(Temp);
	//}
}

void EffectManager::AddEffectDefault(string _ImageName, FPOINT _Pos, float _MaxLifeTime)
{
	Image* Dest = ImageManager::GetInstance()->FindImage(_ImageName);

	if (nullptr == Dest)
	{
		MessageBox(g_hWnd, TEXT("AddEffect 실패, 이미지가 존재하지 않습니다."), L"경고", MB_OK);
		return;
	}

	EffectDesc Desc;
	memset(&Desc, 0, sizeof(Desc));
	Desc.MaxLifeTime = _MaxLifeTime;
	Desc.MaxLoopCnt = 1;
	Effect* Temp = new Effect(_Pos, Desc);

	// SetFlip 필요해보임
	Temp->SetImage(Dest);
	Temp->Init();
	Effects.push_back(Temp);
}



