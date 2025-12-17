#include "TileMap.h"
#include "TileSet.h"
#include "GameObject.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSetPtr)
: Component(associated) {
    SetTileSet(tileSetPtr);
    Load(file);
}

void TileMap::Load(const std::string& file) {
    std::ifstream ifs(file);
    if (!ifs) {
        std::cerr << "[TileMap] Nao foi possivel abrir '" << file << "'\n";
        mapWidth = mapHeight = mapDepth = 0;
        tileMatrix.clear();
        return;
    }

    // Lê a primeira linha (ex.: "40,40,2,") e normaliza vírgulas em espaços
    std::string header;
    if (!std::getline(ifs, header)) {
        std::cerr << "[TileMap] Cabecalho ausente em '" << file << "'\n";
        mapWidth = mapHeight = mapDepth = 0;
        tileMatrix.clear();
        return;
    }
    std::replace(header.begin(), header.end(), ',', ' ');
    {
        std::stringstream hs(header);
        if (!(hs >> mapWidth >> mapHeight >> mapDepth)) {
            std::cerr << "[TileMap] Formato invalido para cabecalho em '" << file << "'\n";
            mapWidth = mapHeight = mapDepth = 0;
            tileMatrix.clear();
            return;
        }
    }

    const int total = mapWidth * mapHeight * mapDepth;
    tileMatrix.assign(total, -1);

    // Lê o resto, também aceitando vírgulas
    std::string content, line;
    while (std::getline(ifs, line)) {
        std::replace(line.begin(), line.end(), ',', ' ');
        content.append(line);
        content.push_back(' ');
    }

    std::stringstream ss(content);
    int value = 0, index = 0;
    while (ss >> value && index < total) {
        tileMatrix[index++] = value;
    }
    if (index < total) {
        std::cerr << "[TileMap] Valores insuficientes em '" << file << "'\n";
    }
}

void TileMap::SetTileSet(TileSet* tileSetPtr) {
    tileSet.reset(tileSetPtr);
}

int& TileMap::At(int x, int y, int z) {
    static int dummy = -1;
    if (x < 0 || y < 0 || z < 0 || x >= mapWidth || y >= mapHeight || z >= mapDepth) {
        std::cerr << "[TileMap] Acesso fora: (" << x << ',' << y << ',' << z << ")\n";
        return dummy;
    }
    const int idx = x + y * mapWidth + z * mapWidth * mapHeight;
    return tileMatrix[idx];
}

void TileMap::Render() {
    if (!tileSet) return;
    for (int layer = 0; layer < mapDepth; ++layer) {
        RenderLayer(layer);
    }
}

void TileMap::RenderLayer(int layer) {
    if (!tileSet) return;
    if (layer < 0 || layer >= mapDepth) return;
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            const int tile = At(x, y, layer);
            if (tile >= 0) {
                const float posX = associated.box.x + x * tileSet->GetTileWidth();
                const float posY = associated.box.y + y * tileSet->GetTileHeight();
                tileSet->RenderTile((unsigned)tile, posX, posY);
            }
        }
    }
}
