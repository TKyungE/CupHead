#pragma once
#include "GameObject.h"
class Image;

class Actor : public GameObject
{
public:
	Actor();
	virtual ~Actor();

public:
	virtual void Init() override;						
	virtual void Release() override;					
	virtual void Update() override;
	virtual void Render(HDC hdc) override;				

	virtual void UpdateFrame();
	virtual void TakeDamage(float damage = 0.f) override;
	
public:
	inline void SetImage(Image* _Image) { image = _Image; }
	inline Image* GetImage() const { return image; }

protected:
	Image* image;
	int CurFrameIndex;
	float FrameSpeed;
	float FrameTime;
	bool IsFlip;
	bool IsStayMaxFrame;
};

