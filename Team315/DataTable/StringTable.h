#pragma once
#include "DataTable.h"
#include <map>
#include <vector>
#include <string>

using namespace std;


enum class Languages
{
	KOR,
	ENG,
	COUNT,
};

class StringTable : public DataTable
{
private:
	//map<Languages, map<string, string>*> tables;

	map<string, wstring> table;	// 
	static Languages currentLang;

public:
	StringTable();
	virtual ~StringTable();

	static Languages getCurrentLang() { return currentLang; }
	static void SetCurrentLang(Languages lang) {currentLang = lang; }
	void SetLanguage(Languages lang);

	const wstring& Get(const string& id);
	//const string& Get(Languages lang, const string& id);

	virtual void Release();
	virtual bool Load();

	wstring s2w(const std::string& var);

	vector<string> fileNames;
};