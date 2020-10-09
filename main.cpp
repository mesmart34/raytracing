#include <cstdlib>
#include <vector>
#include "ray.h"

using namespace std;

auto main(int argc, char** argv) -> int {
    init();
    
    scene scn;
    
    
    
    //scn.spheres.push_back(sphere{v3{0, 0, 0}, 0.1});
    scn.camera_pos = { -3, -4, 10};
    material mat = {0xF80255FF};
    scn.spheres.push_back({{-3,    0,   -16}, 2, mat});
    scn.spheres.push_back({{-1,  -1.5,   -12}, 3, mat});
    scn.spheres.push_back({{7,    5,   -18}, 4, mat});
    //scn.spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2,      glass));
    //scn.spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, red_rubber));
    //scn.spheres.push_back(Sphere(Vec3f( 7,    5,   -18), 4,     mirror));
    
    bool interrupted = false;
    while(!interrupted)
    {
        render(scn);
        scn.camera_pos.z -= 0.1f;
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
        SDL_Delay(1000.0f/60.0f);
    }
    
    return 0;
}