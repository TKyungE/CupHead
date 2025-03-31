#pragma once
#include "GameObject.h"
#include <list>

// background
// Sky 1 loop
// Cloud 5
// dark_hill 1 loop
// MainGround 2 type rotation
// 
// foreground SET render
// SET end -> next SET after 2~8 sec
// large_forest SET 7
// medium_forest SET 4
// small_forest_a SET 6
// small_forest_b SET 4
// 
// SET + foreground object 1 of 6 type randomly

namespace BackGroundInfo
{
	enum EBackGroundType
	{
		SKY,
		CLOUD,
		DARK_HILL,
		MAIN_GROUND,
		BACKTYPE_END,
	};

	extern string BackGroundTypes[EBackGroundType::BACKTYPE_END];
	extern int BackGroundNum[EBackGroundType::BACKTYPE_END];

	enum EForeGroundType
	{
		LARGE_FOREST,
		MEDIUM_FOREST,
		SMALL_FOREST_A,
		SMALL_FOREST_B,
		FORETYPE_END
	};

	extern string ForeGroundTypes[EForeGroundType::FORETYPE_END];
	extern int ForeGroundNum[EForeGroundType::FORETYPE_END];

	extern string ForeObject;
	extern int ForeObjectNum;
}


class Image;
class BackGround : public GameObject
{
public:
	BackGround(FPOINT InPos, Image* _image, int _Speed, bool _Loop);
	virtual ~BackGround();

	void Init();
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);

	float GetRightPos() const;
	inline bool IsOutOfScreen() const { return IsOut; }
private:
	FPOINT StartPos;
	Image* image;
	int Speed;
	bool IsOut;
	bool Loop;
};

// not Singleton
class BackGroundManager : public GameObject
{
public:
	BackGroundManager();
	virtual ~BackGroundManager();

	virtual void Init();
	virtual void Release();
	virtual void Update();
	void RenderBackGround(HDC hdc);
	void RenderForeGround(HDC hdc);

private:
	void PrepareNextBackGround();
	void PrepareNextForeGround();
	void PrepareNextForeObject();

private:
	void AddBackGround(BackGroundInfo::EBackGroundType type, int num, int speed, bool loop, bool init, bool bottomSide = true);
	void AddForeGround(BackGroundInfo::EForeGroundType type, int num, int speed, bool loop, bool init);
	void AddForeObject(string name, int num, int speed, bool loop, bool init);

	vector<BackGround*> BackGroundList[BackGroundInfo::EBackGroundType::BACKTYPE_END];
	vector<BackGround*> ForeGroundList[BackGroundInfo::EForeGroundType::FORETYPE_END];
	vector<BackGround*> ForeObjectList;

	int MainGroundIndex;

	int SelectedForeGround;
	float ForeGroundElapsedTime;
	float ForeGroundCoolTime;
};