#include "FileManager.h"
#include <fstream>
#include <iostream>

#include "ToolScene.h"

FileManager::FileManager()
{
	tiledata.assign(3,
		vector<vector<vector<TileData>>>(10,
			vector<vector<TileData>>(14,
				vector <TileData>(7)
				)
			)
	);
}

FileManager::~FileManager()
{
}

void FileManager::LoadAll()
{
	ifstream ep1_f("config/data/episode.json");
	json ep1_d = json::parse(ep1_f);
	episodeMap = ep1_d;
	ep1_f.close();

	ifstream hitbox("config/data/hitBox.json");
	json hit_d = json::parse(hitbox);
	hitBoxMap = hit_d;
	hitbox.close();

	ifstream cookie("config/data/cookieInfo.json");
	json cook_d = json::parse(cookie);
	cookieInfo = cook_d;
	cookie.close();
}

const map<string, MapData>& FileManager::GetEpisode(string episode)
{
	return episodeMap[episode];
}
const HitBoxInfo& FileManager::GetHitBox(string name)
{
	return hitBoxMap[name];
}

void FileManager::SaveData(map<string, map<string, MapData>> newData, string path)
{
	episodeMap = newData;

	json data = newData;

	ofstream ofs(path);
	ofs << data;
	ofs.close();
}

void FileManager::SaveDataEpisode(map<string, MapData> newData, string name)
{
	episodeMap[name].clear();
	episodeMap[name] = newData;


	json data = episodeMap;

	ofstream ofs("config/data/episode.json");
	ofs << data;
	ofs.close();
}

void FileManager::SaveTileData(ToolScene& toolScene)
{
	json data = toolScene.GetTilesData();
	ofstream ofs("json/tiledata.json");
	ofs << data;
	ofs.close();
}

void FileManager::LoadTileData(ToolScene& toolScene)
{
	ifstream ifs("json/tiledata.json");
	json playTile = json::parse(ifs);
	Chapters chapters = playTile;
	ifs.close();

	toolScene.SetTilesData(chapters);
}

void FileManager::LoadTileData(Chapters& m_PlayTileList)
{
	ifstream ifs("json/tiledata.json");
	json playTile = json::parse(ifs);
	m_PlayTileList = playTile;
	ifs.close();
}

json FileManager::LoadCharacterData()
{
	ifstream ifs("json/CharacterData.json");
	return json::parse(ifs);
}