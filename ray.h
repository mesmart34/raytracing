#pragma once

#include <cstdlib>
#include "SDL2\SDL.h"
#include <vector>
#include <cmath>
#include <cstdint>
#include <cfloat>
#include <iostream>

using namespace std;

#define internal static
#define global static

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef float f32;
typedef double f64;
#define internal static
#define global static

struct v3
{
    f32 x, y, z;
};

struct material
{
    u32 color;
};

struct sphere
{
    sphere() = default;
    v3 pos;
    f32 r;
    material mat;
};

struct scene
{
    vector<sphere> spheres;
    v3 camera_pos;
};

void init();

void render(const scene& scn);