#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

struct TileMapProperties
{
    int srcTileW, srcTileH;
    int columns;
    int mapW;
    int dstTileW, dstTileH;
    uint32_t firstGid;
};

const int MAX_TILES = 1000;

struct Tile
{
    uint32_t srcX[MAX_TILES];
    uint32_t srcY[MAX_TILES];
    uint32_t dstX[MAX_TILES];
    uint32_t dstY[MAX_TILES];
};

struct TileMap
{
    int tileCount;
    Tile tiles;
};

struct Data
{
    TileMapProperties tileMapProps;
    TileMap tileMap;
};

struct FrameState
{
    int maxFps;
    int frameCount;
    Uint64 lastTicks;
    Uint64 now;
    float dt;
    Uint64 frameTime;
    Uint64 targetTime;
};

struct Context
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    FrameState frame;
    Data data;
};

void loadTileMap(Context &ctx, const tmx::Map &map)
{
    auto &tileset = map.getTilesets()[0];
    auto &tileLayer = map.getLayers()[0]->getLayerAs<tmx::TileLayer>();
    auto &srcTiles = tileLayer.getTiles();
    auto &props = ctx.data.tileMapProps;
    auto &tileMap = ctx.data.tileMap;
    tileMap.tileCount = (int)srcTiles.size();
    props.srcTileW = tileset.getTileSize().x;
    props.srcTileH = tileset.getTileSize().y;
    props.columns = tileset.getColumnCount();
    props.mapW = map.getTileCount().x;
    props.dstTileW = map.getTileSize().x;
    props.dstTileH = map.getTileSize().y;
    props.firstGid = tileset.getFirstGID();
    for (int i = 0; i < tileMap.tileCount; i++)
    {
        uint32_t gid = srcTiles[i].ID;
        if (gid == 0)
        {
            tileMap.tiles.srcX[i] = UINT32_MAX;
            continue;
        }
        int idx = gid - props.firstGid;
        tileMap.tiles.srcX[i] = idx % props.columns * props.srcTileW;
        tileMap.tiles.srcY[i] = idx / props.columns * props.srcTileH;
        tileMap.tiles.dstX[i] = i % props.mapW * props.dstTileW;
        tileMap.tiles.dstY[i] = i / props.mapW * props.dstTileH;
    }
}

void RenderSystem(const Context &ctx)
{
    auto &props = ctx.data.tileMapProps;
    auto &tileMap = ctx.data.tileMap;
    SDL_RenderClear(ctx.renderer);
    for (int i = 0; i < tileMap.tileCount; i++)
    {
        if (tileMap.tiles.srcX[i] == UINT32_MAX)
            continue;
        SDL_FRect src = {(float)tileMap.tiles.srcX[i], (float)tileMap.tiles.srcY[i], (float)props.srcTileW, (float)props.srcTileH};
        SDL_FRect dst = {(float)tileMap.tiles.dstX[i], (float)tileMap.tiles.dstY[i], (float)props.dstTileW, (float)props.dstTileH};
        SDL_RenderTexture(ctx.renderer, ctx.texture, &src, &dst);
    }
    SDL_RenderPresent(ctx.renderer);
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("gg2", 1280, 720, 0);
    Context ctx;
    ctx.renderer = SDL_CreateRenderer(window, nullptr);

    SDL_Surface *surface = IMG_Load("assets/texture/texture.png");
    ctx.texture = SDL_CreateTextureFromSurface(ctx.renderer, surface);
    SDL_SetTextureScaleMode(ctx.texture, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(surface);

    tmx::Map map;
    map.load("assets/map/map1.tmx");

    loadTileMap(ctx, map);

    bool running = true;
    SDL_Event event;
    ctx.frame.maxFps = 60;
    ctx.frame.frameCount = 0;
    ctx.frame.lastTicks = SDL_GetTicks();
    while (running)
    {
        ctx.frame.now = SDL_GetTicks();
        ctx.frame.dt = (ctx.frame.now - ctx.frame.lastTicks) / 1000.0f;
        ctx.frame.lastTicks = ctx.frame.now;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        RenderSystem(ctx);

        ctx.frame.frameTime = SDL_GetTicks() - ctx.frame.now;
        ctx.frame.targetTime = 1000 / ctx.frame.maxFps;
        if (ctx.frame.frameTime < ctx.frame.targetTime)
            SDL_Delay(ctx.frame.targetTime - ctx.frame.frameTime);

        if (++ctx.frame.frameCount % 60 == 0)
            SDL_Log("frame: %llu ms", ctx.frame.frameTime);
    }

    SDL_DestroyTexture(ctx.texture);
    SDL_DestroyRenderer(ctx.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
