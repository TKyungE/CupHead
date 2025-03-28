#pragma once
#include "config.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Init();											// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();									// �޸� ����
	virtual void Update();									// ������ ������ ���� ���� ����(������ ���)
	virtual void Render(HDC hdc);							// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	virtual void TakeDamage(float damage = 0.f) {};			// �浹�ϸ� ������ ���� �� Ŭ�������� �����ϼ���

	FPOINT GetPos() const { return pos; }
	bool IsDead() const { return bDead; }
protected:
	FPOINT pos;
	FPOINT size;
	bool bDead;
};

