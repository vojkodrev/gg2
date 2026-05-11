import os

from PIL import Image


def build_atlas(base_dir, settings, images):
    tile_w = settings["tileW"]
    tile_h = settings["tileH"]
    meta = {}
    prepared = []
    atlas_tiles_w = 0
    atlas_tiles_h = 0

    for img in images:
        src = Image.open(os.path.join(base_dir, img["filename"])).convert("RGBA")
        scale = 1.0
        if "h" in img:
            scale = img["h"] / src.height
            target_w = round(src.width * scale)
            src = src.resize((target_w, img["h"]), Image.Resampling.NEAREST)
        tiles_w = max(1, -(-src.width // tile_w))
        tiles_h = max(1, -(-src.height // tile_h))
        atlas_tiles_w = max(atlas_tiles_w, img["x"] + tiles_w)
        atlas_tiles_h = max(atlas_tiles_h, img["y"] + tiles_h)
        prepared.append((img, src, scale, tiles_w, tiles_h))

    atlas = Image.new(
        "RGBA", (atlas_tiles_w * tile_w, atlas_tiles_h * tile_h), (0, 0, 0, 0)
    )

    for img, src, scale, tiles_w, tiles_h in prepared:
        off_x = (tiles_w * tile_w - src.width) // 2
        off_y = (tiles_h * tile_h - src.height) // 2
        paste_x = img["x"] * tile_w + off_x
        paste_y = img["y"] * tile_h + off_y
        meta[img["id"]] = {
            "x": paste_x,
            "y": paste_y,
            "w": src.width,
            "h": src.height,
            "scale": scale,
            "offX": off_x,
            "offY": off_y,
        }
        atlas.paste(src, (paste_x, paste_y))
    atlas.save(os.path.join(base_dir, settings["output"]))
    return meta
