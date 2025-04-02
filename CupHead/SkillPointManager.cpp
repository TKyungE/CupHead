#include "SkillPointManager.h"
#include "TrumpCard.h"
#include "ObjectManager.h"

SkillPointManager::SkillPointManager(): PreActiveCnt(0), CurActiveCnt(0), MaxCardCnt(5), SkillPoint(0.f), MaxSkillPoint(0.f)
{
}

void SkillPointManager::Init(int InBulletCount, int InCardCount)
{
	TrumpCards.resize(MaxCardCnt);

	for (int i = 0; i < MaxCardCnt; ++i)
	{
		// 20과 30은 은 트럼프 이미지의 카드 하나 사이즈다.
		TrumpCard* trumpCard = new TrumpCard();
		trumpCard->Init({ float((80 + 20 * 2) + 20 * (i + 1)),(float)WINSIZE_Y }, MaxCardCnt / 50);
		ObjectManager::GetInstance()->AddObject(trumpCard, OBJTYPE::OBJ_UI);
		TrumpCards[i] = trumpCard;
	}
}

void SkillPointManager::Update()
{
	//if (KeyManager::GetInstance()->IsStayKeyDown('U'))
	//{
	//	++CurrentCount;
	//}

	//if (KeyManager::GetInstance()->IsOnceKeyDown('I'))
	//{
	//	CurrentCount = 0;
	//}

	//if (KeyManager::GetInstance()->IsOnceKeyDown('O'))
	//{
	//	CurrentCount -= BulletCount;
	//}

	//if (CurActiveCnt > MaxCardCnt)
	//{
	//	CurActiveCount = MaxCardCount;
	//}

	//for (int i = 0; i < CurActiveCount; ++i)
	//{
	//	if (CardsCurrentCount > 0)
	//	{
	//		if (CardsCurrentCount >= BulletCount)
	//		{
	//			TrumpCards[i]->SetCurrentCount(BulletCount);
	//			CardsCurrentCount -= BulletCount;
	//		}
	//		else
	//		{
	//			TrumpCards[i]->SetCurrentCount(CardsCurrentCount);
	//			CardsCurrentCount = 0;
	//		}

	//		if (CurrentCount != MaxCount)
	//			TrumpCards[i]->SetbTurn(false);
	//	}
	//	else
	//		TrumpCards[i]->SetCurrentCount(0);

	//	if (CurrentCount == MaxCount && !TrumpCards[i]->IsTurn())
	//	{
	//		TrumpCards[i]->SetbTurn(true);
	//		continue;
	//	}

		// 이런방식으로 하고 싶은데.. 
		///*CardsCurrentCount = (CardsCurrentCount - 1) - 5;
		///*if (CardsCurrentCount)
		//{
		//	int a = CardsCurrentCount % 5 == 0 ? 5 : CardsCurrentCount % 5;
		//	TrumpCards[i]->SetCurrentCount(CardsCurrentCount % 5 == 0 ? 5 : CardsCurrentCount % 5);*/
		//}
	//}
}

void SkillPointManager::Release()
{

}

SkillPointManager::~SkillPointManager()
{

}





