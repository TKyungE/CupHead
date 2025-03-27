#pragma once
#include "config.h"

enum class COLLIDERTYPE
{
	Sphere,
	Rect,
	End
};

class GameObject;
class Collider
{
public:
	Collider(GameObject* owner, COLLIDERTYPE colliderType, FPOINT pivot, FPOINT size);
	~Collider() = default;

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	GameObject* GetOwner() const { return Owner; }
	FPOINT GetPos() const { return Pos; }
	FPOINT GetSize() const { return Size; }
	void SetHit(bool bhit) { this->bHit = bhit; }

private:
	void DrawRectLine(HDC hdc, FPOINT HalfSize);
private:
	GameObject* Owner;
	COLLIDERTYPE ColliderType;

	FPOINT Pos;
	FPOINT PivotPos;
	FPOINT Size;

	bool bHit;
};

