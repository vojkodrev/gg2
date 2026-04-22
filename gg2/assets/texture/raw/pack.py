settings = {
    "tileW": 64,
    "tileH": 64,
    "w": 12,
    "h": 7,
    "output": "texture.png",
}

images = [
    {"filename": "grass.png", "x": 0, "y": 0},
    {"filename": "road.png", "x": 4, "y": 0},
    {"filename": "player.png", "x": 6, "y": 0},
    {"filename": "redmonster.png", "x": 6, "y": 1},
    {"filename": "greenmonster.png", "x": 6, "y": 2},
    {"filename": "tree.png", "x": 6, "y": 3, "h": 64},
    {"filename": "statue praying.png", "x": 2, "y": 4, "h": 64},
    {"filename": "statue praying.png", "x": 0, "y": 4},
    {"filename": "tree.png", "x": 7, "y": 0},
]

if __name__ == "__main__":
    from PIL import Image
    import os

    dir = os.path.dirname(os.path.abspath(__file__))
    tileW = settings["tileW"]
    tileH = settings["tileH"]
    atlas = Image.new("RGBA", (settings["w"] * tileW, settings["h"] * tileH), (0, 0, 0, 0))

    for img in images:
        src = Image.open(os.path.join(dir, img["filename"])).convert("RGBA")
        if "h" in img:
            target_h = img["h"]
            target_w = round(src.width * target_h / src.height)
            src = src.resize((target_w, target_h), Image.NEAREST)
        atlas.paste(src, (img["x"] * tileW, img["y"] * tileH))

    atlas.save(os.path.join(dir, settings["output"]))
