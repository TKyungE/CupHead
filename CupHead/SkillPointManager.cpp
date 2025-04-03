#include "SkillPointManager.h"
#include "TrumpCard.h"
#include "ObjectManager.h"

SkillPointManager::SkillPointManager(): PreActiveCnt(0), CurActiveCnt(0), MaxCardCnt(5), SkillPoint(0), MaxSkillPoint(50), GageCount(0)
{
}

void SkillPointManager::Init(int InBulletCount, int InCardCount)
{
	GageCount = InBulletCount;
	MaxSkillPoint = GageCount * InCardCount;

	TrumpCards.resize(MaxCardCnt);

	for (int i = 0; i < MaxCardCnt; ++i)
	{
		// 20과 30은 은 트럼프 이미지의 카드 하나 사이즈다.
		TrumpCard* trumpCard = new TrumpCard();
		trumpCard->Init({ float((80 + 20 * 2) + 20 * (i + 1)),(float)WINSIZE_Y }, MaxSkillPoint / MaxCardCnt);
		/*trumpCard->SetCurrentCount(50);
		trumpCard->SetbTurn(true);*/
		ObjectManager::GetInstance()->AddObject(trumpCard, OBJTYPE::OBJ_UI);
		TrumpCards[i] = trumpCard;
	}
}

void SkillPointManager::Update()
{
	// 230
	int Temp = SkillPoint / GageCount; //4
	int Gap = SkillPoint % GageCount; // 30

	for (int i = 0; i < MaxCardCnt; ++i)
	{
		if (i < Temp)
		{
			if (!TrumpCards[i]->IsTurn())
			{
				TrumpCards[i]->SetCurrentCount(MaxSkillPoint / MaxCardCnt);
			}
		}
		
		else
		{
			TrumpCards[i]->SetCurrentCount(0);
		}

		if (MaxCardCnt != Temp)
		{
			TrumpCards[i]->SetbTurn(false);

		}

		if (MaxCardCnt == Temp)
		{
			if (!TrumpCards[i]->IsTurn())
			TrumpCards[i]->SetbTurn(true);
		}
	}

	if (0 < Gap)
	{
		TrumpCards[Temp]->SetCurrentCount(Gap);
	}
}

void SkillPointManager::Release()
{

}

SkillPointManager::~SkillPointManager()
{

}





