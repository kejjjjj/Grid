#include "pch.h"


bool Shape::SetHitboxes(const PVector<int>& s, const PVector<int>& e)
{
	if (s.x < 0 || s.y < 0 || e.x <= s.x || e.y <= s.y) {
		return false;
	}

	hitbox_mins = s;
	hitbox_maxs = e;

	return true;
}

void Shape::DrawShape()
{
	switch (shape) {
	case eShape::ARROW:
		return drawing.DrawArrow(mins, maxs, color, thickness);

	default:
		return;
	}

	return;
}

bool GridShape::SetHitboxes(const PVector<float>& s, const PVector<float>& e)
{
	int min = -vGrid->data.vNumbers;
	int max = -min;
	//if (s.x < min || s.y < min || 
	//	s.x > max || s.y > max) {
	//	return false;
	//}


	hitbox_mins = s;
	hitbox_maxs = e;

	return true;
}

void GridShape::DrawShape()
{
	switch (shape) {
	case eShape::ARROW:
		return vGrid->DrawArrow(mins, maxs, color, thickness);

	default:
		return;
	}

	return;
}

GridShape* Grid::FindShapeFromBounds(const PVector<int>& pos)
{
	if (shapes.empty())
		return nullptr;

	for (auto& i : shapes) {

		auto s = TranslateGridToCoordinates(i.hitbox_mins);
		auto e = TranslateGridToCoordinates(i.hitbox_maxs);


		if (	e.x > pos.x && s.x < pos.x 
			&&	e.y > pos.y && s.y < pos.y)
			return &i;

	}
	return 0;
}