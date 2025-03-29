#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"
#include "CommonFunction.h"
#include <cmath>

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{
	for (int objType= 0; objType < OBJ_END; ++objType)
	{
		for (auto iter = CollisionList[objType].begin(); iter != CollisionList[objType].end();)
		{
			if ((*iter)->GetOwner() == nullptr || (*iter)->GetOwner()->IsDead())
			{
				(*iter)->Release();
				delete (*iter);
				(*iter) = nullptr;
				iter = CollisionList[objType].erase(iter);
			}
			else
			{
				(*iter)->Update();
				++iter;
			}
		}
	}	

	for (auto iter = LineList.begin(); iter != LineList.end();)
	{
		(*iter)->Update();
		if (!(*iter)->bDebugDraw)
		{
			delete (*iter);
			(*iter) = nullptr;
			iter = LineList.erase(iter);
		}
		else
			++iter;
	}

	// 콜라이더 업데이트 후 충돌 검사
	// 기본적으로 네모와 원 충돌은 그냥 원 충돌로 퉁침.
	PlayerMonsterCollision();
	PlayerMonsterWeaponCollision();
	PlayerWeaponMonsterCollision();
}

void CollisionManager::Render(HDC hdc)
{
	for (int objType = 0; objType < OBJ_END; ++objType)
	{
		for (auto& iter : CollisionList[objType])
		{
			if (!iter->CanDebugDraw())
				continue;

			iter->Render(hdc);
		}
	}

	DebugLineRender(hdc);
}

void CollisionManager::DebugLineRender(HDC hdc)
{
	for (auto& iter : LineList)
	{
		if (iter->bDebugDraw)
		{
			HPEN hPen = CreatePen(PS_SOLID, 4, iter->DebugColor);
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen); // 현재 DC에 펜을 설정

			iter->Render(hdc);

			// 사용한 펜을 원래대로 복원
			SelectObject(hdc, hOldPen);

			// 펜 메모리 해제
			DeleteObject(hPen);
		}
	}
}

void CollisionManager::Release()
{
	for (int objType = 0; objType < OBJ_END; ++objType)
	{
		for (auto& iter : CollisionList[objType])
		{
			iter->Release();
			delete iter;
			iter = nullptr;
		}
		CollisionList[objType].clear();
	}

	for (auto& iter : LineList)
		delete iter;
	
	LineList.clear();

	ReleaseInstance();
}

void CollisionManager::PlayerMonsterCollision()
{
	for (auto& player : CollisionList[OBJ_PLAYER])
	{
		for (auto& monster : CollisionList[OBJ_MONSTER])
		{
			if (!player->CanHit() || !monster->CanHit())
				continue;

			const COLLIDERTYPE colliderType = player->GetColliderType() == monster->GetColliderType() ? player->GetColliderType() : COLLIDERTYPE::Sphere;

			bool bCollision = false;
			switch (colliderType)
			{
			case COLLIDERTYPE::Sphere:
				bCollision = CollisionSphere(player, monster);
				break;
			case COLLIDERTYPE::Rect:
				bCollision = CollisionAABB(player, monster);
				break;
			default:
				break;
			}

			if (bCollision)
			{
				player->GetOwner()->TakeDamage(1.f);
				monster->GetOwner()->TakeDamage(1.f);
				player->SetHit(true);
				monster->SetHit(true);
			}
		}
	}
}

void CollisionManager::PlayerMonsterWeaponCollision()
{
	for (auto& player : CollisionList[OBJ_PLAYER])
	{
		for (auto& monsterWeapon : CollisionList[OBJ_MONSTER_WEAPON])
		{
			if (!player->CanHit() || !monsterWeapon->CanHit())
				continue;

			const COLLIDERTYPE colliderType = player->GetColliderType() == monsterWeapon->GetColliderType() ? player->GetColliderType() : COLLIDERTYPE::Sphere;

			bool bCollision = false;
			switch (colliderType)
			{
			case COLLIDERTYPE::Sphere:
				bCollision = CollisionSphere(player, monsterWeapon);
				break;
			case COLLIDERTYPE::Rect:
				bCollision = CollisionAABB(player, monsterWeapon);
				break;
			default:
				break;
			}

			if (bCollision)
			{
				player->GetOwner()->TakeDamage(1.f);
				monsterWeapon->GetOwner()->TakeDamage(1.f);

				player->SetHit(true);
				monsterWeapon->SetHit(true);
			}
		}
	}
}

void CollisionManager::PlayerWeaponMonsterCollision()
{
	for (auto& monster : CollisionList[OBJ_MONSTER])
	{
		for (auto& playerWeapon : CollisionList[OBJ_PLAYER_WEAPON])
		{
			if (!monster->CanHit() || !playerWeapon->CanHit())
				continue;

			const COLLIDERTYPE colliderType = monster->GetColliderType() == playerWeapon->GetColliderType() ? monster->GetColliderType() : COLLIDERTYPE::Sphere;

			bool bCollision = false;
			switch (colliderType)
			{
			case COLLIDERTYPE::Sphere:
				bCollision = CollisionSphere(monster, playerWeapon);
				break;
			case COLLIDERTYPE::Rect:
				bCollision = CollisionAABB(monster, playerWeapon);
				break;
			default:
				break;
			}

			if (bCollision)
			{
				playerWeapon->GetOwner()->TakeDamage(1.f);
				monster->GetOwner()->TakeDamage(1.f);
				playerWeapon->SetHit(true);
				monster->SetHit(true);
			}
		}
	}	
}

