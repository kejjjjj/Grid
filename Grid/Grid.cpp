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

PVector<int> Grid::TranslateGridToCoordinates(PVector<float> gridpos)
{
	//gridpos.clamp(-grid.data.vNumbers, grid.data.vNumbers);

	return {
		data.pos.x + (data.vSize.x / 2 - 10) + int((gridpos.x * (float)iGridSpacing.x)),
		data.pos.y + (data.vSize.y / 2 - 10) + int((gridpos.y * (float)-iGridSpacing.y)) };
}
int32_t Grid::TranslateGridToCoordinates(const float gridpos, bool horizontal)
{
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

	if (engine->GetMouse(olc::Mouse::LEFT).bPressed) {

		GridShape* shape = FindShapeFromBounds(GetMousePos());
		if (shape) {
			clicked = true;
		}
	}
	else if(!engine->GetMouse(olc::Mouse::LEFT).bHeld)
		clicked = false;
	
	if (clicked && engine->GetMouse(olc::Mouse::LEFT).bHeld) {

		engine->DrawString({ 400, 10 }, "hello!", olc::BLACK);

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

	PVector<float> arrow1 = { shapes[0].maxs};
	PVector<float> arrow2 = { shapes[1].maxs};



	DrawArrow({ 0 , 0 }, { arrow1 }, COL::GREEN, 2);
	DrawArrow({ 0 , 0 }, { arrow2}, COL::GREEN, 2);


	auto linearA = PVector<float>{ arrow1 } / 2;
	auto linearB = PVector<float>{ arrow2 } / 2;

	auto result = linearA + linearB;

	engine->SetPixelMode(olc::Pixel::ALPHA);
	engine->FillTriangle(
		{ TranslateGridToCoordinates(0, true), TranslateGridToCoordinates(0, false) },
		{ TranslateGridToCoordinates(arrow1.x, true), TranslateGridToCoordinates(arrow1.y, false) },
		{ TranslateGridToCoordinates(result.x, true), TranslateGridToCoordinates(result.y, false) }, { 255,0,255,50 });

	engine->FillTriangle(
		{ TranslateGridToCoordinates(0, true), TranslateGridToCoordinates(0, false) },
		{ TranslateGridToCoordinates(arrow2.x, true), TranslateGridToCoordinates(arrow2.y, false) },
		{ TranslateGridToCoordinates(result.x, true), TranslateGridToCoordinates(result.y, false) }, { 255,0,255,50 });
	engine->SetPixelMode(olc::Pixel::NORMAL);

	DrawArrow({ 0,0 }, result, COL::RED, 2);

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


	auto start = TranslateGridToCoordinates(s);
	auto end = TranslateGridToCoordinates(e);

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