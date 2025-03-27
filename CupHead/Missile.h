#pragma once
#include "GameObject.h"

class Image;
class Missile : public GameObject
{
private:
	FPOINT pos;
	bool isActived;
	COLORREF color;
	float moveSpeed;
	float angle;
	FPOINT destination;
	int size;
	Image* image;

public:
	void Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void Move();
	bool IsOutofScreen();

	// getter, setter
	inline bool GetIsActived() { return isActived; }
	inline void SetIsActived(bool isActived) {
		this->isActived = isActived;	}

	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return pos; }

	inline void SetAngle(float angle) { this->angle = angle; }
	inline int GetSize() { return size; }

	Missile();
	~Missile();

};

