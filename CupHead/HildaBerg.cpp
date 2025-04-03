#include "HildaBerg.h"
#include "Character.h"
#include "HildaBlimp.h"
#include "Taurus.h"
#include "Sagittarius.h"
#include "Moon.h"
#include "BlimpEnemy.h"
#include "StarProjectile.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "EffectManager.h"
#include <numeric>
#include "LevelManager.h"

HildaBerg::HildaBerg()
	: HildaForm{}, Phase{}, Angle{},
	ElapsedSpawnTime{}, SpawnCoolTime{ 3.f }
{
	/*HpList[0] = 200;
	HpList[1] = 250;
	HpList[2] = 200;
	HpList[3] = 250;
	HpList[4] = 200;
	HpList[5] = 300;*/
	HpList[0] = 20;
	HpList[1] = 25;
	HpList[2] = 20;
	HpList[3] = 25;
	HpList[4] = 20;
	HpList[5] = 30;

	ZeroMemory(&HlidaBergData, sizeof(FHildaBergData));	
}

HildaBerg::~HildaBerg()
{
}

void HildaBerg::Init()
{
#pragma region Effect Image Load
	ImageManager::GetInstance()->AddImage(
		"BigCloudFx",
		TEXT("Image\\CupHead\\Hilda Berg\\Normal\\Fx\\big_cloud_fx.bmp"),
		10545, 679,
		19, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"SmallCloudFx",
		TEXT("Image\\CupHead\\Hilda Berg\\Normal\\Fx\\small_cloud_fx.bmp"),
		4147, 308,
		13, 1,
		true, RGB(255, 0, 255));
#pragma endregion

	pos = { WINSIZE_X - 300.f, WINSIZE_Y / 2.f + 50.f };
	Phase = 0;
	ChangeForm();


	HlidaBergData.TotalHp = GetTotalHp();
	memcpy(HlidaBergData.HpList, HpList, sizeof(int) * 6);
}

void HildaBerg::Release()
{
	if (HildaForm)
	{
		HildaForm->Release();
		delete HildaForm;
		HildaForm = NULL;
	}
}

void HildaBerg::Update()
{
	ProcessInput();

	if (Phase < 0) return;

	if (HildaForm)
	{
		HildaForm->Update();

		if (HildaForm->IsDead())
		{
			pos = HildaForm->GetPos();
			Angle = HildaForm->GetMoveAngle();

			CollisionManager::GetInstance()->Update();

			HildaForm->Release();
			delete HildaForm;
			HildaForm = NULL;
			ElapsedSpawnTime = 0.f;

			if (Phase < 4)
			{
				EffectManager::GetInstance()->AddEffect("BigCloudFx", pos, 1.f);

				for (int i = 0; i < 4; ++i)
				{
					uniform_int_distribution<int> randX{ int(pos.x - 350.f * 0.5f), int(pos.x + 350.f * 0.5f) };
					uniform_int_distribution<int> randY{ int(pos.y - 400.f * 0.5f), int(pos.y + 400.f * 0.5f) };

					EffectManager::GetInstance()->AddEffect("SmallCloudFx", { (float)randX(dre), (float)randY(dre) }, 1.f);
				}
			}
		}
	}

	if (!HildaForm)
	{
		Phase++;
		ChangeForm();
	}
	ElapsedSpawnTime += TimerManager::GetInstance()->GetDeltaTime();
	if (ElapsedSpawnTime >= SpawnCoolTime)
	{
		SpawnEnemy();
		ElapsedSpawnTime = 0.f;
	}

	HlidaBergData.Phase = Phase;
	HlidaBergData.CurrentHp = GetCurrentHp();

	LevelManager::GetInstance()->SetData(&HlidaBergData);
}

void HildaBerg::Render(HDC hdc)
{
	if (HildaForm) HildaForm->Render(hdc);
}

int HildaBerg::GetTotalHp() const
{
	return accumulate(HpList, HpList + 6, 0);
}

int HildaBerg::GetCurrentHp() const
{
	return HildaForm ? accumulate(HpList + Phase + 1, HpList + 6, 0) + HildaForm->GetHp() : 0;
}

void HildaBerg::ChangePhaseByInput(int _Phase)
{
	Phase = _Phase;

	if (HildaForm)
	{
		HildaForm->SetDead(true);
		pos = HildaForm->GetPos();
		Angle = HildaForm->GetMoveAngle();
		HildaForm->Update();

		CollisionManager::GetInstance()->Update();

		HildaForm->Release();
		delete HildaForm;
		HildaForm = NULL;
		ElapsedSpawnTime = 0.f;
	}

	EffectManager::GetInstance()->AddEffect("BigCloudFx", pos, 1.f);

	for (int i = 0; i < 4; ++i)
	{
		uniform_int_distribution<int> randX{ int(pos.x - 350.f * 0.5f), int(pos.x + 350.f * 0.5f) };
		uniform_int_distribution<int> randY{ int(pos.y - 400.f * 0.5f), int(pos.y + 400.f * 0.5f) };

		EffectManager::GetInstance()->AddEffect("SmallCloudFx", { (float)randX(dre), (float)randY(dre) }, 1.f);
	}

	ChangeForm();
}

