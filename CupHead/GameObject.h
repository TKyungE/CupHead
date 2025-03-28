#pragma once
#include "config.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Init();											// 멤버 변수의 초기화, 메모리 할당
	virtual void Release();									// 메모리 해제
	virtual void Update();									// 프레임 단위로 게임 로직 실행(데이터 계산)
	virtual void Render(HDC hdc);							// 프레임 단위로 출력(이미지, 텍스트 등)

	virtual void TakeDamage(float damage = 0.f) {};			// 충돌하면 데미지 들어옴 각 클래스에서 구현하세용

	FPOINT GetPos() const { return pos; }
	bool IsDead() const { return bDead; }
protected:
	FPOINT pos;
	FPOINT size;
	bool bDead;
};

