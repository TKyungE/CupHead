#pragma once
#include "GameObject.h"
#include <vector>

class TrumpCard;
class Player;
class TrumpCardManager : public GameObject
{
public:
	TrumpCardManager();
	virtual ~TrumpCardManager();

	void Init(int InBulletCount,int InCardCount);
	virtual void Release() override;
	virtual void Update() override;
private:
	Player* Owner;
	vector<TrumpCard*> TrumpCards;

	int BulletCount;
	int MaxCount;
	int CurrentCount;
};

