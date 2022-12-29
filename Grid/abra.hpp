#pragma once

#ifndef _abra
#define _abra

#include "pch.h"

#include "olcPixelGameEngine.h"

float VectorAngle(const PVector<float>& s, const PVector<float> e);
float VectorAngle(const PVector<int>& e); //where s = 0,0 
float VectorAngleDifference(const PVector<float>& a, const PVector<float>& b);
PVector<float> VectorLinearCombination(const PVector<float>& a, const PVector<float>& b, const float scalarX = .5f, const float scalarY = .5f);
PVector<float> VectorConvexCombination(const PVector<float>& a, const PVector<float>& b, const float alpha, const float beta);
bool VectorSimultaneousEquation(const PVector<float>& a, const PVector<float>& b, const PVector<float>& linearcombination, PVector<float>& out);
inline bool MouseHovered(const PVector<int>& mins, const PVector<int>& maxs)
{
	tagPOINT p;
	GetCursorPos(&p);

	return 
			p.x > mins.x && p.x < maxs.x
		&&	p.y > mins.y && p.y < maxs.y;
}

#endif