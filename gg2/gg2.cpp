#include <SDL3/SDL.h>
#include <functional>
#include <SDL3_image/SDL_image.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

struct TileMapProperties
{
    uint32_t srcTileW, srcTileH;
    uint32_t columns;
    uint32_t mapW;
    uint32_t dstTileW, dstTileH;
    uint32_t firstGid;
};

const int MAX_TILES = 1000;

struct Tile
{
    uint32_t srcX[MAX_TILES];
    uint32_t srcY[MAX_TILES];
    int32_t dstX[MAX_TILES];
    int32_t dstY[MAX_TILES];
};

struct TileMap
{
    uint32_t tileCount;
    Tile tiles;
};

struct Player
{
    uint32_t srcX, srcY, srcW, srcH;
    float x, y, w, h;
    float colOffX, colOffY, colW, colH;
};

const int MAX_NPCS = 100;

struct NPCPosition
{
    float x[MAX_NPCS];
    float y[MAX_NPCS];
    float w[MAX_NPCS];
    float h[MAX_NPCS];
};

struct NPCSrc
{
    uint32_t x[MAX_NPCS];
    uint32_t y[MAX_NPCS];
    uint32_t w[MAX_NPCS];
    uint32_t h[MAX_NPCS];
};

struct NPCCollision
{
    float offX[MAX_NPCS];
    float offY[MAX_NPCS];
    float w[MAX_NPCS];
    float h[MAX_NPCS];
};

struct NPC
{
    uint32_t npcCount;
    NPCSrc src;
    NPCPosition position;
    NPCCollision collision;
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
    uint32_t maxFps;
    uint32_t frameCount;
    Uint64 lastTicks;
    Uint64 now;
    float dt;
    Uint64 frameTime;
    Uint64 targetTime;
};

const int MAX_RENDER_BUFFER = 100;

struct RenderSrc
{
    float x[MAX_RENDER_BUFFER];
    float y[MAX_RENDER_BUFFER];
    float w[MAX_RENDER_BUFFER];
    float h[MAX_RENDER_BUFFER];
};

struct RenderDst
{
    float x[MAX_RENDER_BUFFER];
    float y[MAX_RENDER_BUFFER];
    float w[MAX_RENDER_BUFFER];
    float h[MAX_RENDER_BUFFER];
    float colOffY[MAX_RENDER_BUFFER];
};

struct RenderBuffer
{
    uint32_t count;
    RenderSrc src;
    RenderDst dst;
};

struct Context
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    FrameState frame;
    Data data;
    RenderBuffer renderBuffer;
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

void LoadTileMap(Context &ctx, const tmx::Map &map)
{
    auto &tileset = map.getTilesets()[0];
    auto &tileLayer = map.getLayers()[0]->getLayerAs<tmx::TileLayer>();
    auto &srcTiles = tileLayer.getTiles();
    auto &props = ctx.data.tileMapProps;
    auto &tileMap = ctx.data.tileMap;
    props.srcTileW = tileset.getTileSize().x;
    props.srcTileH = tileset.getTileSize().y;
    props.columns = tileset.getColumnCount();
    props.mapW = map.getTileCount().x;
    props.dstTileW = map.getTileSize().x;
    props.dstTileH = map.getTileSize().y;
    props.firstGid = tileset.getFirstGID();
    tileMap.tileCount = 0;
    for (int i = 0; i < (int)srcTiles.size(); i++)
    {
        uint32_t gid = srcTiles[i].ID;
        if (gid == 0)
            continue;
        uint32_t n = tileMap.tileCount++;
        uint32_t idx = gid - props.firstGid;
        tileMap.tiles.srcX[n] = idx % props.columns * props.srcTileW;
        tileMap.tiles.srcY[n] = idx / props.columns * props.srcTileH;
        tileMap.tiles.dstX[n] = i % props.mapW * props.dstTileW;
        tileMap.tiles.dstY[n] = i / props.mapW * props.dstTileH;
    }

    auto getCollision = [&](uint32_t tileIdx, float &offX, float &offY, float &w, float &h) {
        for (auto &tile : tileset.getTiles()) {
            if (tile.ID != tileIdx)
                continue;
            auto &objs = tile.objectGroup.getObjects();
            if (!objs.empty()) {
                auto &aabb = objs[0].getAABB();
                offX = aabb.left;
                offY = aabb.top;
                w = aabb.width;
                h = aabb.height;
            }
            return;
        }
    };

    auto &playerLayer = map.getLayers()[1]->getLayerAs<tmx::TileLayer>();
    auto &playerTiles = playerLayer.getTiles();
    for (int i = 0; i < (int)playerTiles.size(); i++)
    {
        if (playerTiles[i].ID == 0)
            continue;
        uint32_t idx = playerTiles[i].ID - props.firstGid;
        ctx.data.player.srcX = idx % props.columns * props.srcTileW;
        ctx.data.player.srcY = idx / props.columns * props.srcTileH;
        ctx.data.player.srcW = props.srcTileW;
        ctx.data.player.srcH = props.srcTileH;
        ctx.data.player.x = i % props.mapW * props.dstTileW;
        ctx.data.player.y = i / props.mapW * props.dstTileH;
        ctx.data.player.w = props.dstTileW;
        ctx.data.player.h = props.dstTileH;
        getCollision(idx, ctx.data.player.colOffX, ctx.data.player.colOffY, ctx.data.player.colW, ctx.data.player.colH);
        break;
    }

    auto &npcLayer = map.getLayers()[2]->getLayerAs<tmx::TileLayer>();
    auto &npcTiles = npcLayer.getTiles();
    auto &npc = ctx.data.npc;
    npc.npcCount = 0;
    for (uint32_t i = 0; i < npcTiles.size(); i++)
    {
        if (npcTiles[i].ID == 0)
            continue;
        uint32_t n = npc.npcCount++;
        uint32_t idx = npcTiles[i].ID - props.firstGid;
        npc.src.x[n] = idx % props.columns * props.srcTileW;
        npc.src.y[n] = idx / props.columns * props.srcTileH;
        npc.src.w[n] = props.srcTileW;
        npc.src.h[n] = props.srcTileH;
        npc.position.x[n] = i % props.mapW * props.dstTileW;
        npc.position.y[n] = i / props.mapW * props.dstTileH;
        npc.position.w[n] = props.dstTileW;
        npc.position.h[n] = props.dstTileH;
        getCollision(idx, npc.collision.offX[n], npc.collision.offY[n], npc.collision.w[n], npc.collision.h[n]);
    }
}

