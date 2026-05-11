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
    {"id": 0, "filename": "../grass.png", "x": 0, "y": 0},
    {"id": 1, "filename": "../road.png", "x": 4, "y": 0},
    {"id": 2, "filename": "../player.png", "x": 6, "y": 0},
    {"id": 3, "filename": "../redmonster.png", "x": 6, "y": 1},
    {"id": 4, "filename": "../greenmonster.png", "x": 6, "y": 2},
    {
        "id": 5,
        "filename": "../tree.png",
        "x": 6,
        "y": 3,
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
        "x": 2,
        "y": 4,
        "h": 64,
        "markerFor": 7,
        "colX": 0,
        "colY": 93,
        "colW": 74,
        "colH": 51,
    },
    {"id": 7, "filename": "../statue praying.png", "x": 0, "y": 4},
    {"id": 8, "filename": "../tree.png", "x": 7, "y": 0, "h": 350},
    {"id": 9, "filename": "../flowers.png", "x": 3, "y": 4},
    {"id": 10, "filename": "../fireplace/frame_00_delay-0.08s.gif", "x": 0, "y": 8, "h": 64},
    {"id": 11, "filename": "../fireplace/frame_01_delay-0.08s.gif", "x": 1, "y": 8, "h": 64},
    {"id": 12, "filename": "../fireplace/frame_02_delay-0.08s.gif", "x": 2, "y": 8, "h": 64},
    {"id": 13, "filename": "../fireplace/frame_03_delay-0.08s.gif", "x": 3, "y": 8, "h": 64},
    {"id": 14, "filename": "../fireplace/frame_04_delay-0.08s.gif", "x": 4, "y": 8, "h": 64},
    {"id": 15, "filename": "../fireplace/frame_05_delay-0.08s.gif", "x": 5, "y": 8, "h": 64},
    {"id": 16, "filename": "../fireplace/frame_06_delay-0.08s.gif", "x": 6, "y": 8, "h": 64},
    {"id": 17, "filename": "../fireplace/frame_07_delay-0.08s.gif", "x": 7, "y": 8, "h": 64},
    {"id": 18, "filename": "../fireplace/frame_08_delay-0.08s.gif", "x": 8, "y": 8, "h": 64},
    {"id": 19, "filename": "../fireplace/frame_09_delay-0.08s.gif", "x": 9, "y": 8, "h": 64},
    {"id": 20, "filename": "../fireplace/frame_10_delay-0.08s.gif", "x": 10, "y": 8, "h": 64},
    {"id": 21, "filename": "../fireplace/frame_11_delay-0.08s.gif", "x": 11, "y": 8, "h": 64},
    {"id": 23, "filename": "../pixelweapons.png", "x": 0, "y": 9},
    {"id": 22, "filename": "../dog.png", "x": 0, "y": 7},
]


if __name__ == "__main__":
    base_dir = os.path.dirname(os.path.abspath(__file__))
    meta = build_atlas(base_dir, settings, images)
    update_tileset(base_dir, settings, images, meta)
