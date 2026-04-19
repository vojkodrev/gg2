#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <nlohmann/json.hpp>
#include <fstream>

int main()
{
    nlohmann::json atlas = nlohmann::json::parse(std::ifstream("assets/texture.json"));
    auto& grassFrame = atlas["frames"]["grass/000.png"]["frame"];
    SDL_Rect grassRect = { grassFrame["x"], grassFrame["y"], grassFrame["w"], grassFrame["h"] };

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("gg2", 1280, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    SDL_Surface* surface = IMG_Load("assets/texture.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    SDL_FRect dst = { 100, 100, (float)grassRect.w * 5, (float)grassRect.h * 5 };

    bool running = true;
    SDL_Event event;
    int maxFps = 60;
    int frameCount = 0;
    Uint64 lastTicks = SDL_GetTicks();
    while (running)
    {
        Uint64 now = SDL_GetTicks();
        float dt = (now - lastTicks) / 1000.0f;
        lastTicks = now;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, (SDL_FRect*)&grassRect, &dst);
        SDL_RenderPresent(renderer);

        Uint64 frameTime = SDL_GetTicks() - now;
        Uint64 targetTime = 1000 / maxFps;
        if (frameTime < targetTime)
            SDL_Delay(targetTime - frameTime);

        if (++frameCount % 60 == 0)
            SDL_Log("frame: %llu ms", frameTime);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
