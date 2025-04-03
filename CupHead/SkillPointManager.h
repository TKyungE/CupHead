#pragma once
#include "GameObject.h"
class TrumpCard;

class SkillPointManager : public GameObject
{
public:
	SkillPointManager();
	virtual ~SkillPointManager();

	void Init(int InBulletCount, int InCardCount);
	virtual void Release() override;
	virtual void Update() override;

public:
	inline void SetActiveCount(int _Cnt) 
	{ 
		CurActiveCnt = _Cnt;
		CurActiveCnt = min(CurActiveCnt, MaxCardCnt);
	};

	inline int GetActiveCount() const { return CurActiveCnt; };

	inline void SetSkillPoint(float _Point)
	{
		SkillPoint = _Point;
		SkillPoint = min(SkillPoint, MaxSkillPoint);
	};

	inline int GetSkillPoint() const { return SkillPoint; };

private:
	vector<TrumpCard*> TrumpCards;
	int PreActiveCnt;
	int MaxCardCnt;
	int CurActiveCnt;

	int GageCount;
	int SkillPoint;
	int MaxSkillPoint;

};

