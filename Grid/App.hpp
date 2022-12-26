#pragma once

#ifndef APP_H
#define APP_H

#include "App.hpp"
#include "pch.h"
#ifndef OLC_PGE_APPLICATION
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#endif


struct Grid_s
{
	PVector<int> pos = { 0,0 };
	PVector<int> vSize = { 512,512 };
	int32_t vNumbers = { 10 }; //-xy to +xy
	bool bShowNumbers = true;
};

struct Grid
{
	bool Create(const Grid_s& grid);
	void OnRender();
	Grid_s data;

	PVector<int> iGridSpacing;
	int32_t iThickness;

};

class App : public olc::PixelGameEngine
{
public:
	App();

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	void OnRenderGrid(const Grid& grid);
	void RenderNumbers();
	void RenderGrid();
	void DrawArrow( PVector<float> s,  PVector<float> e, const Pixel& col = COL::RED, int32_t thickness = 1);
	void DrawVectorTriangle(const PVector<int>& s, const PVector<int>& e);

	PVector<int> TranslateGridToCoordinates(PVector<float> gridpos);
	Grid vGrid;

};

inline Grid grid;

#endif