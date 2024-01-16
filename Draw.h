#ifndef DRAW_H_
#define DRAW_H_

#include "Utilities.h"
#include <string>

class Draw {
private:
    spat::Vec2<int16_t> m_map_size;
    
public:
    Draw(spat::Vec2<int16_t> map_size = {16, 16})
        : m_map_size(map_size) {}
    // void Update();
    void SetBlock(float weight, int8_t draw_position_map_data, spat::Vec2<int16_t> draw_position);
private:
    std::string Float2String(float num);
};
#endif