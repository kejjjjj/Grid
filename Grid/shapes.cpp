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
		//return drawing.DrawArrow(mins, maxs, color, thickness);
		break;
	default:
		return;
	}

	return;
}

//bool GridShape::SetHitboxes(const PVector<float>& s, const PVector<float>& e)
//{
//	int min = -vGrid->data.vNumbers;
//	int max = -min;
//
//
//	hitbox_mins = s;
//	hitbox_maxs = e;
//
//	return true;
//}

void GridShape::DrawShape()
{
	switch (shape) {
	case eShape::ARROW:
		return vGrid->DrawArrow(d.mins, d.maxs, d.col, thickness);
	case eShape::CIRCLE:
		return this->DrawCircle();
	default:
		return;
	}

	return;
}
bool GridShape::OnDeltaMove(const PVector<float>& delta)
{
	if (delta == PVector<float>{0, 0})
		return false;

	switch (shape) {
	case eShape::ARROW:
		d.mins += delta;
		d.maxs += delta;
		d.hitbox_maxs += delta;
		d.hitbox_mins += delta;
		break;

	case eShape::CIRCLE:
		d.origin += delta;

		//std::cout << std::format("\nd.origin({:.1f},{:.1f})\nradius_hitbox ({:.1f})\n", d.origin.x, d.origin.y, d.hitbox_radius);

		break;
	}

	return true;
}
void GridShape::OnPositionChanged(const PVector<float>& new_pos)
{
}
PVector<float> GridShape::GetHitboxOrigin() const
{
	switch (shape) {
	case eShape::ARROW:
		return { d.hitbox_mins + ((d.hitbox_maxs - d.hitbox_mins) / 2) };
	case eShape::CIRCLE:
		return d.origin;
	}
}
GridShape* Grid::FindShapeFromBounds(const PVector<int>& pos)
{
	if (shapes.empty())
		return nullptr;

	PVector<int> s, e;
	for (auto& i : shapes) {

		
		switch (i.shape) {
		case eShape::ARROW:
			s = TranslateGridToCoordinates(i.d.hitbox_mins);
			e = TranslateGridToCoordinates(i.d.hitbox_maxs);

			if (e.x > pos.x && s.x < pos.x && e.y > pos.y && s.y < pos.y)
				return &i;

			break;

		case eShape::CIRCLE:

			const auto center = TranslateGridToCoordinates(i.d.origin);
			const auto sub = pos - center;
			
			int32_t radius = GridToCoord(i.d.hitbox_radius, true, true);

			if ((sub.x * sub.x + sub.y * sub.y) < ( radius * radius))
				return &i;

			break;
		//default:
		//	break;
			//MessageBoxA(0, "Grid::FindShapeFromBounds(): unsupported shape\n", "Error", MB_ICONEXCLAMATION);
			//exit(-1);
		}


	}
	return 0;
}


void GridShape::DrawCircle()
{
	const float angleIncr = 360.f / d.faces;

	PVector<int> c, n, org;
	org = vGrid->TranslateGridToCoordinates(d.origin, true);

	const auto amount = vGrid->GridToCoord(d.hitbox_radius, true, true);


	for (int i = 0.f; i < 360; i += angleIncr) {

		if (i >= 360)
			break;

		c.x = org.x + (SIN(i) * amount);
		c.y = org.y - (COS(i) * amount);

		n.x = org.x + (SIN(i + angleIncr) * amount);
		n.y = org.y - (COS(i + angleIncr) * amount);

		// A STAR
		//n.x = org.x + (SIN(i + 135) * amount);
		//n.y = org.y - (COS(i + 135) * amount);

		vGrid->engine->DrawLine({ c.x, c.y }, { n.x, n.y }, { d.col.r, d.col.g, d.col.b, d.col.a });
	}
	
	vGrid->engine->DrawString({ 100, 600 }, std::format("{},{}", org.x, org.y), olc::BLACK);



}