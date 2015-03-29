#include "Level.h"

#include <SDLplusplus/Image.h>

using namespace SDL;

Level::Level(Renderer &p_renderer)
{
	renderer = &p_renderer;
}

void Level::Load()
{
	tmx.Load("Level1-1.tmx");
	
	tileset = Image::LoadTexture(*renderer, tmx.map.tileset.imageFilename);

	Size nbTiles = Size(tileset.GetSize().Width / tmx.map.tileset.tileWidth, tileset.GetSize().Height / tmx.map.tileset.tileHeight);
	
	tileRects = new Rect[nbTiles.Width * nbTiles.Height];
	for (int y = 0; y < nbTiles.Height; y++) {
		for (int x = 0; x < nbTiles.Width; x++) {
			tileRects[y * nbTiles.Width + x] = Rect(Point(x * tmx.map.tileset.tileWidth, y * tmx.map.tileset.tileHeight), Size(tmx.map.tileset.tileWidth, tmx.map.tileset.tileHeight));
		}
	}
}

void Level::Draw()
{
	for (int y = 0; y < tmx.map.height; y++) {
		for (int x = 0; x < tmx.map.width; x++) {
			int tile = tmx.map.layer.tiles[y * tmx.map.width + x] - tmx.map.tileset.firstGID;
			renderer->Copy(tileset, tileRects[tile], Rect(Point(x * tmx.map.tileWidth, y * tmx.map.tileHeight - 2300), Size(tmx.map.tileWidth, tmx.map.tileHeight)));
		}
	}
}