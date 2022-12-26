#pragma once

#ifndef PCH_H
#define PCH_H

#define NOMINMAX

#ifdef _WIN64
typedef unsigned long long UPTR;
#else
typedef unsigned long UPTR;
#endif

#include <Windows.h>
#include <math.h>
#include <timeapi.h>
#include <chrono>
#include <functional>


#include "typedefs.hpp"

#endif