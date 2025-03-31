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

	list<GameObject*> GetObjectList(OBJTYPE objType) const {
		return ObjectList[objType];
	}

	void AddObject(GameObject* object, OBJTYPE objType) {
		ObjectList[objType].push_back(object);
	}

	void RenderObject(HDC hdc);
	void RenderUI(HDC hdc);
private:
	list<GameObject*> ObjectList[OBJ_END];
};

