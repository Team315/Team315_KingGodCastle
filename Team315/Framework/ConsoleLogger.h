#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class ConsoleLogger
{
public:
	static void PrintVectorState(Vector2f vec, string name = "");
	static void PrintVectorState(Vector2i vec, string name = "");
	static void PrintRectState(FloatRect fr, string name = "");

	static void Print3String(
		string str1, string str2 = "", string str3 = "");
	static void WriteCSV(string id, int loopType, int fps, int frameCount,
		string textureID, int left, int top, int width, int height, 
		int xOrigin, int yOrigin, bool writeToRss = true, int flipX = 0, int flipY = 0);
};
#define CLOG ConsoleLogger