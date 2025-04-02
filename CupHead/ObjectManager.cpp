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
			if ((*iter)->IsDead())
			{
				(*iter)->Release();
				delete (*iter);
				(*iter) = nullptr;
				iter = ObjectList[i].erase(iter);
			}
			else
			{
				(*iter)->Update();
				++iter;
			}
		}
	}
}

void ObjectManager::Render(HDC hdc)
{
	RenderObject(hdc);
}

void ObjectManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : ObjectList[i])
		{
			iter->Release();
			delete iter;
			iter = nullptr;
		}
		ObjectList[i].clear();
	}

	ReleaseInstance();
}

void ObjectManager::RenderObject(HDC hdc)
{
	for (auto& iter : ObjectList[OBJ_PLAYER])
		iter->Render(hdc);

	for (auto& iter : ObjectList[OBJ_MONSTER])
		iter->Render(hdc);

	for (auto& iter : ObjectList[OBJ_PLAYER_WEAPON])
		iter->Render(hdc);

	for (auto& iter : ObjectList[OBJ_MONSTER_WEAPON])
		iter->Render(hdc);
}

void ObjectManager::RenderUI(HDC hdc)
{
	for (auto& iter : ObjectList[OBJ_UI])
		iter->Render(hdc);

	for (auto& iter : ObjectList[OBJ_UPPERUI])
		iter->Render(hdc);
}
