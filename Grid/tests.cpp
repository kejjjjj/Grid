
#include "pch.h"


void Grid::Tests()
{

	//t_LinearAlgebra();
	t_Circles();

}

void Grid::t_LinearAlgebra()
{
	if (shapes.size() < 2)
		return;
	//Linear combinations
	//Convex combinations
	//Simultaneous equations
	
	PVector<float> arrow1 = { shapes[0].d.maxs };
	PVector<float> arrow2 = { shapes[1].d.maxs };



	static float t = 0;
	static bool go_backward = false;

	if (!go_backward && (t += 0.0025f) >= 1)
		go_backward = true;

	else if (go_backward && (t -= 0.0025f) <= 0) {
		go_backward = false;
	}
	const float
		alpha = std::lerp(0, 1, t),
		beta = std::lerp(0, 1, 1.f - t);

	DrawArrow({ 0 , 0 }, { arrow1.x, arrow1.y }, COL::GREEN, 2);
	DrawArrow({ 0 , 0 }, { arrow2.x, arrow2.y }, COL::GREEN, 2);

	auto linearA = PVector<float>{ arrow1.x, arrow1.y };
	auto linearB = PVector<float>{ arrow2.x, arrow2.y };

	//auto result = (linearA * alpha + linearB * beta);

	auto result = VectorLinearCombination(linearA, linearB, 3, 2);

	PVector<float> out;
	engine->SetPixelMode(olc::Pixel::ALPHA);

	if (VectorSimultaneousEquation({ arrow1.x, arrow2.x }, { arrow1.y, arrow2.y }, result, out)) {

		engine->DrawString({ 100, 500 }, std::format("out.x: {}, out.y: {}", out.x, out.y), olc::BLACK);

		PVector<float> _new = arrow1 * out.x;
		auto _new2 = arrow2 * out.y;


		DrawArrow(arrow1, _new, { 0,255,0,150 }, 2);
		DrawArrow(arrow2, _new2, { 0,255,0,150 }, 2);

		DrawArrow(_new2, _new2 + _new, { 0,0,255,150 }, 2);
		DrawArrow(_new, _new2 + _new, { 0,0,255,150 }, 2);

		auto combined = _new2 + _new;

		engine->FillTriangle(
			{ TranslateGridToCoordinates(arrow1.x, true, false), TranslateGridToCoordinates(arrow1.y, false, false) },
			{ TranslateGridToCoordinates(_new.x, true, true), TranslateGridToCoordinates(_new.y, false, true) },
			{ TranslateGridToCoordinates(combined.x, true, true), TranslateGridToCoordinates(combined.y, false, true) }, { 0, 0,255,50 });

		engine->FillTriangle(
			{ TranslateGridToCoordinates(arrow2.x, true, false), TranslateGridToCoordinates(arrow2.y, false, false) },
			{ TranslateGridToCoordinates(_new2.x, true, true), TranslateGridToCoordinates(_new2.y, false, true) },
			{ TranslateGridToCoordinates(combined.x, true, true), TranslateGridToCoordinates(combined.y, false, true) }, { 0, 0,255,50 });

	}

	engine->FillTriangle(
		{ TranslateGridToCoordinates(0, true), TranslateGridToCoordinates(0, false) },
		{ TranslateGridToCoordinates(arrow1.x, true, true), TranslateGridToCoordinates(arrow1.y, false, true) },
		{ TranslateGridToCoordinates(result.x, true, true), TranslateGridToCoordinates(result.y, false, true) }, { 255,0,255,50 });

	engine->FillTriangle(
		{ TranslateGridToCoordinates(0, true), TranslateGridToCoordinates(0, false) },
		{ TranslateGridToCoordinates(arrow2.x, true, true), TranslateGridToCoordinates(arrow2.y, false, true) },
		{ TranslateGridToCoordinates(result.x, true, true), TranslateGridToCoordinates(result.y, false, true) }, { 255,0,255,50 });




	engine->SetPixelMode(olc::Pixel::NORMAL);

	DrawArrow({ 0,0 }, result, COL::RED, 2);

	const auto pos = TranslateCoordinatesToGrid(GetMousePos());

	engine->DrawString({ 100, 300 }, std::format("{:.1f},{:.1f}", pos.x, pos.y), olc::BLACK);
}
void Grid::t_Circles()
{

	//if (shapes.empty())
	//	return;

	shapes[0].DrawShape();
	shapes[1].DrawShape();


}