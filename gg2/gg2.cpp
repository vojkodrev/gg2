#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

struct TileMap
{
    int srcTileW, srcTileH;
    int columns;
    int mapW;
    int dstTileW, dstTileH;
    uint32_t firstGid;
    int tileCount;
    uint32_t tiles[1000];
};

TileMap loadTileMap(const tmx::Map &map)
{
    auto &tileset = map.getTilesets()[0];
    auto &tileLayer = map.getLayers()[0]->getLayerAs<tmx::TileLayer>();
    TileMap tm;
    auto &srcTiles = tileLayer.getTiles();
    tm.tileCount = (int)srcTiles.size();
    for (int i = 0; i < tm.tileCount; i++)
        tm.tiles[i] = srcTiles[i].ID;
    tm.srcTileW = tileset.getTileSize().x;
    tm.srcTileH = tileset.getTileSize().y;
    tm.columns = tileset.getColumnCount();
    tm.mapW = map.getTileCount().x;
    tm.dstTileW = map.getTileSize().x;
    tm.dstTileH = map.getTileSize().y;
    tm.firstGid = tileset.getFirstGID();
    return tm;
}

void RenderSystem(SDL_Renderer *renderer, SDL_Texture *texture, const TileMap &tileMap)
{
    SDL_RenderClear(renderer);
    for (int i = 0; i < tileMap.tileCount; i++)
    {
        uint32_t gid = tileMap.tiles[i];
        if (gid == 0)
            continue;
        int idx = gid - tileMap.firstGid;
        SDL_FRect src = {(float)(idx % tileMap.columns * tileMap.srcTileW), (float)(idx / tileMap.columns * tileMap.srcTileH), (float)tileMap.srcTileW, (float)tileMap.srcTileH};
        SDL_FRect dst = {(float)(i % tileMap.mapW * tileMap.dstTileW), (float)(i / tileMap.mapW * tileMap.dstTileH), (float)tileMap.dstTileW, (float)tileMap.dstTileH};
        SDL_RenderTexture(renderer, texture, &src, &dst);
    }
    SDL_RenderPresent(renderer);
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("gg2", 1280, 720, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);

    SDL_Surface *surface = IMG_Load("assets/texture/texture.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(surface);

    tmx::Map map;
    map.load("assets/map/map1.tmx");

    TileMap tileMap = loadTileMap(map);

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

        RenderSystem(renderer, texture, tileMap);

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
