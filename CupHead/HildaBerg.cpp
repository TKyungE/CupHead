#include "HildaBerg.h"
#include "Character.h"
#include "HildaBlimp.h"
#include "Sagittarius.h"
#include "Moon.h"

HildaBerg::HildaBerg()
	: HildaForm{}, Phase{}, Angle{}
{
}

HildaBerg::~HildaBerg()
{
}

void HildaBerg::Init()
{
	pos = { WINSIZE_X - 300.f, WINSIZE_Y / 2.f + 50.f };
	Phase = 0;
	ChangeForm();
}

void HildaBerg::Release()
{
	if (HildaForm)
	{
		HildaForm->Release();
		delete HildaForm;
		HildaForm = NULL;
	}
}

void HildaBerg::Update()
{
	if (Phase < 0) return;

	if (HildaForm)
	{
		HildaForm->Update();

		if (HildaForm->IsDead())
		{
			pos = HildaForm->GetPos();
			Angle = HildaForm->GetMoveAngle();
			HildaForm->Release();
			delete HildaForm;
			HildaForm = NULL;
		}
	}

	if (!HildaForm) ChangeForm();
}

void HildaBerg::Render(HDC hdc)
{
	if (HildaForm) HildaForm->Render(hdc);
}

void HildaBerg::ChangeForm()
{
	switch (Phase)
	{
	case 0:
	{
		HildaBlimp* blimp = new HildaBlimp(0);
		blimp->Init(pos, Angle);
		HildaForm = blimp;
		++Phase;
		break;
	}
	case 1:
	{
		// taurus
		++Phase;
		break;
	}
	case 2:
	{
		HildaBlimp* blimp = new HildaBlimp(1);
		blimp->Init(pos, Angle);
		HildaForm = blimp;
		++Phase;
		break;
	}
	case 3:
	{
		Sagittarius* sag = new Sagittarius();
		sag->Init(pos, Angle);
		HildaForm = sag;
		++Phase;
		break;
	}
	case 4:
	{
		HildaBlimp* blimp = new HildaBlimp(2);
		blimp->Init(pos, Angle);
		HildaForm = blimp;
		++Phase;
		break;
	}
	case 5:
	{
		Moon* moon = new Moon();
		moon->Init();
		HildaForm = moon;
		++Phase;
		break;
	}
	}
}
