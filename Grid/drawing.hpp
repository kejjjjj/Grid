#pragma once

#ifndef _drawing
#define _drawing

#include "pch.h"
#include "olcPixelGameEngine.h"

class Drawing
{
public:
	
	Drawing(olc::PixelGameEngine* _engine) : engine(_engine) {}
	Drawing() : engine(0){}

	bool Initialize(olc::PixelGameEngine* _engine) {
		if (!_engine || engine)
			return false;

		engine = _engine;

		return true;
	}

	void DrawArrow(PVector<int> s, PVector<int> e, const Pixel& col = COL::RED, int32_t thickness = 1);
	void DrawVectorTriangle(const PVector<int>& s, const PVector<int>& e);

private:
	olc::PixelGameEngine* engine = nullptr;

};

inline Drawing drawing;

#endif