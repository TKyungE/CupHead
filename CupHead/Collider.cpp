#include "Collider.h"
#include "GameObject.h"

Collider::Collider(GameObject* owner, COLLIDERTYPE colliderType, FPOINT pivot, FPOINT size, bool bDebugDraw)
	:Owner(owner),ColliderType(colliderType), PivotPos(pivot), Size(size), bDebugDraw(bDebugDraw), Pos(), bHit(false)
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
		hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0)); // �ʷ�
	else
		hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // ����

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
	MoveToEx(hdc, int(Pos.x - HalfSize.x), int(Pos.y - HalfSize.y), NULL);
	LineTo(hdc, int(Pos.x + HalfSize.x), int(Pos.y - HalfSize.y));
	LineTo(hdc, int(Pos.x + HalfSize.x), int(Pos.y + HalfSize.y));
	LineTo(hdc, int(Pos.x - HalfSize.x), int(Pos.y + HalfSize.y));
	LineTo(hdc, int(Pos.x - HalfSize.x), int(Pos.y - HalfSize.y));
}
