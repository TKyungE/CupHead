#include "SagittariusStar.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "CommonFunction.h"

SagittariusStar::SagittariusStar(FPOINT InPos, float InGuidedTime, float InAngle)
	: State(EStarState::End), GuidedTime(InGuidedTime), Angle(InAngle), CurrentTime(0.f), AngularVelocity(0.f), maxAngularAcceleration(0.2f), maxAngularVelocity(0.1f), friction(0.3f)
{
	pos = InPos;
	StartPos = InPos;
}

void SagittariusStar::Init()
{
	State = EStarState::Fire;
	Speed = 250.f;
	FrameSpeed = 20.f;

	MaxHp = 2;
	Hp = MaxHp;

	image = ImageManager::GetInstance()->AddImage("sagg_star", L"Image/CupHead/Hilda Berg/Sagittarius/Arrow/Star/sagg_star.bmp", 1157, 90, 13, 1, true, RGB(255, 0, 255));

	Collider* collider = new Collider(this, COLLIDERTYPE::Sphere, { 0.f,0.f }, 30.f, true, 1.f);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_MONSTER_WEAPON);
}

void SagittariusStar::Update()
{
	UpdateFrame();

	Move();
}

void SagittariusStar::Render(HDC hdc)
{
	if (image != nullptr)
		image->FrameRender(hdc, (int)pos.x, (int)pos.y, CurFrameIndex, 0);
}

void SagittariusStar::Move()
{
	switch (State)
	{
	case SagittariusStar::EStarState::Fire:
		Fire();
		break;
	case SagittariusStar::EStarState::Guided:
		Guided();
		break;
	case SagittariusStar::EStarState::Done:
		Done();
		break;
	case SagittariusStar::EStarState::Dead:
		Dead();
		break;
	case SagittariusStar::EStarState::End:
		break;
	default:
		break;
	}
}

void SagittariusStar::Fire()
{
	pos.x += Speed * cosf((float)DEG_TO_RAD(Angle)) * TimerManager::GetInstance()->GetDeltaTime();
	pos.y += Speed * sinf((float)DEG_TO_RAD(Angle)) * TimerManager::GetInstance()->GetDeltaTime();

	const float distance = sqrtf(powf(pos.x - StartPos.x, 2) + powf(pos.y - StartPos.y, 2));

	if (distance >= 200.f)
		State = EStarState::Guided;
}

void SagittariusStar::Guided()
{
	CurrentTime += TimerManager::GetInstance()->GetDeltaTime();

	list<GameObject*> playerList = ObjectManager::GetInstance()->GetObjectList(OBJTYPE::OBJ_PLAYER);
	if (!playerList.empty() && CurrentTime <= GuidedTime)
	{
		GameObject* player = playerList.front();
		const float targetAngle = atan2f(player->GetPos().y - pos.y, player->GetPos().x - pos.x);
		const float angleDiff = NoramlizeAngle(targetAngle - (float)DEG_TO_RAD(Angle));

		//각 가속도
		float angularAcceleration = maxAngularAcceleration * (angleDiff > 0 ? 1 : -1);
		AngularVelocity += angularAcceleration;

		if (AngularVelocity > maxAngularVelocity)
			AngularVelocity = maxAngularVelocity;
		else if (AngularVelocity < -maxAngularVelocity)
			AngularVelocity = -maxAngularVelocity;

		AngularVelocity *= friction;

		Angle += AngularVelocity;
		Angle = (float)RAD_TO_DEG(NoramlizeAngle((float)DEG_TO_RAD(Angle)));

		pos.x += cosf((float)DEG_TO_RAD(Angle)) * Speed * TimerManager::GetInstance()->GetDeltaTime();
		pos.y += sinf((float)DEG_TO_RAD(Angle)) * Speed * TimerManager::GetInstance()->GetDeltaTime();
	}
	else
		State = EStarState::Done;
}

void SagittariusStar::Done()
{
	pos.x += cosf((float)DEG_TO_RAD(Angle)) * Speed * TimerManager::GetInstance()->GetDeltaTime();
	pos.y += sinf((float)DEG_TO_RAD(Angle)) * Speed * TimerManager::GetInstance()->GetDeltaTime();

	if (OutOfScreen(pos, image->GetFrameWidth(), image->GetFrameHeight()))
		bDead = true;
}

void SagittariusStar::Dead()
{
	bDead = true;
}

float SagittariusStar::SmoothAngle(float currentAngle, float targetAngle, float maxAngleSpeed)
{
	float deltaAngle = targetAngle - currentAngle;

	if (deltaAngle > maxAngleSpeed)
		deltaAngle = maxAngleSpeed;
	else if (deltaAngle < -maxAngleSpeed)
		deltaAngle = -maxAngleSpeed;

	return currentAngle + deltaAngle;
}

float SagittariusStar::NoramlizeAngle(float angle)
{
	while (angle > PI)
		angle -= 2.f * PI;
	while (angle < -PI)
		angle += 2.f * PI;

	return angle;
}

void SagittariusStar::TakeDamage(int damage)
{
	Hp -= damage;

	if (Hp <= 0)
		State = EStarState::Dead;
}

void SagittariusStar::Release()
{
}
