#include "Draw.h"
#include "API.h"

#include <sstream>
#include <iomanip>
#include <windows.h>

void Draw::Update() {
    for(int16_t y = 0; y < m_map_size.y; y++) {
        for(int16_t x = 0; x < m_map_size.x; x++) {
            SetBlock(m_weight[y][x], m_mapdata[y][x], {x,y});
        }
    }
}

void Draw::SetBlock(float weight, uint8_t draw_position_map_data, spat::vec2<int16_t> draw_position) {
    std::string str = Float2String(weight);
    // API::setText(draw_position, str);
    if((~draw_position_map_data & spat::way::n))
        API::setWall(draw_position, 'n');
    if((~draw_position_map_data & spat::way::e))
        API::setWall(draw_position, 'e');
    if((~draw_position_map_data & spat::way::s))
        API::setWall(draw_position, 's');
    if((~draw_position_map_data & spat::way::w))
        API::setWall(draw_position, 'w');
}

std::string Draw::Float2String(float num) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << num;
    return ss.str();
}