#include "CollisionManager.h"
#include "Collider.h"
#include <cmath>

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{
	for (int objType= 0; objType < OBJ_END; ++objType)
	{
		for (auto& iter : CollisionList[objType])
		{
			iter->Update();
		}
	}	
}

void CollisionManager::Render(HDC hdc)
{
	for (int objType = 0; objType < OBJ_END; ++objType)
	{
		for (auto& iter : CollisionList[objType])
		{
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
			HPEN hPen = CreatePen(PS_SOLID, 4, iter->DebugColor); // RGB(0, 255, 0) -> �ʷϻ�
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen); // ���� DC�� ���� ����

			iter->Render(hdc);

			// ����� ���� ������� ����
			SelectObject(hdc, hOldPen);

			// �� �޸� ����
			DeleteObject(hPen);
		}
	}
}

void CollisionManager::Release()
{
	for (int objType = 0; objType < OBJ_END; ++objType)
	{
		for (auto iter = CollisionList[objType].begin(); iter != CollisionList[objType].end();)
		{
			(*iter)->Release();
			delete (*iter);
			iter = CollisionList[objType].erase(iter);
		}

		CollisionList[objType].clear();
	}

	for (auto iter = LineList.begin(); iter != LineList.end();)
	{
		delete (*iter);
		iter = LineList.erase(iter);
	}	

	ReleaseInstance();
}

bool CollisionManager::LineTraceByObject(FHitResult& hitResult, OBJTYPE objType, FPOINT start, FPOINT end, GameObject* owner, bool bIgnoreSelf, bool bDebugDraw, float DebugDuration, COLORREF DebugColor)
{
	// �� ���� �� �˻��ؾ� �Ѵ�
	// ccw �˰��� ���

	Line* line = new Line(start, end);
	line->bDebugDraw = bDebugDraw;
	line->DebugDuration = DebugDuration;
	line->DebugColor = DebugColor;
	LineList.push_back(line);

	for (auto& iter : CollisionList[objType])
	{
		const FPOINT collPos = iter->GetPos();
		const FPOINT collSize = iter->GetSize();
		const FPOINT collHalfSize = { collSize.x * 0.5f, collSize.y * 0.5f };

		// 0 1 Rect ����
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
				// �浹
				bCollision = true;
				break;
			}
		}

		if (bCollision)
		{
			hitResult.HitObj = iter->GetOwner();
			return true;
		}	
	}

	return false;
}

bool CollisionManager::CheckLineTrace(FPOINT p1, FPOINT p2, FPOINT p3, FPOINT p4)
{
	int ccw1 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
	int ccw2 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

	// �� ���� �ϴ� ������ �� ���� min,max �� 
	if (ccw1 == 0 && ccw2 == 0)
	{
		// p1 , p2    // p3, p4�� �� �����̴�.
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
