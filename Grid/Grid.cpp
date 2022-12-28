#include "pch.h"

void Grid::OnRender()
{

}

bool Grid::Create(const Grid_s& grid)
{
	if (grid.vSize.x < 0 || grid.vSize.y < 0)
		return false;

	iGridSpacing.x = grid.vSize.x / (grid.vNumbers * 2) - 1;
	iGridSpacing.y = grid.vSize.y / (grid.vNumbers * 2) - 1;


	data = grid;
	return true;
}
PVector<float> Grid::TranslateCoordinatesToGrid(const PVector<int>& c)
{
	const auto corner = data.pos + 20 + data.vSize;
	PVector<float> center = { (float)corner.x, (float)corner.y }; center /= 2;

	PVector<float> coordinates = { (float)c.x, (float)c.y };

	coordinates.x = std::clamp(c.x, data.pos.x, corner.x);
	coordinates.y = std::clamp(c.y, data.pos.y, corner.y);


	coordinates.x = (coordinates.x - center.x) / iGridSpacing.x;
	coordinates.y = (coordinates.y - center.y) / iGridSpacing.y;

	coordinates.y *= -1;
	coordinates.clamp(-(float)data.vNumbers, (float)data.vNumbers);
	return{
		coordinates
	};
}
PVector<int> Grid::TranslateGridToCoordinates(PVector<float>& gridpos, const bool clamp)
{
	if(clamp)
		gridpos.clamp(-data.vNumbers, data.vNumbers);

	return {
		data.pos.x + (data.vSize.x / 2 - 10) + int((gridpos.x * (float)iGridSpacing.x)),
		data.pos.y + (data.vSize.y / 2 - 10) + int((gridpos.y * (float)-iGridSpacing.y)) };
}
PVector<int> Grid::GridToCoord(PVector<float>& gridpos, const bool clamp)
{
	if (clamp)
		gridpos.clamp(-data.vNumbers, data.vNumbers);

	return{ 
		int((gridpos.x * (float)iGridSpacing.x)), 
		int((gridpos.y * (float)-iGridSpacing.y)) };
}
int32_t Grid::GridToCoord(const float gridpos, bool horizontal, const bool clamp)
{
	if (horizontal)
		return int((gridpos * (float)iGridSpacing.x));

	return int((gridpos * (float)iGridSpacing.y));

}
int32_t Grid::TranslateGridToCoordinates(const float gridpos, bool horizontal)
{
	if (horizontal) {
		return data.pos.x + (data.vSize.x / 2 - 10) + int((gridpos * (float)iGridSpacing.x));

	}
	return data.pos.y + (data.vSize.y / 2 - 10) + int((gridpos * (float)-iGridSpacing.y));
}
int32_t Grid::TranslateGridToCoordinates(float& gridpos, bool horizontal, const bool clamp)
{
	if (clamp)
		gridpos = std::clamp(gridpos, -(float)data.vNumbers, (float)data.vNumbers);
	if (horizontal) {
		return data.pos.x + (data.vSize.x / 2 - 10) + int((gridpos * (float)iGridSpacing.x));

	}
	return data.pos.y + (data.vSize.y / 2 - 10) + int((gridpos * (float)-iGridSpacing.y));
}