void HildaBerg::ChangeForm()
{
	switch (Phase)
	{
	case 0:
	{
		HildaBlimp* blimp = new HildaBlimp(0);
		blimp->Init(pos, Angle, HpList[Phase]);
		HildaForm = blimp;
		SpawnCoolTime = 6.f;
		break;
	}
	case 1:
	{
		Taurus* taurus = new Taurus();
		taurus->Init(pos, Angle, HpList[Phase]);
		HildaForm = taurus;
		SpawnCoolTime = 5.f;
		break;
	}
	case 2:
	{
		HildaBlimp* blimp = new HildaBlimp(1);
		blimp->Init(pos, Angle, HpList[Phase]);
		HildaForm = blimp;
		SpawnCoolTime = 5.f;
		break;
	}
	case 3:
	{
		Sagittarius* sag = new Sagittarius();
		sag->Init(pos, Angle, HpList[Phase]);
		HildaForm = sag;
		SpawnCoolTime = 4.f;
		break;
	}
	case 4:
	{
		HildaBlimp* blimp = new HildaBlimp(2);
		blimp->Init(pos, Angle, HpList[Phase]);
		HildaForm = blimp;
		SpawnCoolTime = 4.f;
		break;
	}
	case 5:
	{
		Moon* moon = new Moon();
		moon->Init(HpList[Phase]);
		HildaForm = moon;
		SpawnCoolTime = 1.3f;
		break;
	}
	}
}

void HildaBerg::SpawnEnemy()
{
	std::uniform_int_distribution<int> uidY{ 100, WINSIZE_Y - 200 };
	std::uniform_int_distribution<int> uidY2{ 100, WINSIZE_Y - 50 };
	switch (Phase)
	{
	case 0:	case 1:
	{
		BlimpEnemy* blimpEnemy = new BlimpEnemy();
		blimpEnemy->Init(BlimpEnemyInfo::EColor::PURPLE, 1, { WINSIZE_X + 100.f, (float)uidY(dre) });
		ObjectManager::GetInstance()->AddObject(blimpEnemy, OBJ_MONSTER);
		break;
	}
	case 2:	// normal
	{
		bool PurpleEnemy = uid(dre) % 10;
		BlimpEnemyInfo::EColor color{};
		int bulletNum{};
		if (PurpleEnemy)
		{
			color = BlimpEnemyInfo::EColor::PURPLE;
			bulletNum = 1;
		}
		else
		{
			color = BlimpEnemyInfo::EColor::GREEN;
			bulletNum = 4;
		}
		BlimpEnemy* blimpEnemy = new BlimpEnemy();
		blimpEnemy->Init(color, bulletNum, { WINSIZE_X + 100.f, (float)uidY(dre) });
		ObjectManager::GetInstance()->AddObject(blimpEnemy, OBJ_MONSTER);
		break;
	}
	case 3:	case 4:
	{
		bool spawnOnce = uid(dre) % (10 - Phase * 2);
		int spawnNum = spawnOnce ? 1 : 2;
		for (int i = 0; i < spawnNum; ++i)
		{
			bool PurpleEnemy = uid(dre) % 10;
			BlimpEnemyInfo::EColor color{};
			int bulletNum{};
			if (PurpleEnemy)
			{
				color = BlimpEnemyInfo::EColor::PURPLE;
				bulletNum = 1;
			}
			else
			{
				color = BlimpEnemyInfo::EColor::GREEN;
				bulletNum = 4;
			}
			BlimpEnemy* blimpEnemy = new BlimpEnemy();
			blimpEnemy->Init(color, bulletNum, { WINSIZE_X + 100.f, (float)uidY(dre) });
			ObjectManager::GetInstance()->AddObject(blimpEnemy, OBJ_MONSTER);
		}
		break;
	}
	case 5:	// moon
	{
		// Moon Phase Star Spawn
		int type = uid(dre) % 3;
		StarProjectile* star = new StarProjectile(StarType(type));
		star->Init({ WINSIZE_X, (float)uidY2(dre) });
		ObjectManager::GetInstance()->AddObject(star, OBJ_MONSTER);
		break;
	}
	}
}

void HildaBerg::ProcessInput()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown('Z'))
	{
		ChangePhaseByInput(0);
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('X'))
	{
		ChangePhaseByInput(1);
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('C'))
	{
		ChangePhaseByInput(2);
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('V'))
	{
		ChangePhaseByInput(3);
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('B'))
	{
		ChangePhaseByInput(4);
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('N'))
	{
		ChangePhaseByInput(5);
	}
}
