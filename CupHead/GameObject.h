#pragma once
#include "config.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init();											// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();									// �޸� ����
	virtual void Update();									// ������ ������ ���� ���� ����(������ ���)
	virtual void Render(HDC hdc);							// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	virtual void TakeDamage(int damage = 0) {};			// �浹�ϸ� ������ ���� �� Ŭ�������� �����ϼ���

	FPOINT GetPos() const { return pos; }
	bool IsDead() const { return bDead; }

	void SetDead(bool bDead) { this->bDead = bDead; }
protected:
	FPOINT pos;
	FPOINT size;
	bool bDead;
};

