#pragma once
#include "../3rd/SingleTon.h"
#include <SFML/Audio.hpp>
#include <list>

#define SOUND_MGR (SoundMgr::GetInstance())

using namespace sf;
using namespace std;

class SoundMgr : public Singleton<SoundMgr>
{
private:
	list<Sound*> playing;
	list<Sound*> waiting;

	float globalVolume;

public:
	SoundMgr();
	virtual ~SoundMgr();
	
	const int TotalChannels;

	void Init();
	void Release();

	void Play(string id, float volume = 100.f, bool loop = false);
	void StopAll();

	void Update(float dt);
	void SetVolume(float num);
};