#include "Collider.h"
#include "GameObject.h"

Collider::Collider(GameObject* owner, COLLIDERTYPE colliderType, FPOINT pivot, FPOINT size)
	:Owner(owner),ColliderType(colliderType), Pos(), PivotPos(pivot), Size(size),bHit(false)
{
}

void Collider::Init()
{
}

void Collider::Update()
{
	if (Owner)
	{
		Pos.x = Owner->GetPos().x + PivotPos.x;
		Pos.y = Owner->GetPos().y + PivotPos.y;
	}
}

void Collider::Render(HDC hdc)
{
	FPOINT HalfSize = { Size.x / 2.f, Size.y / 2.f };

	HPEN hPen;

	if (!bHit)
	{
		hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0)); // RGB(0, 255, 0) -> �ʷϻ�
	}
	else
	{
		hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // RGB(0, 255, 0) -> �ʷϻ�
	}
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen); // ���� DC�� ���� ����

	switch (ColliderType)
	{
	case COLLIDERTYPE::Sphere:
		Ellipse(hdc, (int)(Pos.x - HalfSize.x), (int)(Pos.y - HalfSize.y), (int)(Pos.x + HalfSize.x), (int)(Pos.y + HalfSize.y));
		break;
	case COLLIDERTYPE::Rect:
		DrawRectLine(hdc, HalfSize);
		break;
	}
	// ����� ���� ������� ����
	SelectObject(hdc, hOldPen);

	// �� �޸� ����
	DeleteObject(hPen);
}

void Collider::Release()
{
}

void Collider::DrawRectLine(HDC hdc, FPOINT HalfSize)
{
	MoveToEx(hdc, Pos.x - HalfSize.x, Pos.y - HalfSize.y, NULL);
	LineTo(hdc, Pos.x + HalfSize.x, Pos.y - HalfSize.y);
	LineTo(hdc, Pos.x + HalfSize.x, Pos.y + HalfSize.y);
	LineTo(hdc, Pos.x - HalfSize.x, Pos.y + HalfSize.y);
	LineTo(hdc, Pos.x - HalfSize.x, Pos.y - HalfSize.y);
}
