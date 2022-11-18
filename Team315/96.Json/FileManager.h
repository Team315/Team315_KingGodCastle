#pragma once
#include "Singleton.h"
#include "FileData.h"
#include "ToolScene.h"

using namespace ns;

class FileManager : public Singleton<FileManager>
{
private:
	map<string, map<string, MapData>> episodeMap; //find by path
	map<string, HitBoxInfo> hitBoxMap; //find by path
	map<string, map<string, CookieHitBox>> cookieInfo; //find by cookie name and cookie state. return now animation hitbox

	vector<vector<vector<vector<TileData>>>> tiledata;
	//cookieInfo[Jungle][Jump]
public:
	FileManager();
	~FileManager();

	void LoadAll();
	const map<string, MapData>& GetEpisode(string name);
	const HitBoxInfo& GetHitBox(string name);
	const  map<string, CookieHitBox>& GetCookie(string name) {return cookieInfo[name];}
	const map<string, map<string, MapData>> GetAllEpisode() { return episodeMap; };

	void SaveData(map<string, map<string, MapData>> newData, string path);
	void SaveDataEpisode( map<string, MapData> newData, string name);

	void SaveDataMapInfo(TileData tileData, int chapter, int stage, int cols, int raws);

	void SaveTileData(ToolScene& scene);
	void LoadTileData(ToolScene& scene);

};

#define FILE_MGR (FileManager::GetInstance())