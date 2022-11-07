#include "ResourceMgr.h"
#include "../3rd/rapidcsv.h"
#include "ConsoleLogger.h"

string ResourceMgr::filePath("Resources.csv");

ResourceMgr::ResourceMgr()
{
}

ResourceMgr::~ResourceMgr()
{
	Release();
}

bool ResourceMgr::LoadAll()
{
	Release();
	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));

	auto ids = doc.GetColumn<string>(0);
	auto types = doc.GetColumn<int>(1);

	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		if (!Load((ResourceTypes)types[i], ids[i]))
		{
			CLOG::Print3String("resource manager load fail! file name: ", ids[i]);
			return false;
		}
	}
	CLOG::Print3String("resource manager load success");
	return true;
}

bool ResourceMgr::LoadTexture(string id)
{
	if (texMap.find(id) != texMap.end())
	{
		CLOG::Print3String("resource load fail", id);
		return false;
	}

	Texture* texture = new Texture();

	if (!(texture->loadFromFile(id)))
	{
		delete texture;
		return false;
	}
	texMap[id] = texture;
	return true;
}

bool ResourceMgr::LoadFont(string id)
{
	if (fontMap.find(id) != fontMap.end())
	{
		CLOG::Print3String("font load fail", id);
		return false;
	}

	Font* font = new Font();

	if (!(font->loadFromFile(id)))
	{
		delete font;
		return false;
	}
	fontMap[id] = font;
	return true;
}

bool ResourceMgr::LoadSoundBuffer(string id)
{
	if (soundMap.find(id) != soundMap.end())
	{
		CLOG::Print3String("sound load fail", id);
		return false;
	}

	SoundBuffer* sound = new SoundBuffer();

	if (!(sound->loadFromFile(id)))
	{
		delete sound;
		return false;
	}
	soundMap[id] = sound;
	return true;
}

bool ResourceMgr::LoadAnimationClip(string id)
{
	if (animationClipMap.find(id) != animationClipMap.end())
	{
		CLOG::Print3String("animation load fail", id);
		return false;
	}

	rapidcsv::Document csv(id);
	auto rowClip = csv.GetRow<string>(0);
	AnimationClip* clip = new AnimationClip();
	clip->id = rowClip[0];
	clip->loopType = (LoopTypes)stoi(rowClip[1]);
	clip->fps = stoi(rowClip[2]);

	for (int i = 3; i < csv.GetRowCount(); ++i)
	{
		clip->frames.push_back(csv.GetRow<string>(i));
	}
	animationClipMap.insert({ clip->id, clip });
	return true;
}

bool ResourceMgr::Load(ResourceTypes type, string id)
{
	switch (type)
	{
	case ResourceTypes::Texture:
		return LoadTexture(id);
	case ResourceTypes::Font:
		return LoadFont(id);
	case ResourceTypes::SoundBuffer:
		return LoadSoundBuffer(id);
	case ResourceTypes::AnimationClip:
		return LoadAnimationClip(id);
	}

	return false;
}

void ResourceMgr::Release()
{
	for (auto it : texMap)
	{
		delete it.second;
	}
	texMap.clear();
	for (auto it : fontMap)
	{
		delete it.second;
	}
	fontMap.clear();
	for (auto it : soundMap)
	{
		delete it.second;
	}
	soundMap.clear();
	for (auto it : animationClipMap)
	{
		delete it.second;
	}
	animationClipMap.clear();
}

Texture* ResourceMgr::GetTexture(string id)
{
	auto it = texMap.find(id);
	if (it == texMap.end())
		return nullptr;
	return it->second;
}

Font* ResourceMgr::GetFont(string id)
{
	auto it = fontMap.find(id);
	if (it == fontMap.end())
		return nullptr;
	return it->second;
}

SoundBuffer* ResourceMgr::GetSoundBuffer(string id)
{
	auto it = soundMap.find(id);
	if (it == soundMap.end())
		return nullptr;
	return it->second;
}

AnimationClip* ResourceMgr::GetAnimationClip(string id)
{
	auto it = animationClipMap.find(id);
	if (it == animationClipMap.end())
		return nullptr;
	return it->second;
}