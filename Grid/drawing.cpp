#include "pch.h"


//SHAPES////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SHAPES////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SHAPES////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Drawing::DrawArrow(PVector<int> start, PVector<int> end, const Pixel& col, int32_t thickness)
{


	//auto s = TranslateGridToCoordinates(start);
	//auto e = TranslateGridToCoordinates(end);

	PVector<int> vLeft;

	engine->DrawThickLine({ start.x, start.y }, { end.x, end.y }, thickness, { col.r, col.g, col.b, col.a });
	start = end;



	float angle = VectorAngle({ (float)start.x, (float)start.y }, { (float)end.x, (float)end.y });

	float Hp = -angle;

	const float left = Hp - 60;
	const float right = left - 60;



	////right side
	vLeft.x = start.x + sin((right)*PI / 180) * 15;
	vLeft.y = start.y - cos((right)*PI / 180) * 15;

	//left side
	end.x = start.x + sin((left)*PI / 180) * 15;
	end.y = start.y - cos((left)*PI / 180) * 15;

	engine->DrawString({ 100, 0 }, std::format("angle: {}", Hp), olc::BLACK);

	engine->FillTriangle({ start.x, start.y }, { vLeft.x, vLeft.y }, { end.x, end.y }, { col.r, col.g, col.b, col.a });

	//DrawLine({ start.x, start.y }, { end.x, end.y }, { col.r, col.g, col.b, col.a });

}
void Drawing::DrawVectorTriangle(const PVector<int>& s, const PVector<int>& e)
{
	engine->DrawLine({ s.x, s.y }, { e.x, s.y }, olc::RED);
	engine->DrawLine({ s.x, s.y }, { e.x, e.y }, olc::RED);
	engine->DrawLine({ e.x, s.y }, { e.x, e.y }, olc::RED);
}