bool CollisionManager::CollisionAABB(Collider* collider1, Collider* collider2)
{
	FPOINT collider1Pos = collider1->GetPos();
	FPOINT Collider1HalfSize = { collider1->GetSize().x * 0.5f,collider1->GetSize().y * 0.5f };

	FPOINT collider2Pos = collider2->GetPos();
	FPOINT Collider2HalfSize = { collider2->GetSize().x * 0.5f,collider2->GetSize().y * 0.5f };

	RECT rc1;
	rc1.left = LONG(collider1Pos.x - Collider1HalfSize.x);
	rc1.right = LONG(collider1Pos.x + Collider1HalfSize.x);
	rc1.top = LONG(collider1Pos.y - Collider1HalfSize.y);
	rc1.bottom = LONG(collider1Pos.y + Collider1HalfSize.y);

	RECT rc2;
	rc2.left = LONG(collider2Pos.x - Collider2HalfSize.x);
	rc2.right = LONG(collider2Pos.x + Collider2HalfSize.x);
	rc2.top = LONG(collider2Pos.y - Collider2HalfSize.y);
	rc2.bottom = LONG(collider2Pos.y + Collider2HalfSize.y);
	
	return RectInRect(rc1,rc2);
}

bool CollisionManager::CollisionSphere(Collider* collider1, Collider* collider2)
{
	// 원은 사이즈가 x,y가 같다. 타원 불가
	float radius = (collider1->GetSize().x + collider2->GetSize().x) * 0.5f;
	float distance = GetDistance(collider1->GetPos(), collider2->GetPos());

	return distance <= radius;
}

bool CollisionManager::LineTraceByObject(FHitResult& hitResult, OBJTYPE objType, FPOINT start, FPOINT end, GameObject* owner, bool bIgnoreSelf, bool bDebugDraw, float DebugDuration, COLORREF DebugColor)
{
	// 네 변을 다 검사해야 한다
	// ccw 알고리즘 사용
	if (bDebugDraw)
	{
		Line* line = new Line(start, end);
		line->bDebugDraw = bDebugDraw;
		line->DebugDuration = DebugDuration;
		line->DebugColor = DebugColor;
		LineList.push_back(line);
	}

	for (auto& iter : CollisionList[objType])
	{
		const FPOINT collPos = iter->GetPos();
		const FPOINT collSize = iter->GetSize();
		const FPOINT collHalfSize = { collSize.x * 0.5f, collSize.y * 0.5f };

		// 0 1 Rect 기준
		// 3 2
		const FPOINT CollRect[4] = {		 
			{collPos.x - collHalfSize.x,collPos.y - collHalfSize.y}, {collPos.x + collHalfSize.x,collPos.y - collHalfSize.y},
			{collPos.x + collHalfSize.x, collPos.y + collHalfSize.y}, {collPos.x - collHalfSize.x,collPos.y + collHalfSize.y}
		};
		
		bool bCollision = false;
		for (int i = 0; i < 4; ++i)
		{
			const FPOINT collEnd = i == 3 ? CollRect[0] : CollRect[i + 1];
			if (CheckLineTrace(CollRect[i], collEnd, start, end))
			{
				// 충돌
				bCollision = true;
				break;
			}
		}

		if (bCollision)
		{
			iter->SetHit(true);

			hitResult.HitObj = iter->GetOwner();
			return true;
		}
		else
			iter->SetHit(false);
	}

	return false;
}

bool CollisionManager::CheckLineTrace(FPOINT p1, FPOINT p2, FPOINT p3, FPOINT p4)
{
	int ccw1 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
	int ccw2 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

	// 두 선이 일단 평행함 두 선의 min,max 비교 
	if (ccw1 == 0 && ccw2 == 0)
	{
		// p1 , p2    // p3, p4는 각 선분이다.
		// ---------------              ------------- 
		FPOINT minAB = { min(p1.x,p2.x),min(p1.y,p2.y) };
		FPOINT maxAB = { max(p1.x,p2.x),max(p1.y,p2.y) };
		FPOINT minCD = { min(p3.x,p4.x),min(p3.y,p4.y) };
		FPOINT maxCD = { max(p3.x,p4.x),max(p3.y,p4.y) };

		return (minAB.x <= maxCD.x && minAB.y <= maxCD.y && minCD.x <= maxAB.x && minCD.y <= maxAB.y);
	}

	return (ccw1 <= 0 && ccw2 <= 0);
}

int CollisionManager::ccw(FPOINT p1, FPOINT p2, FPOINT p3)
{
	const float result = (p1.x * p2.y + p2.x * p3.y + p3.x * p1.y) - (p1.y * p2.x + p2.y * p3.x + p3.y * p1.x);

	if (result > 0.f) return 1;
	if (result < 0.f) return -1;
	return 0;
}
