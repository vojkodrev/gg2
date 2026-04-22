settings = {
    "tileW": 64,
    "tileH": 64,
    "w": 12,
    "h": 7,
    "output": "../texture.png",
    "tileset": "../../map/texture.tsx"
}

images = [
    {"id": 0, "filename": "grass.png", "x": 0, "y": 0},
    {"id": 1, "filename": "road.png", "x": 4, "y": 0},
    {"id": 2, "filename": "player.png", "x": 6, "y": 0},
    {"id": 3, "filename": "redmonster.png", "x": 6, "y": 1},
    {"id": 4, "filename": "greenmonster.png", "x": 6, "y": 2},
    {"id": 5, "filename": "tree.png", "x": 6, "y": 3, "h": 64, "markerFor": 8},
    {"id": 6, "filename": "statue praying.png", "x": 2, "y": 4, "h": 64, "markerFor": 7},
    {"id": 7, "filename": "statue praying.png", "x": 0, "y": 4},
    {"id": 8, "filename": "tree.png", "x": 7, "y": 0},
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
        tilesW = max(1, -(-src.width // tileW))   # ceil div
        tilesH = max(1, -(-src.height // tileH))
        areaW = tilesW * tileW
        areaH = tilesH * tileH
        offX = (areaW - src.width) // 2
        offY = (areaH - src.height) // 2
        atlas.paste(src, (img["x"] * tileW + offX, img["y"] * tileH + offY))

    atlas.save(os.path.join(dir, settings["output"]))

    # update marker tile properties in tsx
    import xml.etree.ElementTree as ET

    ET.register_namespace("", "")
    tsx_path = os.path.join(dir, settings["tileset"])
    tree = ET.parse(tsx_path)
    root = tree.getroot()
    columns = settings["w"]

    img_by_id = {img["id"]: img for img in images}

    for img in images:
        if "markerFor" not in img:
            continue

        target = img_by_id[img["markerFor"]]
        tsrc = Image.open(os.path.join(dir, target["filename"])).convert("RGBA")
        if "h" in target:
            th = target["h"]
            tw = round(tsrc.width * th / tsrc.height)
            tsrc = tsrc.resize((tw, th), Image.NEAREST)

        t_tilesW = max(1, -(-tsrc.width // tileW))
        t_tilesH = max(1, -(-tsrc.height // tileH))
        t_offX = (t_tilesW * tileW - tsrc.width) // 2
        t_offY = (t_tilesH * tileH - tsrc.height) // 2
        px = target["x"] * tileW + t_offX
        py = target["y"] * tileH + t_offY
        pw = tsrc.width
        ph = tsrc.height

        tile_id = str(img["y"] * columns + img["x"])
        tile_el = next((t for t in root.findall("tile") if t.get("id") == tile_id), None)
        if tile_el is None:
            tile_el = ET.SubElement(root, "tile")
            tile_el.set("id", tile_id)

        props_el = tile_el.find("properties")
        if props_el is None:
            props_el = ET.SubElement(tile_el, "properties")

        def set_prop(name, ptype, value):
            prop = next((p for p in props_el.findall("property") if p.get("name") == name), None)
            if prop is None:
                prop = ET.SubElement(props_el, "property")
                prop.set("name", name)
            if ptype:
                prop.set("type", ptype)
            elif "type" in prop.attrib:
                del prop.attrib["type"]
            prop.set("value", str(value))

        set_prop("type", None, "marker")
        set_prop("x", "int", px)
        set_prop("y", "int", py)
        set_prop("w", "int", pw)
        set_prop("h", "int", ph)

    ET.indent(tree, space=" ")
    tree.write(tsx_path, encoding="unicode", xml_declaration=True)
