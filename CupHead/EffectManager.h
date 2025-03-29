#pragma once
#include "Singleton.h"
#include "config.h"
#include <list>
#include <map>

class Effect;

enum EFFECTTYPE
{
	EFFECT_NORMAL, EFFECT_LOOP, EFFECT_TRACE, EFFECT_END
};

class EffectManager : public Singleton<EffectManager>
{
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void AddEffect(string _ImageName, FPOINT _Pos, void* _Desc);
	void AddEffect(string _ImageName, FPOINT _Pos, float _MaxLifeTime, FPOINT _Offset = { 0.f, 0.f }, int _MaxLoopCnt = 1, bool _IsTraceTarget = false, GameObject* TraceTarget = nullptr);
	list<Effect*> Effects;
	//map<GameObject*, list<Effect*>> Test;

};