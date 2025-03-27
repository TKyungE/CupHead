#pragma once
#include "Singleton.h"
#include "config.h"
#include <list>

class GameObject;
class ObjectManager : public Singleton<ObjectManager>
{
public:
	void Init();
	void Update();
	void Render();
	void Release();
private:
	list<GameObject*> ObjectList[OBJ_END];
};

