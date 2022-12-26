#pragma once

#ifndef tpdef
#define tpdef

#include "pch.h"

template <typename T>
struct PVector
{

	T x, y;

	constexpr PVector() { x = 0; y = 0; }
	constexpr PVector(const T& v) { x = v; y = v; }
	constexpr PVector(const T& a, const T& b) { x = a; y = b; }

	PVector operator+(const PVector& v) const { return { x + v.x, y + v.y }; }
	PVector operator-(const PVector& v) const { return { x - v.x, y - v.y }; }
	PVector operator*(const PVector& v) const { return { x * v.x, y * v.y }; }
	PVector operator/(const PVector& v) const { return { x / v.x, y / v.y }; }
	void operator=(const PVector& v) { x = v.x; y = v.y; }

	PVector operator+(const T& v) const { return { x + v, y + v }; }
	PVector operator-(const T& v) const { return { x - v, y - v }; }
	PVector operator*(const T& v) const { return { x * v, y * v }; }
	PVector operator/(const T& v) const { return { x / v, y / v }; }

	PVector operator+=(const PVector& v) { return { x += v.x, y += v.y }; }
	PVector operator-=(const PVector& v) { return { x -= v.x, y -= v.y }; }
	PVector operator*=(const PVector& v) { return { x *= v.x, y *= v.y }; }
	PVector operator/=(const PVector& v) { return { x /= v.x, y /= v.y }; }
	bool operator==(const PVector& v) const { return  x == v.x && y == v.y; }
	bool operator!=(const PVector& v) const { return  x != v.x || y != v.y; }

	PVector operator+=(const T& v) { return { x += v, y += v }; }
	PVector operator-=(const T& v) { return { x -= v, y -= v }; }
	PVector operator*=(const T& v) { return { x *= v, y *= v }; }
	PVector operator/=(const T& v) { return { x /= v, y /= v }; }

	float mag() const {
		return sqrtf(x * x + y * y);
	}
	float dot(const PVector& vec) const
	{
		return x * vec.x + y * vec.y;
	}
	float normalize() {
		const float length = this->mag();
		float ilength;

		if (length) {
			ilength = 1 / length;
			this->x *= ilength;
			this->y *= ilength;
		}

		return length;
	}
	float dist(const PVector& vec) const
	{
		const PVector sub = *this - vec;
		return sub.mag();
	}
	PVector inverse() const
	{
		return { -x, -y };
	}
	float MagSq() const { //magnitude squared
		return (x * x + y * y);
	}


};
struct Pixel
{
	int r, g, b, a;

	constexpr Pixel() { r = 0, g = 0, b = 0, a = 255; }
	constexpr Pixel(const int32_t val) { r = val, g = val, b = val, a = val; };
	constexpr Pixel(const int32_t _r, const int32_t _g, const int32_t _b, const int32_t _a) { r = _r, g = _g, b = _b, a = _a; }

	Pixel operator=(const Pixel& px) {
		return { px.r, px.g, px.b, px.a };
	}




};

namespace COL
{
	constexpr Pixel BLACK = Pixel(0, 0, 0, 255);
	constexpr Pixel WHITE = Pixel(255, 255, 255, 255);
	constexpr Pixel RED = Pixel(255, 0, 0, 255);
	constexpr Pixel GREEN = Pixel(0, 255, 0, 255);
	constexpr Pixel BLUE = Pixel(0, 0, 255, 255);
	constexpr Pixel YELLOW = Pixel(255, 255, 0, 255);
	constexpr Pixel PURPLE = Pixel(255, 0, 255, 255);
	constexpr Pixel LIGHTBLUE = Pixel(0, 255, 255, 255);

}

#endif