#include "FileManager.h"
#include <fstream>
#include <iostream>

FileManager::FileManager()
{
	//{
	//	CookieHitBox hit;
	//	ns::RectangleInfo bottom{ { 40, 10 }, { 180, 354  } };
	//	ns::RectangleInfo body{ { 45.f,52.f }, { 176,300 } };
	//	ns::CircleInfo cir{ 38,sf::Vector2f{ 186,234} };
	//	hit.type = "Run";
	//	hit.bottom = bottom;
	//	hit.hitBox.circles.push_back(cir);
	//	hit.hitBox.rectangls.push_back(body);
	//	hit.hitBox.rectangls.push_back(bottom);
	//	cookieInfo["Jungle"]["Run"] = hit;
	//	bottom = { { 40, 10 }, { 180, 354  } };
	//	body = { { 45.f,52.f }, { 176,300 } };
	//	CookieHitBox hit1;
	//	hit1.type = "Slide";
	//	hit1.bottom = bottom;
	//	hit1.hitBox.circles.push_back(cir);
	//	hit1.hitBox.rectangls.push_back(body);
	//	hit1.hitBox.rectangls.push_back(bottom);
	//	cookieInfo["Jungle"]["Slide"] = hit1;
	//	ofstream cookie1("config/data/cookieInfo.json");
	//	json data = cookieInfo;
	//	cookie1 << data;
	//	
	//}

	{
		/*TempData t1;
		t1.m_TileTypes = 0;
		t1.m_index = sf::Vector2i{ 0,0 };
		t1.m_chapterIndex = 0;
		t1.m_stateIndex = 0;
		t1.isCollAble = false;

		vector<TempData> tt1;
		tt1.push_back(t1);
		tt1.push_back(t1);
		tt1.push_back(t1);

		vector<vector<TempData>> ttt1;
		ttt1.push_back(tt1);
		ttt1.push_back(tt1);
		ttt1.push_back(tt1);

		vector<vector<vector<TempData>>> tttt1;
		tttt1.push_back(ttt1);
		tttt1.push_back(ttt1);
		tttt1.push_back(ttt1);

		vector<vector<vector<vector<TempData>>>> last;
		last.push_back(tttt1);
		last.push_back(tttt1);
		last.push_back(tttt1);

		json data = last;

		ofstream ofs("json/test.json");
		ofs << data;
		ofs.close();*/

	}


	ifstream test_f("json/test.json");
	json test_json = json::parse(test_f);
	test = test_json;
	test_f.close();

	std::cout << test[0][0][0][0].m_stateIndex << std::endl;
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

const map<string,MapData>& FileManager::GetEpisode(string episode)
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
