#include "ConsoleLogger.h"
#include <iostream>
#include <sstream>
#include "../3rd/CSVWriter.h"

void ConsoleLogger::PrintVectorState(Vector2f vec, string name)
{
	cout << name << 
		"(" << vec.x << " " << vec.y << ")" << endl;
}

void ConsoleLogger::PrintVectorState(Vector2i vec, string name)
{
	cout << name << "(" << vec.x << " " << vec.y << ")" << endl;
}

void ConsoleLogger::PrintRectState(FloatRect fr, string name)
{
	cout << name
		<< " left: " << fr.left
		<< " top: " << fr.top
		<< " width: " << fr.width
		<< " height: " << fr.height << endl;
}

void ConsoleLogger::Print3String(string str1, string str2, string str3)
{
	stringstream ss;
	ss << str1 << " " << str2 << " " << str3;
	cout << ss.str() << endl;
}

// Main 맨 윗줄에
// LOG::WriteCSV("파일명/키", loopType, fps, 프레임 수, 
// 리소스 파일명 확장자 빼고, L, T, W, H, X, Y, false);
void ConsoleLogger::WriteCSV(string id, 
	int loopType, int fps, int frameCount,
	string textureID, int left, int top, int width, int height,
	int xOrigin, int yOrigin, bool writeToRss, int flipX, int flipY)
{
	CSVWriter csv(",");
	csv.newRow() << "ID" << "LOOPTYPE (0: Single 1: Move)" << "FPS";
	csv.newRow() << id << loopType << fps;
	csv.newRow();
	csv.newRow() << "TEXTURE ID" << "L" << "T" << "W" << "H" << "W" << "Y" << "FlipX" << "FlipY";

	csv.enableAutoNewRow(9);
	int leftStart = 0;
	string texturePath = "graphics/" + textureID + ".png";
	for (int i = 0; i < frameCount; i++)
	{
		csv << texturePath << leftStart << top << width << height << xOrigin << yOrigin << flipX << flipY;
		leftStart += left;
	}
	cout << csv << endl;

	string filepath = "animations/" + id + ".csv";
	csv.writeToFile(filepath);

	if (!writeToRss)
		return ;
	CSVWriter resourceFile(",");
	resourceFile.newRow() << filepath << 3;

	cout << resourceFile << endl;
	resourceFile.writeToFile("Resources.csv", true);
}