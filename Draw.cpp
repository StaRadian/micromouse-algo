#include "Draw.h"
#include "API.h"

#include <sstream>
#include <iomanip>
#include <windows.h>

#define N_WAY (0b00001000)
#define E_WAY (0b00000100)
#define S_WAY (0b00000010)
#define W_WAY (0b00000001)

// void Draw::Update() {
//     for(int y = 0; y < m_map_size.y; y++) {
//         for(int x = 0; x < m_map_size.x; x++) {
//             SetBlock();
//         }
//     }
// }

void Draw::SetBlock(float weight, int8_t draw_position_map_data, spat::Vec2<int16_t> draw_position) {
    std::string hexString = Float2String(weight);
    API::setText(draw_position.x, draw_position.y, hexString);
    if(draw_position_map_data & N_WAY)
        API::setWall(draw_position.x, draw_position.y, 'n');
    if(draw_position_map_data & E_WAY)
        API::setWall(draw_position.x, draw_position.y, 'e');
    if(draw_position_map_data & S_WAY)
        API::setWall(draw_position.x, draw_position.y, 's');
    if(draw_position_map_data & W_WAY)
        API::setWall(draw_position.x, draw_position.y, 'w');
    Sleep(0.1);
}

std::string Draw::Float2String(float num) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << num;
    return ss.str();
}