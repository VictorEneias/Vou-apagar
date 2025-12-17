// include/TileSet.h
#pragma once
#include <string>
#include "Sprite.h"

class TileSet {
public:
    TileSet(int tileWidth, int tileHeight, const std::string& file);
    void RenderTile(unsigned index, float x, float y);
    int  GetTileWidth()  const { return tileWidth; }
    int  GetTileHeight() const { return tileHeight; }
private:
    Sprite sprite;
    int tileWidth{0}, tileHeight{0};
    int tileCount{0};
    int columns{0};
};