void FillRenderBufferSystem(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    rb.count = 0;

    auto &player = ctx.data.player;
    uint32_t n = rb.count++;
    rb.src.x[n] = (float)player.srcX;
    rb.src.y[n] = (float)player.srcY;
    rb.src.w[n] = (float)player.srcW;
    rb.src.h[n] = (float)player.srcH;
    rb.dst.x[n] = player.x;
    rb.dst.y[n] = player.y;
    rb.dst.w[n] = player.w;
    rb.dst.h[n] = player.h;
    rb.dst.colOffY[n] = player.colOffY;

    auto &npc = ctx.data.npc;
    for (uint32_t i = 0; i < npc.npcCount; i++)
    {
        n = rb.count++;
        rb.src.x[n] = (float)npc.src.x[i];
        rb.src.y[n] = (float)npc.src.y[i];
        rb.src.w[n] = (float)npc.src.w[i];
        rb.src.h[n] = (float)npc.src.h[i];
        rb.dst.x[n] = npc.position.x[i];
        rb.dst.y[n] = npc.position.y[i];
        rb.dst.w[n] = npc.position.w[i];
        rb.dst.h[n] = npc.position.h[i];
        rb.dst.colOffY[n] = npc.collision.offY[i];
    }

    // sort ascending by y + colOffY (painter's algorithm: top of screen first)
    auto rbSwap = [&](uint32_t a, uint32_t b) {
        std::swap(rb.src.x[a], rb.src.x[b]);
        std::swap(rb.src.y[a], rb.src.y[b]);
        std::swap(rb.src.w[a], rb.src.w[b]);
        std::swap(rb.src.h[a], rb.src.h[b]);
        std::swap(rb.dst.x[a], rb.dst.x[b]);
        std::swap(rb.dst.y[a], rb.dst.y[b]);
        std::swap(rb.dst.w[a], rb.dst.w[b]);
        std::swap(rb.dst.h[a], rb.dst.h[b]);
        std::swap(rb.dst.colOffY[a], rb.dst.colOffY[b]);
    };
    auto depthKey = [&](uint32_t i) { return rb.dst.y[i] + rb.dst.colOffY[i]; };
    std::function<void(int, int)> rbSort = [&](int lo, int hi) {
        if (lo >= hi) return;
        float pivot = depthKey(lo + (hi - lo) / 2);
        int i = lo, j = hi;
        while (i <= j) {
            while (depthKey(i) < pivot) i++;
            while (depthKey(j) > pivot) j--;
            if (i <= j) { rbSwap(i++, j--); }
        }
        rbSort(lo, j);
        rbSort(i, hi);
    };
    if (rb.count > 1)
        rbSort(0, (int)rb.count - 1);
}

void RenderSystem(const Context &ctx)
{
    auto &props = ctx.data.tileMapProps;
    auto &tileMap = ctx.data.tileMap;
    SDL_RenderClear(ctx.renderer);
    for (uint32_t i = 0; i < tileMap.tileCount; i++)
    {
        SDL_FRect src = {(float)tileMap.tiles.srcX[i], (float)tileMap.tiles.srcY[i], (float)props.srcTileW, (float)props.srcTileH};
        SDL_FRect dst = {(float)tileMap.tiles.dstX[i], (float)tileMap.tiles.dstY[i], (float)props.dstTileW, (float)props.dstTileH};
        SDL_RenderTexture(ctx.renderer, ctx.texture, &src, &dst);
    }
    auto &rb = ctx.renderBuffer;
    for (uint32_t i = 0; i < rb.count; i++)
    {
        SDL_FRect src = {rb.src.x[i], rb.src.y[i], rb.src.w[i], rb.src.h[i]};
        SDL_FRect dst = {rb.dst.x[i], rb.dst.y[i], rb.dst.w[i], rb.dst.h[i]};
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

    LoadTileMap(ctx, map);

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

        FillRenderBufferSystem(ctx);
        RenderSystem(ctx);

        FrameRateLimitSystem(ctx);
    }

    SDL_DestroyTexture(ctx.texture);
    SDL_DestroyRenderer(ctx.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
