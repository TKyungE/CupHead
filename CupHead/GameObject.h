#pragma once
#include "config.h"

class GameObject
{
public:
	void Init();		// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	void Release();		// �޸� ����
	void Update();		// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	FPOINT GetPos() const { return pos; }
	bool IsDead() const { return bDead; }

	GameObject();
	~GameObject();

protected:
	FPOINT pos;
	FPOINT size;
	bool bDead;
};

