import os
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
    columns = settings["w"]

    for img in images:
        if "markerFor" not in img:
            continue
        marker_meta = meta[img["markerFor"]]
        tile_id = str(img["y"] * columns + img["x"])
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
    tree.write(tsx_path, encoding="unicode", xml_declaration=True)
