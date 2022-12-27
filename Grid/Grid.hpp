#pragma once

#ifndef GRID_H
#define GRID_H

#include "pch.h"
#include "olcPixelGameEngine.h"

struct Grid_s
{
	PVector<int> pos = { 0,0 };
	PVector<int> vSize = { 512,512 };
	int32_t vNumbers = { 10 }; //-xy to +xy
	bool bShowNumbers = true;
};

struct Grid
{
	Grid(olc::PixelGameEngine* _engine) : engine(_engine){};
	Grid() : engine(0){};

	bool Initialize(olc::PixelGameEngine* _engine) {
		if (!_engine || engine)
			return false;

		engine = _engine;

		return true;
	}
	bool Create(const Grid_s& grid);
	void OnRender();

	void OnRenderGrid();
	void RenderNumbers();
	void RenderGrid();
	void OnKeyEvent();
	PVector<int> GetMousePos();
	bool OnMouseHovered(PVector<float>& s, PVector<float>& e);

	void PushShape(GridShape shape) { shapes.push_back(shape); }

	PVector<int> TranslateGridToCoordinates(PVector<float> gridpos);
	int32_t TranslateGridToCoordinates(const float gridpos, bool horizontal);
	void DrawArrow(PVector<float> s, PVector<float> e, const Pixel& col = COL::RED, int32_t thickness = 1);
	GridShape* FindShapeFromBounds(const PVector<int>& pos);

	Grid_s data;
private:
	olc::PixelGameEngine* engine;
	PVector<int> iGridSpacing;
	std::vector<GridShape> shapes;

};

#endif