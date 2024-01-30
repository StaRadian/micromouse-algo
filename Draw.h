#pragma once

#include "Utilities.h"
#include "Map.h"
#include <string>

class Draw {
private:
    spat::vec2<int16_t> m_map_size;
    float** m_weight;
    uint8_t** m_mapdata;
    
public:
    Draw(float** weight, Map& map)
        : m_weight(weight), m_map_size(map.GetSize()), m_mapdata(map.GetData()) {

        }
    void Update();
    void SetBlock(float weight, uint8_t draw_position_map_data, spat::vec2<int16_t> draw_position);
private:
    std::string Float2String(float num);
};