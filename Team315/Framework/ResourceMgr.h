#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include "AnimationClip.h"
#include "../3rd/SingleTon.h"

#define RESOURCE_MGR (ResourceMgr::GetInstance())

using namespace sf;
using namespace std;

enum class ResourceTypes
{
	Texture, Font, SoundBuffer, AnimationClip
};

class ResourceMgr : public Singleton<ResourceMgr>
{
private:
	map<string, Texture*> texMap;
	map<string, Font*> fontMap;
	map<string, SoundBuffer*> soundMap;
	map<string, AnimationClip*> animationClipMap;

public:
	static string filePath;
	ResourceMgr();
	~ResourceMgr();
	
	bool LoadAll();
	bool Load(ResourceTypes type, string id);
	void Release();

	bool LoadTexture(string id);
	bool LoadFont(string id);
	bool LoadSoundBuffer(string id);
	bool LoadAnimationClip(string id);

	Texture* GetTexture(string id);
	Font* GetFont(string id);
	SoundBuffer* GetSoundBuffer(string id);
	AnimationClip* GetAnimationClip(string id);
};