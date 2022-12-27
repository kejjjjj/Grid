#pragma once

#ifndef APP_H
#define APP_H

#include "App.hpp"
#include "pch.h"
#ifndef OLC_PGE_APPLICATION
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#endif



class App : public olc::PixelGameEngine
{
public:
	App();

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	Grid vGrid;

};

#endif