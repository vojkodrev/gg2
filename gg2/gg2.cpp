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

struct Player
{
    uint32_t srcX, srcY, srcW, srcH;
    uint32_t x, y, w, h;
};

const int MAX_NPCS = 100;

struct NPCPosition
{
    uint32_t x[MAX_NPCS];
    uint32_t y[MAX_NPCS];
    uint32_t w[MAX_NPCS];
    uint32_t h[MAX_NPCS];
};

struct NPCSrc
{
    uint32_t x[MAX_NPCS];
    uint32_t y[MAX_NPCS];
    uint32_t w[MAX_NPCS];
    uint32_t h[MAX_NPCS];
};

struct NPC
{
    int npcCount;
    NPCSrc src;
    NPCPosition position;
};

struct Data
{
    TileMapProperties tileMapProps;
    TileMap tileMap;
    Player player;
    NPC npc;
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

void UpdateFrameStateSystem(Context &ctx)
{
    ctx.frame.now = SDL_GetTicks();
    ctx.frame.dt = (ctx.frame.now - ctx.frame.lastTicks) / 1000.0f;
    ctx.frame.lastTicks = ctx.frame.now;
}

void FrameRateLimitSystem(Context &ctx)
{
    ctx.frame.frameTime = SDL_GetTicks() - ctx.frame.now;
    ctx.frame.targetTime = 1000 / ctx.frame.maxFps;
    if (ctx.frame.frameTime < ctx.frame.targetTime)
        SDL_Delay(ctx.frame.targetTime - ctx.frame.frameTime);

    if (++ctx.frame.frameCount % 60 == 0)
        SDL_Log("frame: %llu ms", ctx.frame.frameTime);
}

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

    auto &playerLayer = map.getLayers()[1]->getLayerAs<tmx::TileLayer>();
    auto &playerTiles = playerLayer.getTiles();
    for (int i = 0; i < (int)playerTiles.size(); i++)
    {
        if (playerTiles[i].ID == 0)
            continue;
        int idx = playerTiles[i].ID - props.firstGid;
        ctx.data.player.srcX = idx % props.columns * props.srcTileW;
        ctx.data.player.srcY = idx / props.columns * props.srcTileH;
        ctx.data.player.srcW = props.srcTileW;
        ctx.data.player.srcH = props.srcTileH;
        ctx.data.player.x = i % props.mapW * props.dstTileW;
        ctx.data.player.y = i / props.mapW * props.dstTileH;
        ctx.data.player.w = props.dstTileW;
        ctx.data.player.h = props.dstTileH;
        break;
    }

    auto &npcLayer = map.getLayers()[2]->getLayerAs<tmx::TileLayer>();
    auto &npcTiles = npcLayer.getTiles();
    auto &npc = ctx.data.npc;
    npc.npcCount = 0;
    for (int i = 0; i < (int)npcTiles.size(); i++)
    {
        if (npcTiles[i].ID == 0)
            continue;
        int n = npc.npcCount++;
        int idx = npcTiles[i].ID - props.firstGid;
        npc.src.x[n] = idx % props.columns * props.srcTileW;
        npc.src.y[n] = idx / props.columns * props.srcTileH;
        npc.src.w[n] = props.srcTileW;
        npc.src.h[n] = props.srcTileH;
        npc.position.x[n] = i % props.mapW * props.dstTileW;
        npc.position.y[n] = i / props.mapW * props.dstTileH;
        npc.position.w[n] = props.dstTileW;
        npc.position.h[n] = props.dstTileH;
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
    auto &player = ctx.data.player;
    SDL_FRect playerSrc = {(float)player.srcX, (float)player.srcY, (float)player.srcW, (float)player.srcH};
    SDL_FRect playerDst = {(float)player.x, (float)player.y, (float)player.w, (float)player.h};
    SDL_RenderTexture(ctx.renderer, ctx.texture, &playerSrc, &playerDst);

    auto &npc = ctx.data.npc;
    for (int i = 0; i < npc.npcCount; i++)
    {
        SDL_FRect npcSrc = {(float)npc.src.x[i], (float)npc.src.y[i], (float)npc.src.w[i], (float)npc.src.h[i]};
        SDL_FRect npcDst = {(float)npc.position.x[i], (float)npc.position.y[i], (float)npc.position.w[i], (float)npc.position.h[i]};
        SDL_RenderTexture(ctx.renderer, ctx.texture, &npcSrc, &npcDst);
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
        UpdateFrameStateSystem(ctx);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        RenderSystem(ctx);

        FrameRateLimitSystem(ctx);
    }

    SDL_DestroyTexture(ctx.texture);
    SDL_DestroyRenderer(ctx.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
