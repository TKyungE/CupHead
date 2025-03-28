#pragma once
#include "Singleton.h"
#include "config.h"
#include <list>


class Collider;
class GameObject;

struct FHitResult
{
	GameObject* HitObj;
};

struct Line
{
	Line(FPOINT st, FPOINT ed)
		: start(st), end(ed), bDebugDraw(false), CurrentTime(0.f), DebugDuration(0.f), DebugColor(RGB(0, 255, 0))
	{

	}

	void Render(HDC hdc)
	{
		MoveToEx(hdc, (int)start.x, (int)start.y, NULL);
		LineTo(hdc, (int)end.x, (int)end.y);
	}
	void Update()
	{
		CurrentTime += TimerManager::GetInstance()->GetDeltaTime();
		if (CurrentTime >= DebugDuration)
		{
			CurrentTime = 0.f;
			bDebugDraw = false;
		}
	}
	FPOINT start;
	FPOINT end;

	float CurrentTime;
	float DebugDuration;
	bool bDebugDraw;
	COLORREF DebugColor;
};

class CollisionManager : public Singleton<CollisionManager>
{
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void DebugLineRender(HDC hdc);
	void Release();

	void AddCollider(Collider* collider, OBJTYPE objType) { CollisionList[objType].push_back(collider); }

	void PlayerMonsterCollision();
	void PlayerMonsterWeaponCollision();
	void PlayerWeaponMonsterCollision();

	bool CollisionAABB(Collider* collider1, Collider* collider2);
	bool CollisionSphere(Collider* collider1, Collider* collider2);





	bool LineTraceByObject(FHitResult& hitResult, OBJTYPE objType, FPOINT start, FPOINT end, GameObject* owner, bool bIgnoreSelf, bool bDebugDraw, float DebugDuration, COLORREF DebugColor);
	bool CheckLineTrace(FPOINT p1, FPOINT p2, FPOINT p3, FPOINT p4);
	int ccw(FPOINT p1, FPOINT p2, FPOINT p3);
private:
	list<Collider*> CollisionList[OBJ_END];
	list<Line*> LineList;
};
 
