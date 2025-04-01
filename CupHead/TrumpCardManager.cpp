#include "TrumpCardManager.h"
#include "TrumpCard.h"
#include "Player.h"
#include "ObjectManager.h"
#include <list>

TrumpCardManager::TrumpCardManager()
	: Owner(nullptr), MaxCount(0), CurrentCount(0)
{
}

void TrumpCardManager::Init(int InBulletCount, int InCardCount)
{
	BulletCount = InBulletCount;
	MaxCount = BulletCount * InCardCount;		// 앞에 5는 개당 카운트 / 뒤에 5는 카드 개수
	for (int i = 0; i < InCardCount; ++i)
	{
		// 20과 30은 은 트럼프 이미지의 카드 하나 사이즈다.
		TrumpCard* trumpCard = new TrumpCard();
		trumpCard->Init({ float(80 + 20 * (i + 1)),(float)WINSIZE_Y }, MaxCount / InCardCount);

		ObjectManager::GetInstance()->AddObject(trumpCard, OBJTYPE::OBJ_UI);
		TrumpCards.push_back(trumpCard);
	}
}

void TrumpCardManager::Update()
{
	if (Owner == nullptr)
	{
		list<GameObject*> playerList = ObjectManager::GetInstance()->GetObjectList(OBJ_PLAYER);
		if (!playerList.empty())
			Owner = dynamic_cast<Player*>(playerList.front());
	}

	if (KeyManager::GetInstance()->IsOnceKeyDown('U'))
	{
		++CurrentCount;
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('I'))
	{
		CurrentCount = 0;
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('O'))
	{
		CurrentCount -= BulletCount;
	}

	if (CurrentCount > MaxCount)
		CurrentCount = MaxCount;

	int CardsCurrentCount = CurrentCount;
	for (int i = 0; i < TrumpCards.size(); ++i)
	{
		// 이코드는 쓰레기다.
		if (CardsCurrentCount > 0)
		{
			if (CardsCurrentCount >= BulletCount)
			{
				TrumpCards[i]->SetCurrentCount(BulletCount);
				CardsCurrentCount -= BulletCount;
			}
			else
			{
				TrumpCards[i]->SetCurrentCount(CardsCurrentCount);
				CardsCurrentCount = 0;
			}
		}
		else
			TrumpCards[i]->SetCurrentCount(0);

		if (CurrentCount == MaxCount && !TrumpCards[i]->IsTurn())
			TrumpCards[i]->SetbTurn(true);

		// 이런방식으로 하고 싶은데.. 
		///*CardsCurrentCount = (CardsCurrentCount - 1) - 5;
		///*if (CardsCurrentCount)
		//{
		//	int a = CardsCurrentCount % 5 == 0 ? 5 : CardsCurrentCount % 5;
		//	TrumpCards[i]->SetCurrentCount(CardsCurrentCount % 5 == 0 ? 5 : CardsCurrentCount % 5);*/
		//}
	}
}

void TrumpCardManager::Release()
{
}
TrumpCardManager::~TrumpCardManager()
{
}