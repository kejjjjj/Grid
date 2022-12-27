#pragma once

#ifndef __shapes
#define __shapes

#include "pch.h"
#include "olcPixelGameEngine.h"

enum class eShape : char
{
	INVALID,
	ARROW
};
class Shape
{
public:
	Shape(const PVector<int>& s, const PVector<int>& e, const eShape _shape, const Pixel& _color = COL::WHITE, const int32_t _thickness = 1) 
		: shape(_shape), mins(s), maxs(e), color(_color), thickness(_thickness) {};
	
	bool SetHitboxes(const PVector<int>& s, const PVector<int>& e);

	void DrawShape();

	
	PVector<int> mins, maxs; //for drawing
	PVector<int> hitbox_mins, hitbox_maxs; //for key events

	eShape shape = eShape::INVALID;

	Pixel color = COL::WHITE;
private:
	int32_t thickness = 1;
};

class GridShape
{
public:
	GridShape(struct Grid* grid, const PVector<float>& s, const PVector<float>& e, const eShape _shape, const Pixel& _color = COL::WHITE, const int32_t _thickness = 1)
		: vGrid(grid), shape(_shape), mins(s), maxs(e), color(_color), thickness(_thickness) {};

	bool SetHitboxes(const PVector<float>& s, const PVector<float>& e);

	void DrawShape();
	

	PVector<float> mins, maxs; //for drawing
	PVector<float> hitbox_mins, hitbox_maxs; //for key events

	eShape shape = eShape::INVALID;
	Pixel color = COL::WHITE;
private:
	int32_t thickness = 1;
	struct Grid* vGrid = 0;
};

#endif