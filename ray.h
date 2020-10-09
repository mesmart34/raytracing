#pragma once


#include "glm/glm.hpp"
#include "glm/vec2.hpp"
#include <cstdlib>
#include "SDL2\SDL.h"
#include <vector>
#include <cmath>
#include <cstdint>
#include <cfloat>
#include <iostream>

using namespace std;
using namespace glm;

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


struct material
{
    u32 color;
};

struct sphere
{
    sphere() = default;
    vec3 pos;
    f32 r;
    material mat;
};

struct scene
{
    vector<sphere> spheres;
    vec3 camera_pos;
};

void init();

void render(const scene& scn);