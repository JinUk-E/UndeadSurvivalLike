#pragma once
#include <cmath>
#include <windows.h>

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

struct Stat
{
	int32 Health{ 0 };
	int32 MaxHealth{ 0 };
	float Speed{ 0.0f };
};

struct Vector2
{
	Vector2() {}
	Vector2(float x, float y) : X(x), Y(y) {}
	Vector2(POINT point) : X(static_cast<float>(point.x)), Y(static_cast<float>(point.y)) {}

	float X{ 0.0f };
	float Y{ 0.0f };

	// Operators
	Vector2 operator+(const Vector2& others){ return Vector2(X + others.X, Y + others.Y);}

	Vector2 operator-(const Vector2& others){ return Vector2(X - others.X, Y - others.Y);}

	Vector2 operator*(const float& scalar){	return Vector2(X * scalar, Y * scalar);}

	Vector2 operator/(const float& scalar){	return Vector2(X / scalar, Y / scalar);}

	Vector2& operator+=(const Vector2& others)
	{
		X += others.X;
		Y += others.Y;
		return *this;
	}

	Vector2& operator-=(const Vector2& others)
	{
		X -= others.X;
		Y -= others.Y;
		return *this;
	}

	Vector2& operator*=(const float& scalar)
	{
		X *= scalar;
		Y *= scalar;
		return *this;
	}

	Vector2& operator/=(const float& scalar)
	{
		X /= scalar;
		Y /= scalar;
		return *this;
	}

	bool operator==(const Vector2& others){	return X == others.X && Y == others.Y;}

	bool operator!=(const Vector2& others){	return X != others.X || Y != others.Y;}

	float LengthNonSquared(){return X * X + Y * Y;}

	float Length(){return std::sqrt(LengthNonSquared());}

	Vector2 Normalize(){return *this / Length();}
	void NormalizeSelf(){*this /= Length();}

	float Dot(const Vector2& others){return X * others.X + Y * others.Y;}
	float Cross(const Vector2& others){return X * others.Y - Y * others.X;}

};

struct Vector2Int
{
	Vector2Int() {}
	Vector2Int(int32 x, int32 y) : X(x), Y(y) {}
	Vector2Int(POINT point) : X(point.x), Y(point.y) {}

	int32 X{ 0 };
	int32 Y{ 0 };

	// Operators
	Vector2Int operator+(const Vector2Int& others){ return Vector2Int(X + others.X, Y + others.Y);}
	Vector2Int operator-(const Vector2Int& others){ return Vector2Int(X - others.X, Y - others.Y);}
	Vector2Int operator*(const int32& scalar){	return Vector2Int(X * scalar, Y * scalar);}
	Vector2Int operator/(const int32& scalar){	return Vector2Int(X / scalar, Y / scalar);}

	Vector2Int& operator+=(const Vector2Int& others)
	{
		X += others.X;
		Y += others.Y;
		return *this;
	}

	Vector2Int& operator-=(const Vector2Int& others)
	{
		X -= others.X;
		Y -= others.Y;
		return *this;
	}

	Vector2Int& operator*=(const int32& scalar)
	{
		X *= scalar;
		Y *= scalar;
		return *this;
	}

	Vector2Int& operator/=(const int32& scalar)
	{
		X /= scalar;
		Y /= scalar;
		return *this;
	}

	bool operator==(const Vector2Int& others){	return X == others.X && Y == others.Y;}
	bool operator!=(const Vector2Int& others){	return X != others.X || Y != others.Y;}

	int32 LengthNonSquared(){return X * X + Y * Y;}
	float Length(){return static_cast<float>(std::sqrt(LengthNonSquared()));}
	int32 Dot(const Vector2Int& others){return X * others.X + Y * others.Y;}
	int32 Cross(const Vector2Int& others){return X * others.Y - Y * others.X;}
};

using Postion = Vector2;
using PosInt = Vector2Int;