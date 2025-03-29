#pragma once
#include "Actor.h"

class Image;
struct EffectInfo
{
	float CurLifeTime;
	FPOINT OffsetPos;
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
	Effect(float _MaxLifeTime, FPOINT _Pos, FPOINT _Offset = { 0.f, 0.f }, int _MaxLoopCnt = 1, bool _IsTraceTarget = false, GameObject* TraceTarget = nullptr);
	Effect(FPOINT _Pos, EffectInfo _Desc);

	virtual void UpdateFrame() override;


	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void UpdateTime();
	void PosUpdate();

	inline EffectDesc& GetDesc() { return m_EffectDesc; }
	inline void SetDesc(EffectDesc _Desc){ m_EffectDesc = _Desc; }
	virtual ~Effect();

private:
	EffectDesc m_EffectDesc;
};

