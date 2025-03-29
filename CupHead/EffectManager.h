#pragma once
#include "Singleton.h"
#include "config.h"
#include <list>

class Effect;

enum EFFECTTYPE
{
	EFFECT_NORMAL, EFFECT_LOOP, EFFECT_TRACE, EFFECT_END
};

class EffectManager : public Singleton<EffectManager>
{
	void Init();
	void Update();
	void Release();

	void AddEffect(string _ImageName, void* _Desc);
	void AddEffect(string _ImageName, float _LifeTime, int _MaxLoopCnt = 1, bool _IsTraceTarget = false, GameObject* TraceTarget = nullptr);

	list<Effect*> Effects;
	wchar_t szText[128];

};