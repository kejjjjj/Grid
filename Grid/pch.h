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

#define DEG2RAD(x) x * PI / 180
#define RAD2DEG(x) x * 180.f / PI

#define SIN(x) (sin(DEG2RAD((x))))
#define COS(x) (cos(DEG2RAD((x))))
#define TAN(x) (tan(DEG2RAD(x)))



#include <Windows.h>
#include <math.h>
#include <timeapi.h>
#include <chrono>
#include <functional>
#include <random>
#include <ranges>

#include "typedefs.hpp"
#include "shapes.hpp"
#include "Grid.hpp"
#include "App.hpp"
#include "drawing.hpp"
#include "abra.hpp"
#include "qmath.hpp"
#endif