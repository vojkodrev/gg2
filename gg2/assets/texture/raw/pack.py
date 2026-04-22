settings = {
    "tileW": 64,
    "tileH": 64,
    "w": 12,
    "h": 8,
    "output": "../texture.png",
    "tileset": "../../map/texture.tsx",
}

images = [
    {"id": 0, "filename": "grass.png", "x": 0, "y": 0},
    {"id": 1, "filename": "road.png", "x": 4, "y": 0},
    {"id": 2, "filename": "player.png", "x": 6, "y": 0},
    {"id": 3, "filename": "redmonster.png", "x": 6, "y": 1},
    {"id": 4, "filename": "greenmonster.png", "x": 6, "y": 2},
    {
        "id": 5,
        "filename": "tree.png",
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
        "filename": "statue praying.png",
        "x": 2,
        "y": 4,
        "h": 64,
        "markerFor": 7,
        "colX": 0,
        "colY": 93,
        "colW": 74,
        "colH": 51,
    },
    {"id": 7, "filename": "statue praying.png", "x": 0, "y": 4},
    {"id": 8, "filename": "tree.png", "x": 7, "y": 0, "h": 350},
    {"id": 9, "filename": "flowers.png", "x": 3, "y": 4},
]


def build_atlas(dir):
    from PIL import Image

    tileW = settings["tileW"]
    tileH = settings["tileH"]
    atlas = Image.new(
        "RGBA", (settings["w"] * tileW, settings["h"] * tileH), (0, 0, 0, 0)
    )
    meta = {}
    for img in images:
        src = Image.open(os.path.join(dir, img["filename"])).convert("RGBA")
        scale = 1.0
        if "h" in img:
            scale = img["h"] / src.height
            target_w = round(src.width * scale)
            src = src.resize((target_w, img["h"]), Image.NEAREST)
        tilesW = max(1, -(-src.width // tileW))
        tilesH = max(1, -(-src.height // tileH))
        offX = (tilesW * tileW - src.width) // 2
        offY = (tilesH * tileH - src.height) // 2
        pasteX = img["x"] * tileW + offX
        pasteY = img["y"] * tileH + offY
        meta[img["id"]] = {
            "x": pasteX,
            "y": pasteY,
            "w": src.width,
            "h": src.height,
            "scale": scale,
            "offX": offX,
            "offY": offY,
        }
        atlas.paste(src, (pasteX, pasteY))
    atlas.save(os.path.join(dir, settings["output"]))
    return meta


def update_tileset(dir, meta):
    import xml.etree.ElementTree as ET

    ET.register_namespace("", "")
    tsx_path = os.path.join(dir, settings["tileset"])
    tree = ET.parse(tsx_path)
    root = tree.getroot()
    columns = settings["w"]

    def set_prop(props_el, name, ptype, value):
        prop = next(
            (p for p in props_el.findall("property") if p.get("name") == name), None
        )
        if prop is None:
            prop = ET.SubElement(props_el, "property")
            prop.set("name", name)
        if ptype:
            prop.set("type", ptype)
        elif "type" in prop.attrib:
            del prop.attrib["type"]
        prop.set("value", str(value))

    for img in images:
        if "markerFor" not in img:
            continue
        m = meta[img["markerFor"]]
        tile_id = str(img["y"] * columns + img["x"])
        tile_el = next(
            (t for t in root.findall("tile") if t.get("id") == tile_id), None
        )
        if tile_el is None:
            tile_el = ET.SubElement(root, "tile")
            tile_el.set("id", tile_id)
        props_el = tile_el.find("properties")
        if props_el is None:
            props_el = ET.SubElement(tile_el, "properties")
        set_prop(props_el, "type", None, "marker")
        set_prop(props_el, "x", "int", m["x"])
        set_prop(props_el, "y", "int", m["y"])
        set_prop(props_el, "w", "int", m["w"])
        set_prop(props_el, "h", "int", m["h"])
        if "colX" in img:
            tm = meta[img["markerFor"]]
            s = tm["scale"]
            set_prop(props_el, "colOffX", "int", round(img["colX"] * s))
            set_prop(props_el, "colOffY", "int", round(img["colY"] * s))
            set_prop(props_el, "colW", "int", round(img["colW"] * s))
            set_prop(props_el, "colH", "int", round(img["colH"] * s))

    ET.indent(tree, space=" ")
    tree.write(tsx_path, encoding="unicode", xml_declaration=True)


if __name__ == "__main__":
    import os

    dir = os.path.dirname(os.path.abspath(__file__))
    meta = build_atlas(dir)
    update_tileset(dir, meta)
