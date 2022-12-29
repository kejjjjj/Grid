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

	sShape<float> data{};
	data.mins = { -5, -7 };
	data.maxs = { 5,5 };

	data.hitbox_mins = { data.maxs.x - 0.2f, data.maxs.y + 0.2f };
	data.hitbox_maxs = { data.maxs.x + 0.2f, data.maxs.y - 0.2f };
	data.col = COL::GREEN;

	//arrows
	GridShape shape(&vGrid, eShape::ARROW, data); vGrid.PushShape(shape);
	
	memset(&data, 0, sizeof(sShape<float>));

	data.radius = 3.f;
	data.hitbox_radius = data.radius;
	data.faces = 16;
	data.origin = { 0,0 };
	data.col = COL::RED;
	data.color_fill = true;

	GridShape shape3(&vGrid, eShape::CIRCLE, data);

	vGrid.PushShape(shape3);

	vGrid.Create(grids);
	// Called once at the start, so create things here
	return true;
}

bool App::OnUserUpdate(float fElapsedTime)
{
	vGrid.OnRenderGrid();
	//Clear(olc::WHITE);

	//if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
	//	PVector<float> out;
	//	VectorSimultaneousEquation({ 1, 3 }, { 2, 2 }, { 9,10}, out);

	//}

	return true;
}


int main()
{
	App demo;
	if (demo.Construct(1000-38, 1000-38, 1, 1, 0, true))
		demo.Start();
	return 0;
}


