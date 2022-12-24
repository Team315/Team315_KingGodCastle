#pragma once
#include "Singleton.h"
#include "FileData.h"

using namespace ns;
class ToolScene;
class FileManager : public Singleton<FileManager>
{
private:
	map<string, map<string, MapData>> episodeMap; //find by path
	map<string, HitBoxInfo> hitBoxMap; //find by path
	map<string, map<string, CookieHitBox>> cookieInfo; //find by cookie name and cookie state. return now animation hitbox

	vector<vector<vector<vector<TileData>>>> tileData;
	vector<BackGroundData> backGroundData;
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

	void SaveTileData(ToolScene& scene);
	void LoadTileData(ToolScene& scene);
	void LoadTileData(Chapters& m_PlayTileList);



	void SaveBackGroundData(vector<BackGroundData> datas);
	json LoadByFilePath(string filePath);
};

#define FILE_MGR (FileManager::GetInstance())