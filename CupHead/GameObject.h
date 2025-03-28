#pragma once
#include "config.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Init();		// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	void Release();		// �޸� ����
	void Update();		// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	virtual void TakeDamage(float damage = 0.f) {};

	FPOINT GetPos() const { return pos; }
	bool IsDead() const { return bDead; }

	
protected:
	FPOINT pos;
	FPOINT size;
	bool bDead;
};

