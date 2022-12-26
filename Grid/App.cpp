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
	grids.vNumbers = { 10, 10 };
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Grid::Create(const Grid_s& grid)
{
	if (grid.vSize.x < 0 || grid.vSize.y < 0)
		return false;

	iGridSpacing.x = grid.vSize.x / (grid.vNumbers.x * 2) - 1;
	iGridSpacing.y = grid.vSize.y / (grid.vNumbers.y * 2) - 1;


	data = grid;
	return true;
}
void App::RenderNumbers()
{
	int width = ScreenWidth();
	int j = -grid.data.vNumbers.x;

	Grid_s data = grid.data;

	//horizontal numbers
	for (int i = data.pos.x; i < data.pos.x + data.vSize.x; i += grid.iGridSpacing.x) {
		if(j != 0)
			DrawString({ i - (j < 1 ? 10 : 0), data.vSize.y / 2 + 20 }, std::to_string(j), olc::BLACK);


		j++;
	}

	//vertical numbers
	j = data.vNumbers.y;
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
}
void App::OnRenderGrid(const Grid& grid)
{
	Clear(olc::WHITE);
	RenderGrid();
	RenderNumbers();
}