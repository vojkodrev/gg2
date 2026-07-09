import os

from build_atlas import build_atlas
from update_tileset import update_tileset

settings = {
    "tileW": 64,
    "tileH": 64,
    "output": "../../texture.png",
    "tileset": "../../../map/texture.tsx",
}

images = [
    {"id": 0, "filename": "../grass.png", "dx": 0, "dy": 0},
    {"id": 1, "filename": "../road.png", "dx": 4, "dy": 0},
    {"id": 2, "filename": "../player.png", "dx": 6, "dy": 0},
    {"id": 3, "filename": "../redmonster.png", "dx": 6, "dy": 1},
    {"id": 4, "filename": "../greenmonster.png", "dx": 6, "dy": 2},
    {
        "id": 5,
        "filename": "../tree.png",
        "dx": 6,
        "dy": 3,
        "h": 64,
        "markerFor": 8,
        "colX": 100,
        "colY": 257,
        "colW": 22,
        "colH": 21,
    },
    {
        "id": 6,
        "filename": "../statue praying.png",
        "dx": 2,
        "dy": 4,
        "h": 64,
        "markerFor": 7,
        "colX": 0,
        "colY": 93,
        "colW": 74,
        "colH": 51,
    },
    {"id": 7, "filename": "../statue praying.png", "dx": 0, "dy": 4},
    {"id": 8, "filename": "../tree.png", "dx": 7, "dy": 0, "h": 350},
    {"id": 9, "filename": "../flowers.png", "dx": 3, "dy": 4},
    {"id": 10, "filename": "../fireplace/frame_00_delay-0.08s.gif", "dx": 0, "dy": 8, "h": 64},
    {"id": 11, "filename": "../fireplace/frame_01_delay-0.08s.gif", "dx": 1, "dy": 8, "h": 64},
    {"id": 12, "filename": "../fireplace/frame_02_delay-0.08s.gif", "dx": 2, "dy": 8, "h": 64},
    {"id": 13, "filename": "../fireplace/frame_03_delay-0.08s.gif", "dx": 3, "dy": 8, "h": 64},
    {"id": 14, "filename": "../fireplace/frame_04_delay-0.08s.gif", "dx": 4, "dy": 8, "h": 64},
    {"id": 15, "filename": "../fireplace/frame_05_delay-0.08s.gif", "dx": 5, "dy": 8, "h": 64},
    {"id": 16, "filename": "../fireplace/frame_06_delay-0.08s.gif", "dx": 6, "dy": 8, "h": 64},
    {"id": 17, "filename": "../fireplace/frame_07_delay-0.08s.gif", "dx": 7, "dy": 8, "h": 64},
    {"id": 18, "filename": "../fireplace/frame_08_delay-0.08s.gif", "dx": 8, "dy": 8, "h": 64},
    {"id": 19, "filename": "../fireplace/frame_09_delay-0.08s.gif", "dx": 9, "dy": 8, "h": 64},
    {"id": 20, "filename": "../fireplace/frame_10_delay-0.08s.gif", "dx": 10, "dy": 8, "h": 64},
    {"id": 21, "filename": "../fireplace/frame_11_delay-0.08s.gif", "dx": 11, "dy": 8, "h": 64},
    {"id": 22, "filename": "../dog.png", "dx": 0, "dy": 7},
    {"id": 23, "filename": "../pixelweapons.png", "dx": 0, "dy": 9},
    {"id": 24, "filename": "../healthbars.png", "dx": 0, "dy": 22, "sx": 1 * 48, "sy": 8 * 16, "sw": 50, "sh": 16, "w": 64},
    {"id": 25, "filename": "../healthbars.png", "dx": 1, "dy": 22, "sx": 2 * 48, "sy": 8 * 16, "sw": 50, "sh": 16, "w": 64},
    {"id": 26, "filename": "../healthbars.png", "dx": 2, "dy": 22, "sx": 3 * 48, "sy": 8 * 16, "sw": 50, "sh": 16, "w": 64},
    {"id": 27, "filename": "../healthbars.png", "dx": 3, "dy": 22, "sx": 4 * 48, "sy": 8 * 16, "sw": 50, "sh": 16, "w": 64},
    {"id": 28, "filename": "../healthbars.png", "dx": 4, "dy": 22, "sx": 5 * 48, "sy": 8 * 16, "sw": 50, "sh": 16, "w": 64},
    {"id": 29, "filename": "../healthbars.png", "dx": 5, "dy": 22, "sx": 6 * 48, "sy": 8 * 16, "sw": 50, "sh": 16, "w": 64},
    {"id": 30, "filename": "../font/boldpixels.png", "dx": 12, "dy": 0},
    {"id": 31, "filename": "../pixel ui pack 3-7.png", "dx": 6, "dy": 22, "sx": 3 * 32, "sy": 176, "sw": 32, "sh": 32},
    {"id": 32, "filename": "../icons/Ability_Hunter_Quickshot.png", "dx": 8, "dy": 22},
    {"id": 33, "filename": "../icons/INV_Weapon_Bow_02.png", "dx": 9, "dy": 22},
    {"id": 34, "filename": "../healthbars.png", "dx": 0, "dy": 23, "sx": 1 * 48, "sy": 9 * 16, "sw": 50, "sh": 16, "w": 64},
    {"id": 35, "filename": "../healthbars.png", "dx": 1, "dy": 23, "sx": 2 * 48, "sy": 9 * 16, "sw": 50, "sh": 16, "w": 64},
    {"id": 36, "filename": "../healthbars.png", "dx": 2, "dy": 23, "sx": 3 * 48, "sy": 9 * 16, "sw": 50, "sh": 16, "w": 64},
    {"id": 37, "filename": "../healthbars.png", "dx": 3, "dy": 23, "sx": 4 * 48, "sy": 9 * 16, "sw": 50, "sh": 16, "w": 64},
    {"id": 38, "filename": "../healthbars.png", "dx": 4, "dy": 23, "sx": 5 * 48, "sy": 9 * 16, "sw": 50, "sh": 16, "w": 64},
    {"id": 39, "filename": "../healthbars.png", "dx": 5, "dy": 23, "sx": 6 * 48, "sy": 9 * 16, "sw": 50, "sh": 16, "w": 64}, 
    {"id": 40, "filename": "../icons/Spell_Frost_Stun.png", "dx": 10, "dy": 22},
    {"id": 41, "filename": "../blood splatter/B100.png", "dx": 6, "dy": 23, "w": 64}, 
    {"id": 42, "filename": "../blood splatter/B101.png", "dx": 7, "dy": 23, "w": 64}, 
    {"id": 43, "filename": "../blood splatter/B102.png", "dx": 8, "dy": 23, "w": 64}, 
]


if __name__ == "__main__":
    base_dir = os.path.dirname(os.path.abspath(__file__))
    atlas_meta = build_atlas(base_dir, settings, images)
    update_tileset(base_dir, settings, images, atlas_meta)
