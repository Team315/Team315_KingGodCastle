#include "Utils.h"
#define _USE_MATH_DEFINES
#include <math.h>

std::random_device Utils::rd;
std::mt19937 Utils::gen(Utils::rd());

void Utils::SetOrigin(Text& obj, Origins origin)
{
	SetOrigin(obj, origin, obj.getLocalBounds());
}

void Utils::SetOrigin(Sprite& obj, Origins origin)
{
	SetOrigin(obj, origin, obj.getLocalBounds());
}

void Utils::SetOrigin(Shape& obj, Origins origin)
{
	SetOrigin(obj, origin, obj.getLocalBounds());
}

void Utils::SetOrigin(Transformable& obj, Origins origin, FloatRect rect)
{
	Vector2f originPos(rect.width, rect.height);
	originPos.x *= ((int)origin % 3) * 0.5f;
	originPos.y *= ((int)origin / 3) * 0.5f;
	obj.setOrigin(originPos);
}

float Utils::Clamp(float v, float min, float max)
{
	if ( v < min )
		return min;
	else if ( v > max )
		return max;
	return v;
}

int Utils::RandomRange(int min, int maxExclude)
{
	return (gen() % (maxExclude - min)) + min;
}

float Utils::RandomRange(float min, float maxInclude)
{
	uniform_real_distribution<> dist(min, maxInclude);
	return dist(gen);
}

float Utils::RandomZeroToOne()
{
	return RandomRange(0.f, 1.f);
}

Vector2f Utils::RandomInCirclePoint()
{
	return RandomZeroToOne() * RandomOutCirclePoint();
}

Vector2f Utils::RandomOutCirclePoint()
{
	float radian = RandomRange(0.f, M_PI * 2);
	return Vector2f({ cos(radian), sin(radian) });
}

float Utils::SqrMagnitude(const Vector2f& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float Utils::Magnitude(const Vector2f& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

Vector2f Utils::Normalize(const Vector2f& vec)
{
	float mag = Magnitude(vec);
	if ( mag == 0.f )
	{
		return vec;
	}
	return vec / mag;
}

float Utils::Distance(const Vector2f& vec1, const Vector2f& vec2)
{
	return Magnitude(vec1 - vec2);
}

float Utils::Dot(const Vector2f& a, const Vector2f& b)
{
	return a.x * b.x + a.y + b.y;
}

Vector2f Utils::GetNormal(const Vector2f& vec)
{
	return Vector2f(-vec.y, vec.x);
}

float Utils::SqrMagnitude(const Vector2i& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float Utils::Magnitude(const Vector2i& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float Utils::Distance(const Vector2i& vec1, const Vector2i& vec2)
{
	return Magnitude(vec1 - vec2);
}

bool Utils::EqualFloat(float a, float b, float epsilon)
{
	return fabs(a - b) < epsilon;
}

float Utils::GetMinScaleRatioFromFloatRect(float sizeX, float sizeY, FloatRect fr)
{
	float width = sizeX / fr.width;
	float height = sizeY / fr.height;
	float min = width > height ? height : width;
	return min;
}

std::wstring Utils::s2w(const std::string& var)
{
	static std::locale loc("");
	auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
	return std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).from_bytes(var);
}

wstring Utils::ReplaceNewLine(wstring str)
{
	wstring toFind = s2w("\\n");
	wstring toChange = s2w("\u000A");

	while (str.find(toFind) != wstring::npos)
	{
		str.replace(str.find(toFind), toFind.length(), toChange);
	}
	return str;
}