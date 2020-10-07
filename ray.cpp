#include "ray.h",


using namespace std;

global SDL_Window* window;
global SDL_Renderer* renderer;
global SDL_Texture* screen_texture;

const global int width = 800;
const global int height = 600;
const global int fov = 90;

void init();
void render(const scene& scn);
internal u32 cast_ray(const scene& scn, v3 pos, v3 dir);
internal v3 vec3_norm(const v3& v);
internal bool sphere_intersect(const sphere& sph, const v3& start, const v3& dir);

void
init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    SDL_RenderSetLogicalSize(renderer, width, height);
}

void 
render(const scene& scn)
{
    u32 data[width * height] = {};
    
    
    
    for(u32 x = 0; x < width; x++)
    {
        for(u32 y = 0; y < height; y++)
        {
            
            float dir_x = (x + 0.5) - width / 2;
            float dir_y = -(y + 0.5) + height / 2;
            float dir_z = -height / (2.0f * tanf(fov / 2));
            
            v3 pos = scn.camera_pos;
            v3 dir = vec3_norm(v3{dir_x, dir_y, dir_z});
            
            u32 color = cast_ray(scn, pos, dir);
            
            data[x + y * width] = color;
        }
    }
    
    
    SDL_UpdateTexture(screen_texture, NULL, &data[0], sizeof(u32) * width);
    SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

internal v3
vec3_norm(const v3& v)
{
    auto l = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return v3{v.x / l, v.y / l, v.z / l};
}

internal float
vec3_mult(const v3& a, const v3& b)
{
    float res = a.x * b.x + a.y * b.y + a.z * b.z;
    return res;
}

internal bool
sphere_intersect(const sphere& sph, const v3& start, const v3& dir)
{
    v3 L = {
        sph.pos.x - start.x, sph.pos.y - start.y
    };
    f32 tca = vec3_mult(L, dir);
    f32 m1 = vec3_mult(L, L);
    f32 m2 = tca * tca;
    f32 d2 = m1 - m2;
    if (d2 > sph.r * sph.r)
        return false;
    f32 thc = sqrtf(sph.r * sph.r - d2);
    f32 t0       = tca - thc;
    f32 t1 = tca + thc;
    if (t0 < 0) t0 = t1;
    if (t0 < 0)
        return false;
    return true;
}

internal u32 
cast_ray(const scene& scn, v3 pos, v3 dir)
{
    const f32 max = FLT_MAX;
    u32 color = 0x252525;
    f32 hit_distance = max;
    for(u32 i = 0; i < scn.spheres.size(); i++)
    {
        sphere sph = scn.spheres[i];
        if(sphere_intersect(sph, pos, dir))
        {
            color = sph.mat.color;
        }
    }
    
    return color;
}