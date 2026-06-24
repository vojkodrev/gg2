from pathlib import Path

from PIL import Image, ImageDraw, ImageFont

FONT_FILENAME = "../boldpixels.ttf"
OUTPUT_FILENAME = "../boldpixels.png"

FONT_SIZE = 16
GLYPH_W = 8
GLYPH_H = 16
GRID_W = 16
GLYPH_COUNT = 256


def main():
    base_dir = Path(__file__).resolve().parent
    font_path = (base_dir / FONT_FILENAME).resolve()
    output_path = (base_dir / OUTPUT_FILENAME).resolve()

    grid_h = (GLYPH_COUNT + GRID_W - 1) // GRID_W

    image = Image.new("RGBA", (GRID_W * GLYPH_W, grid_h * GLYPH_H), (0, 0, 0, 0))
    draw = ImageDraw.Draw(image)
    font = ImageFont.truetype(str(font_path), FONT_SIZE)

    for index in range(GLYPH_COUNT):
        char = bytes([index]).decode("cp1252", errors="ignore")
        if not char or not char.isprintable():
            continue

        col = index % GRID_W
        row = index // GRID_W
        x = col * GLYPH_W
        y = row * GLYPH_H
        draw.text((x, y), char, font=font, fill=(255, 255, 255, 255))

    image.save(output_path)
    print(f"Saved {output_path}")


if __name__ == "__main__":
    main()
