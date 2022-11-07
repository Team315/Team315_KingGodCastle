#include "StringTable.h"
#include "../3rd/rapidcsv.h"
#include <SFML/Graphics.hpp>

Languages StringTable::currentLang(Languages::ENG);
StringTable::StringTable()
	: DataTable(Types::String)
{
	fileNames.push_back("tables/StringTable_Kor.csv");
	fileNames.push_back("tables/StringTable_Eng.csv");
}

StringTable::~StringTable()
{
}

void StringTable::SetLanguage(Languages lang)
{
	Release();

	currentLang = lang;
	rapidcsv::Document doc(fileNames[(int)currentLang], rapidcsv::LabelParams(0, -1));
	vector<string> keys = doc.GetColumn<string>(0);		// ID
	vector<string> values = doc.GetColumn<string>(1);	// STRING

	for (int j = 0; j < doc.GetRowCount(); ++j)
	{
		if (table.find(keys[j]) != table.end())
		{
			//¿?·ù
			return;
		}
		table.insert({ keys[j], s2w(values[j]) });
	}
}

const wstring& StringTable::Get(const string& id)
{
	auto find = table.find(id);
	if (find == table.end())
		return L"Undefined ID";
	return find->second;
}

void StringTable::Release()
{
	table.clear();
}

bool StringTable::Load()
{
	SetLanguage(currentLang);

	return true;
}

std::wstring StringTable::s2w(const std::string& var)
{
	static std::locale loc("");
	auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
	return std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).from_bytes(var);
}