#include "LoadTileMap.h"
#include <tmxlite/TileLayer.hpp>

namespace
{
    const tmx::Layer *findLayer(const tmx::Map &map, const std::string &name)
    {
        for (auto &layer : map.getLayers())
            if (layer->getName() == name)
                return layer.get();
        return nullptr;
    }
}

void LoadTileMap(Context &ctx, const tmx::Map &map)
{
    auto &tileset = map.getTilesets()[0];
    auto &tileLayer = findLayer(map, "Ground")->getLayerAs<tmx::TileLayer>();
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

    auto &playerLayer = findLayer(map, "Player")->getLayerAs<tmx::TileLayer>();
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

    auto &npcLayer = findLayer(map, "NPC")->getLayerAs<tmx::TileLayer>();
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
