#include "ray.h"



global SDL_Window* window;
global SDL_Renderer* renderer;
global SDL_Texture* screen_texture;

const global int width = 640;
const global int height = 480;
const global int fov = 90;

void init();
void render(const scene& scn);
internal u32 cast_ray(const scene& scn, vec3 pos, vec3 dir);
internal vec3 vec3_norm(const vec3& v);
internal bool sphere_intersect(const sphere& sph, const vec3& start, const vec3& dir);

void
init()
{
    
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
            
            vec3 pos = scn.camera_pos;
            
            vec3 dir = normalize(vec3(dir_x, dir_y, dir_z));
            
            u32 color = cast_ray(scn, pos, dir);
            
            data[x + y * width] = color;
        }
    }
    
    
    SDL_UpdateTexture(screen_texture, NULL, &data[0], sizeof(u32) * width);
    SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}


#if 1 

internal bool
sphere_intersect(const sphere& sph, const vec3& start, const vec3& dir, float& hit_distance)
{
    vec3 o = sph.pos;
    vec3 d = dir;
    vec3 oc = o - start;
    float b = 2 * dot(oc, d);
    float c = dot(oc, oc) - sph.r;
    float disc = b*b - 4*c;
    if(disc < 0) return false;
    else {
        disc = sqrt(disc);
        hit_distance = disc;
        float t0 = -b - disc;
        float t1 = -b + disc;
        float t = (t0 < t1) ? t0 : t1;
        return true;
    }
}

#else

internal bool
sphere_intersect(const sphere& sph, const vec3& start, const vec3& dir, float& hit_distance)
{
    vec3 L = sph.pos - start;
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

#endif
internal float 
distance(const vec3& a, const vec3& b)
{
    return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

internal u32 
cast_ray(vec3 pos, vec3 dir)
{
    u32 color = 0x252525;
    f32 hit_distance = FLT_MAX;
    for(u32 i = 0; i < scn.spheres.size(); i++)
    {
        sphere sph = scn.spheres[i];
        if(sphere_intersect(sph, pos, dir, hit_distance))
        {
            color = sph.mat.color;
        }
    }
    
    return color;
}