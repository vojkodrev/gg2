import os
from io import StringIO
import xml.etree.ElementTree as ET


def set_prop(props_el, name, ptype, value):
    prop = next((p for p in props_el.findall("property") if p.get("name") == name), None)
    if prop is None:
        prop = ET.SubElement(props_el, "property")
        prop.set("name", name)
    if ptype:
        prop.set("type", ptype)
    elif "type" in prop.attrib:
        del prop.attrib["type"]
    prop.set("value", str(value))


def update_tileset(base_dir, settings, images, meta):
    ET.register_namespace("", "")
    tsx_path = os.path.join(base_dir, settings["tileset"])
    tree = ET.parse(tsx_path)
    root = tree.getroot()
    columns = meta["columns"]

    root.set("tilecount", str(meta["tilecount"]))
    root.set("columns", str(columns))

    image_el = root.find("image")
    if image_el is None:
        image_el = ET.SubElement(root, "image")
    image_el.set("width", str(meta["width"]))
    image_el.set("height", str(meta["height"]))

    for img in images:
        if "markerFor" not in img:
            continue
        marker_meta = meta["tiles"][img["markerFor"]]
        tile_id = str(img["dy"] * columns + img["dx"])
        tile_el = next((t for t in root.findall("tile") if t.get("id") == tile_id), None)
        if tile_el is None:
            tile_el = ET.SubElement(root, "tile")
            tile_el.set("id", tile_id)
        props_el = tile_el.find("properties")
        if props_el is None:
            props_el = ET.SubElement(tile_el, "properties")
        set_prop(props_el, "type", None, "marker")
        set_prop(props_el, "x", "int", marker_meta["x"])
        set_prop(props_el, "y", "int", marker_meta["y"])
        set_prop(props_el, "w", "int", marker_meta["w"])
        set_prop(props_el, "h", "int", marker_meta["h"])
        if "colX" in img:
            scale = marker_meta["scale"]
            set_prop(props_el, "colOffX", "int", round(img["colX"] * scale))
            set_prop(props_el, "colOffY", "int", round(img["colY"] * scale))
            set_prop(props_el, "colW", "int", round(img["colW"] * scale))
            set_prop(props_el, "colH", "int", round(img["colH"] * scale))

    ET.indent(tree, space=" ")
    buffer = StringIO()
    tree.write(buffer, encoding="unicode", xml_declaration=False)
    xml_text = buffer.getvalue().replace(" />", "/>")
    with open(tsx_path, "w", encoding="UTF-8", newline="\n") as tsx_file:
        tsx_file.write('<?xml version="1.0" encoding="UTF-8"?>\n')
        tsx_file.write(xml_text)
        tsx_file.write("\n")
