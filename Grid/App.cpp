#include "App.hpp"

App::App()
{
	// Name your application
	sAppName = "Example";
}

bool App::OnUserCreate()
{
	Grid_s grids;
	grids.bShowNumbers = true;
	grids.vNumbers = { 10 };
	grids.vSize = { 900, 900 };
	grids.pos = { 38,38 };
	grid.Create(grids);
	// Called once at the start, so create things here
	return true;
}

bool App::OnUserUpdate(float fElapsedTime)
{
	OnRenderGrid(grid);

	return true;
}


int main()
{
	App demo;
	if (demo.Construct(1000-38, 1000-38, 1, 1, 0, true))
		demo.Start();
	return 0;
}

//GRID////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GRID////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GRID////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Grid::Create(const Grid_s& grid)
{
	if (grid.vSize.x < 0 || grid.vSize.y < 0)
		return false;

	iGridSpacing.x = grid.vSize.x / (grid.vNumbers * 2) - 1;
	iGridSpacing.y = grid.vSize.y / (grid.vNumbers * 2) - 1;


	data = grid;
	return true;
}
void App::RenderNumbers()
{
	int width = ScreenWidth();
	int j = -grid.data.vNumbers;

	Grid_s data = grid.data;

	//horizontal numbers
	for (int i = data.pos.x; i < data.pos.x + data.vSize.x; i += grid.iGridSpacing.x) {
		if(j != 0)
			DrawString({ i - (j < 1 ? 10 : 0), data.vSize.y / 2 + 20 }, std::to_string(j), olc::BLACK);


		j++;
	}

	//vertical numbers
	j = data.vNumbers;
	for (int i = data.pos.y; i < data.pos.y + data.vSize.y; i += grid.iGridSpacing.y) {
		if (j != 0)
			DrawString({ data.vSize.y / 2 + (j < 1 ? 6 : 10) , i }, std::to_string(j), olc::BLACK);
		j--;
	}
}
void App::RenderGrid()
{
	FillRect({ grid.data.pos.x, grid.data.pos.y }, { grid.data.vSize.x, grid.data.vSize.y });

	Grid_s data = grid.data;
	//vertical lines
	for (int x = data.pos.x; x < data.pos.x + data.vSize.x; x += grid.iGridSpacing.x) {
		DrawLine({ x, data.pos.y }, { x, data.vSize.y + data.pos.y / 2}, olc::GREY);
	}
	//horizontal lines
	for (int y = data.pos.y; y < data.pos.y + data.vSize.y; y += grid.iGridSpacing.y) {
		DrawLine({ data.pos.x, y }, { data.pos.x / 2 + data.vSize.x, y }, olc::GREY);
	}

	DrawArrow({ 0,0 }, { 0, 10.5f }, COL::GREY, 1);
	DrawArrow({ 0,0 }, { 0, -10.5f }, COL::GREY, 1);
	DrawArrow({ 0,0 }, { 10.5f, 0 }, COL::GREY, 1);
	DrawArrow({ 0,0 }, { -10.5f, 0 }, COL::GREY, 1);
}
void App::OnRenderGrid(const Grid& grid)
{
	Clear(olc::WHITE);
	RenderGrid();
	RenderNumbers();

	static DWORD ms = timeGetTime();

	static float x1 = rand() % 20, y1 = rand() % 20, x2 = rand() % 20, y2 = rand() % 20;

	if (timeGetTime() > ms + 1000) {
		x1 = random(-10, 10), y1 = random(-10, 10), x2 = random(-10, 10), y2 = random(-10, 10);
		ms = timeGetTime();
	}
//	x1 = 8, y1 = 8, x2 = 7, y2 = 7;
	DrawArrow({x1 , y1}, { x2, y2 }, COL::GREEN, 2);

	

}
PVector<int> App::TranslateGridToCoordinates(PVector<float> gridpos)
{
	//gridpos.clamp(-grid.data.vNumbers, grid.data.vNumbers);

	return { 
		grid.data.pos.x + (grid.data.vSize.x / 2 - 10) + int((gridpos.x * (float)grid.iGridSpacing.x)), 
		grid.data.pos.y + (grid.data.vSize.y / 2 - 10) + int((gridpos.y * (float)-grid.iGridSpacing.y))};
}

//SHAPES////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SHAPES////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SHAPES////////////////////////////////////////////////////////////////////////////////////////////////////////////

void App::DrawArrow( PVector<float> s,  PVector<float> e, const Pixel& col, int32_t thickness)
{


	auto start = TranslateGridToCoordinates(s);
	auto end = TranslateGridToCoordinates(e);

	PVector<int> vLeft;

	DrawThickLine({ start.x, start.y }, { end.x, end.y }, thickness, { col.r, col.g, col.b, col.a });
	start = end;

		

	float angle = VectorAngle(s, e);

	float Hp = -angle;

	const float left = Hp - 60;
	const float right = left - 60;



	////right side
	vLeft.x = start.x + sin((right)*PI / 180) * 15;
	vLeft.y = start.y - cos((right)*PI / 180) * 15;

	//left side
	end.x = start.x + sin((left) * PI / 180) * 15;
	end.y = start.y - cos((left) * PI / 180) * 15;

	DrawString({ 100, 0 }, std::format("angle: {}", Hp), olc::BLACK);

	FillTriangle({ start.x, start.y }, { vLeft.x, vLeft.y }, { end.x, end.y }, { col.r, col.g, col.b, col.a });

	//DrawLine({ start.x, start.y }, { end.x, end.y }, { col.r, col.g, col.b, col.a });

}
void App::DrawVectorTriangle(const PVector<int>& s, const PVector<int>& e)
{
	DrawLine({ s.x, s.y }, { e.x, s.y }, olc::RED);
	DrawLine({ s.x, s.y }, { e.x, e.y }, olc::RED);
	DrawLine({ e.x, s.y }, { e.x, e.y }, olc::RED);


}