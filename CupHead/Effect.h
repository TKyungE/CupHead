#pragma once
#include "Actor.h"

class Image;
struct EffectInfo
{
	float CurLifeTime;
	float MaxLifeTime;
	int LoopCnt;
	int MaxLoopCnt;
	bool IsTraceTarget;
	GameObject* TraceTarget;
}typedef EffectDesc;

class Effect : public Actor
{
public:
	Effect();
	Effect(float _MaxLifeTime, int _MaxLoopCnt = 1, bool _IsTraceTarget = false, GameObject* TraceTarget = nullptr);
	Effect(EffectInfo _Desc);

	void Init();
	void Update();
	void PosUpdate();
	void Release();

	inline EffectDesc& GetDesc() { return m_EffectDesc; }
	inline void SetDesc(EffectDesc _Desc){ m_EffectDesc = _Desc; }
	virtual ~Effect();

private:
	EffectDesc m_EffectDesc;
};

