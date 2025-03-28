#include "ObjectManager.h"
#include "GameObject.h"

void ObjectManager::Init()
{
}

void ObjectManager::Update()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = ObjectList[i].begin(); iter != ObjectList[i].end();)
		{
			(*iter)->Update();
			if ((*iter)->IsDead())
			{
				(*iter)->Release();
				delete (*iter);
				iter = ObjectList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void ObjectManager::Render(HDC hdc)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : ObjectList[i])
		{
			iter->Render(hdc);
		}
	}
}

void ObjectManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : ObjectList[i])
		{
			iter->Release();
			delete iter;
		}
		ObjectList[i].clear();
	}

	ReleaseInstance();
}
