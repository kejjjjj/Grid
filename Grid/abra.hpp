#pragma once

#ifndef _abra
#define _abra

#include "pch.h"

float VectorAngle(const PVector<float>& s, const PVector<float> e);
float VectorAngle(const PVector<int>& e); //where s = 0,0 
float AngleFromAxis(const PVector<int>& pos, float angle);
template <typename T> 
T clamp(T val, const T min, const T max)
{

	if (val < min)	val = min;
	if (val > max)	val = max;

	return val;

}
#endif