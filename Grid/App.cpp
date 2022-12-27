#include "App.hpp"

App::App()
{
	// Name your application
	sAppName = "Example";
}

bool App::OnUserCreate()
{
	if (!vGrid.Initialize(GetPointerToClass()) || !drawing.Initialize(GetPointerToClass())) {
		std::cout << "nope\n";
		return false;
	}

	Grid_s grids;
	grids.bShowNumbers = true;
	grids.vNumbers = { 10 };
	grids.vSize = { 900, 900 };
	grids.pos = { 38,38 };

	GridShape shape(&vGrid, { -5,7 }, { 5,5 }, eShape::ARROW, COL::BLACK, 1);
	GridShape shape2(&vGrid, { 5,-5 }, { -3,10 }, eShape::ARROW, COL::BLACK, 1);

	shape.SetHitboxes({ shape.maxs.x - 0.2f, shape.maxs.y + 0.2f }, {shape.maxs.x + 0.2f, shape.maxs.y - 0.2f });
	shape2.SetHitboxes({ shape2.maxs.x - 0.2f, shape2.maxs.y + 0.2f }, { shape2.maxs.x + 0.2f, shape2.maxs.y - 0.2f });


	vGrid.PushShape(shape);
	vGrid.PushShape(shape2);


	vGrid.Create(grids);
	// Called once at the start, so create things here
	return true;
}

bool App::OnUserUpdate(float fElapsedTime)
{
	vGrid.OnRenderGrid();
	//Clear(olc::WHITE);

	return true;
}


int main()
{
	App demo;
	if (demo.Construct(1000-38, 1000-38, 1, 1, 0, true))
		demo.Start();
	return 0;
}


