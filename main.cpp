#include "scene.h"
#include "sphere.h"
#include <cstdint>

using namespace std;

auto get_color_from_rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b) -> std::uint32_t
{
    std::uint32_t color = 0;
    color += r << 24;
    color += g << 16;
    color += b << 8;
    return color;
}

auto main(int argc, char** argv) -> int {
    const int width = 640;
    const int height = 480;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    SDL_RenderSetLogicalSize(renderer, width, height);
    
    scene main_scene = scene();
    
    for(int i = -10; i < 10; i++)
    {
        
        sphere sph = sphere(vec3(i * 3, 0, -10), 2.0f, get_color_from_rgb(100, 100, 100));
        main_scene.spheres.push_back(sph);
    }
    
    vec3 camera = vec3();
    
    bool interrupted = false;
    while(!interrupted)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_WINDOWEVENT)
            {
                switch(event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                    {
                        interrupted = true;
                    } break;
                }
            }
        }
        main_scene.render(renderer, texture, width, height, vec3(0, 0, -25));
        SDL_Delay(1000.0f/60.0f);
    }
    
    return 0;
}