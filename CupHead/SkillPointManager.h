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
		CurActiveCnt = max(CurActiveCnt, MaxCardCnt);
	};

	inline int GetActiveCount() const { return CurActiveCnt; };


private:
	vector<TrumpCard*> TrumpCards;
	int PreActiveCnt;
	int MaxCardCnt;
	int CurActiveCnt;


	float SkillPoint;
	float MaxSkillPoint;

};

