#pragma once

#ifndef __shapes
#define __shapes

#include "pch.h"
#include "olcPixelGameEngine.h"

enum class eShape : char
{
	INVALID,
	CIRCLE,
	ARROW
};
template <typename T>
struct sShape
{
	//arrows
	int32_t thickness = 1;

	//circle
	float radius = 1; //circle - radius
	int32_t faces = -1; //circle - how many polygons
	PVector<T> origin; //circle - location
	float hitbox_radius; //circle -

	//rectangles
	PVector<T> mins, maxs; //rectangles - for drawing
	PVector<T> hitbox_mins, hitbox_maxs; //rectangles - for key events

	//general
	Pixel col;
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
	GridShape(struct Grid* grid, const eShape _shape, const sShape<float> data)
		: vGrid(grid), shape(_shape), d(data) {};

	//bool SetHitboxes(const PVector<float>& s, const PVector<float>& e);

	void DrawShape();
	bool OnDeltaMove(const PVector<float>& delta);
	void OnPositionChanged(const PVector<float>& new_pos);
	PVector<float> GetHitboxOrigin() const;

	eShape shape = eShape::INVALID;
	sShape<float> d;

private:
	void DrawCircle();

	int32_t thickness = 2;
	struct Grid* vGrid = 0;
};

#endif