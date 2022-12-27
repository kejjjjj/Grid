#pragma once

#ifndef PCH_H
#define PCH_H

#define NOMINMAX

#ifdef _WIN64
typedef unsigned long long UPTR;
#else
typedef unsigned long UPTR;
#endif

#define PI 3.1415926535

#include <Windows.h>
#include <math.h>
#include <timeapi.h>
#include <chrono>
#include <functional>
#include <random>

#include "typedefs.hpp"
#include "shapes.hpp"
#include "Grid.hpp"
#include "App.hpp"
#include "drawing.hpp"
#include "abra.hpp"
#include "qmath.hpp"
#endif