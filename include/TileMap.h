// include/TileMap.h
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Component.h"

// apenas forward declaration — a definição real está em include/TileSet.h
class TileSet;

class TileMap : public Component {
public:
    TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);
    void Load(const std::string& file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void Render() override;
    void RenderLayer(int layer);
    void Update(float) override {}
    int GetWidth()  const { return mapWidth;  }
    int GetHeight() const { return mapHeight; }
    int GetDepth()  const { return mapDepth;  }
private:
    std::vector<int> tileMatrix;                // idx = x + y*W + z*W*H
    std::unique_ptr<TileSet> tileSet;           // posse do tileset
    int mapWidth{0}, mapHeight{0}, mapDepth{0};
};