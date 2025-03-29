#include "Effect.h"

Effect::Effect()
{
	memset(&m_EffectDesc, 0, sizeof(m_EffectDesc));
	m_EffectDesc.MaxLoopCnt = 1;
}

Effect::Effect(float _MaxLifeTime, int _MaxLoopCnt, bool _IsTraceTarget, GameObject* TraceTarget)
{
	m_EffectDesc.MaxLifeTime = _MaxLifeTime;
	m_EffectDesc.MaxLoopCnt = _MaxLoopCnt;
	m_EffectDesc.IsTraceTarget = _IsTraceTarget;
	m_EffectDesc.TraceTarget = TraceTarget;
	m_EffectDesc.CurLifeTime = 0;
	m_EffectDesc.LoopCnt = 0;
}

Effect::Effect(EffectInfo _Desc) : m_EffectDesc(_Desc)
{

}

void Effect::Init()
{

}

void Effect::Update()
{
	UpdateFrame();

	//if(m_EffectDesc.LifeTime)
}

void Effect::PosUpdate()
{

}

void Effect::Release()
{

}

Effect::~Effect()
{

}