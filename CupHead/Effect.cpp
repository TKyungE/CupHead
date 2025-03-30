#include "Effect.h"
#include "Image.h"

Effect::Effect()
{
	memset(&m_EffectDesc, 0, sizeof(m_EffectDesc));
	m_EffectDesc.MaxLoopCnt = 1;
}

Effect::Effect(float _MaxLifeTime, FPOINT _Pos, FPOINT _Offset, int _MaxLoopCnt, bool _IsTraceTarget, GameObject* TraceTarget)
{
	m_EffectDesc.MaxLifeTime = _MaxLifeTime;
	m_EffectDesc.OffsetPos = _Offset;
	m_EffectDesc.MaxLoopCnt = _MaxLoopCnt;
	m_EffectDesc.IsTraceTarget = _IsTraceTarget;
	m_EffectDesc.TraceTarget = TraceTarget;
	m_EffectDesc.CurLifeTime = 0;
	m_EffectDesc.LoopCnt = 0;

	pos.x = _Pos.x + m_EffectDesc.OffsetPos.x;
	pos.y = _Pos.y + m_EffectDesc.OffsetPos.y;
}

Effect::Effect(FPOINT _Pos, EffectInfo _Desc) : m_EffectDesc(_Desc)
{
	pos.x = _Pos.x + m_EffectDesc.OffsetPos.x;
	pos.y = _Pos.y + m_EffectDesc.OffsetPos.y;

}

void Effect::Init()
{
	FrameSpeed = m_EffectDesc.MaxLoopCnt / m_EffectDesc.MaxLifeTime * image->GetMaxFrameX();
}

void Effect::Update()
{
	UpdateTime();
	UpdateFrame();
	PosUpdate();
}

void Effect::Render(HDC hdc)
{
	image->FrameRender(hdc,pos.x,pos.y, CurFrameIndex, 0);
}

void Effect::UpdateTime()
{
	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();
	m_EffectDesc.CurLifeTime += DeltaTime;

	if (m_EffectDesc.MaxLifeTime <= m_EffectDesc.CurLifeTime)
	{
		bDead = true;
	}
}

void Effect::UpdateFrame()
{
	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();
	FrameTime += FrameSpeed * DeltaTime;
	CurFrameIndex = (int)FrameTime;

	if (CurFrameIndex >= image->GetMaxFrameX())
	{
		CurFrameIndex = FrameTime = 0.f;
		++m_EffectDesc.LoopCnt;
		if (m_EffectDesc.MaxLoopCnt <= m_EffectDesc.LoopCnt)
		{
			bDead = true;
		}
	}
}

void Effect::PosUpdate()
{
	if (true == m_EffectDesc.IsTraceTarget && nullptr != m_EffectDesc.TraceTarget)
	{
		pos.x = m_EffectDesc.TraceTarget->GetPos().x + m_EffectDesc.OffsetPos.x;
		pos.y = m_EffectDesc.TraceTarget->GetPos().y + m_EffectDesc.OffsetPos.y;
	}
}

void Effect::Release()
{

}

Effect::~Effect()
{

}