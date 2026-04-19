#include <SDL3/SDL.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("gg2", 1280, 720, 0);

    bool running = true;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
