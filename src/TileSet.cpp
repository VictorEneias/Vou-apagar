#include "TileSet.h"
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, const std::string& file)
: sprite(), tileWidth(tileWidth), tileHeight(tileHeight) {
    sprite.Open(file);
    if (!sprite.IsOpen()) {
        std::cerr << "[TileSet] Falha ao abrir '" << file << "'" << std::endl;
        tileWidth = tileHeight = 0;
        tileCount = columns = 0;
        return;
    }

    const int totalW = sprite.GetWidth();
    const int totalH = sprite.GetHeight();

    if (tileWidth <= 0 || tileHeight <= 0) {
        std::cerr << "[TileSet] Dimensoes invalidas para tileset '" << file << "'" << std::endl;
        tileWidth = tileHeight = 0;
        return;
    }

    columns = totalW / tileWidth;
    const int rows = totalH / tileHeight;
    if (columns <= 0 || rows <= 0) {
        std::cerr << "[TileSet] Grid invalido para '" << file << "'" << std::endl;
        columns = 0;
        tileCount = 0;
        return;
    }

    tileCount = columns * rows;
    sprite.SetFrameCount(columns, rows);
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if (!sprite.IsOpen() || columns <= 0 || tileCount <= 0) return;
    if (index >= static_cast<unsigned>(tileCount)) return;
    sprite.SetFrame(static_cast<int>(index));
    sprite.Render(static_cast<int>(x), static_cast<int>(y), tileWidth, tileHeight);
}