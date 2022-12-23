#include "FingerSnap.h"
#include "Character.h"

FingerSnap::FingerSnap()
	:isPlaying(false)
{
}

FingerSnap::~FingerSnap()
{
}

void FingerSnap::Enter()
{
	SetAni();
}

void FingerSnap::Init()
{
}

void FingerSnap::Release()
{
}

void FingerSnap::Update(float dt)
{
	if (isPlaying)
	m_FingerSnap.Update(dt);
}

void FingerSnap::Draw(RenderWindow& window)
{
	if (!m_FingerSnap.GetEndFrame())
	{
		SpriteObj::Draw(window);
	}
}

void FingerSnap::SetAni()
{
	m_FingerSnap.SetTarget(&sprite);
	m_FingerSnap.AddClip(*RESOURCE_MGR->GetAnimationClip("Fx_FingerSnap"));
	SetPos({ GAME_SCREEN_WIDTH * 0.5f ,GAME_SCREEN_HEIGHT * 0.5f - 50.f });
	SetScale(3.f, 3.f);
}

void FingerSnap::SetIsPlaying(bool is)
{
	isPlaying = is;
}

void FingerSnap::PlayingAni()
{
	isPlaying = true;
	m_FingerSnap.Play("Fx_FingerSnap");
	ActionSkill();
}

void FingerSnap::ActionSkill()
{
	vector<SpriteObj*>& mainGrid = GAME_MGR->GetMainGridRef();
	vector<SpriteObj*> target;

	int count = 0;
	for (auto monster : mainGrid)
	{
		if (monster != nullptr && monster->GetType().compare("Obstacle"))
		{
			target.push_back(monster);
			++count;
		}
	}
	int deadCount;

	if (count % 2 != 0)
	{
		deadCount = count / 2 + 1;
	}
	else
	{
		deadCount = count / 2;
	}

	int arr[100];
	int num = target.size();
	int n = 0;

	while (n < num)
	{
		int i = 0;

		int r = Utils::RandomRange(0, num);

		for (i = 0; i < n; i++)
			if (arr[i] == r) break;

		if (n == i) arr[n++] = r;
	}

	for (int i = 0; i < deadCount; i++)
	{
		dynamic_cast<Character*>(target[arr[i]])->TakeDamege(99999.f);
		cout << dynamic_cast<Character*>(target[arr[i]])->GetName() <<" die" << endl;
	}

	SOUND_MGR->Play("sounds/panel_FingerSnap.ogg", 30.f, false);
}
