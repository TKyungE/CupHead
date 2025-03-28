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
	void Render(HDC hdc);
	void Release();

	void AddObject(GameObject* object, OBJTYPE objType) {
		ObjectList[objType].push_back(object);
	}
private:
	list<GameObject*> ObjectList[OBJ_END];
};