void Grid::RenderNumbers()
{
	int width = engine->ScreenWidth();
	int j = -data.vNumbers;

	//horizontal numbers
	for (int i = data.pos.x; i < data.pos.x + data.vSize.x; i += iGridSpacing.x) {
		if (j != 0)
			engine->DrawString({ i - (j < 1 ? 10 : 0), data.vSize.y / 2 + 20 }, std::to_string(j), olc::BLACK);
		j++;
	}

	//vertical numbers
	j = data.vNumbers;
	for (int i = data.pos.y; i < data.pos.y + data.vSize.y; i += iGridSpacing.y) {
		if (j != 0)
			engine->DrawString({ data.vSize.y / 2 + (j < 1 ? 6 : 10) , i }, std::to_string(j), olc::BLACK);
		j--;
	}
}
void Grid::RenderGrid()
{
	engine->FillRect({ data.pos.x, data.pos.y }, { data.vSize.x, data.vSize.y });

	//vertical lines
	for (int x = data.pos.x; x < data.pos.x + data.vSize.x; x += iGridSpacing.x) {
		engine->DrawLine({ x, data.pos.y }, { x, data.vSize.y + data.pos.y / 2 }, olc::GREY);
	}
	//horizontal lines
	for (int y = data.pos.y; y < data.pos.y + data.vSize.y; y += iGridSpacing.y) {
		engine->DrawLine({ data.pos.x, y }, { data.pos.x / 2 + data.vSize.x, y }, olc::GREY);
	}

	DrawArrow({ 0,0 }, { 0, 10.5f }, COL::GREY, 1);
	DrawArrow({ 0,0 }, { 0, -10.5f }, COL::GREY, 1);
	DrawArrow({ 0,0 }, { 10.5f, 0 }, COL::GREY, 1);
	DrawArrow({ 0,0 }, { -10.5f, 0 }, COL::GREY, 1);
}
void Grid::OnKeyEvent()
{
	static bool clicked = false;
	static GridShape* shape = 0;
	static PVector<float> ClickPos;
	if (engine->GetMouse(olc::Mouse::LEFT).bPressed) {

		shape = FindShapeFromBounds(GetMousePos());
		if (shape) {
			ClickPos = TranslateCoordinatesToGrid(GetMousePos());
			clicked = true;
		}
	}
	else if (!engine->GetMouse(olc::Mouse::LEFT).bHeld) {
		clicked = false;
		shape = 0;
	}
	
	if (shape && engine->GetMouse(olc::Mouse::LEFT).bHeld) {

		auto difference = TranslateCoordinatesToGrid(GetMousePos()) - ClickPos;

		if (shape->OnDeltaMove(difference)) {
			ClickPos = TranslateCoordinatesToGrid(GetMousePos());
		}

		engine->DrawString({ 400, 10 }, std::format("delta: {:.1f}, {:.1f}", difference.x, difference.y), olc::BLACK);

	}

	//if (OnMouseHovered(shapes[0].hitbox_mins, shapes[0].hitbox_maxs)) {
	//	engine->DrawString({ 400, 10 }, "hello!", olc::BLACK);

	//}

	//auto pos = GetMousePos();

	//engine->FillCircle({ pos.x, pos.y }, 20, olc::RED);

}
PVector<int> Grid::GetMousePos()
{
	tagPOINT p;
	GetCursorPos(&p);

	p.x -= data.pos.x;
	p.y -= data.pos.y + 25;

	return {p.x, p.y};
}
void Grid::OnRenderGrid()
{
	engine->Clear(olc::WHITE);
	RenderGrid();
	RenderNumbers();
	OnKeyEvent();

	//for (auto& i : shapes) {
	//	auto hitbox = i.GetHitboxOrigin();
	//	auto org = TranslateGridToCoordinates(hitbox);
	//	engine->DrawCircle({ org.x, org.y }, 10, olc::RED);
	//}

	Tests();
}

bool Grid::OnMouseHovered(PVector<float>& s, PVector<float>& e)
{
	auto start = TranslateGridToCoordinates(s);
	auto end = TranslateGridToCoordinates(e);

	auto p = GetMousePos();

	return
		p.x > start.x && p.x < end.x
		&& p.y > start.y && p.y < end.y;
}

void Grid::DrawArrow(PVector<float> s, PVector<float> e, const Pixel& col, int32_t thickness)
{
	

	auto start = TranslateGridToCoordinates(s, true);
	auto end = TranslateGridToCoordinates(e, true);

	PVector<int> vLeft;

	engine->DrawThickLine({ start.x, start.y }, { end.x, end.y }, thickness, { col.r, col.g, col.b, col.a });
	start = end;



	float angle = VectorAngle(s, e);

	float Hp = -angle;

	const float left = Hp - 60;
	const float right = left - 60;



	//right side
	vLeft.x = start.x + sin((right)* PI / 180) * 15;
	vLeft.y = start.y - cos((right)* PI / 180) * 15;

	//left side
	end.x = start.x + sin((left)* PI / 180) * 15;
	end.y = start.y - cos((left)* PI / 180) * 15;

	//engine->DrawString({ 100, 0 }, std::format("angle: {}", Hp), olc::BLACK);

	engine->FillTriangle({ start.x, start.y }, { vLeft.x, vLeft.y }, { end.x, end.y }, { col.r, col.g, col.b, col.a });

	//DrawLine({ start.x, start.y }, { end.x, end.y }, { col.r, col.g, col.b, col.a });

}