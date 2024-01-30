#pragma once

#include "Algo.h"

class Controller : public Algo {
    spat::vec2<int16_t> m_current_position;
    uint8_t m_current_way;
    uint8_t m_target_way;
    bool m_stop_flag = true;
public:
    Controller(Map& map, spat::vec2<int16_t> startpoint, uint8_t current_way)
        : Algo(map), m_current_position(startpoint), m_current_way(current_way) {}
    void Goto();
    spat::vec2<int16_t> GetCurrentPosition() { return m_current_position; }
    uint8_t GetCurrentWay() { return m_current_way; }
    int16_t Turn();
private:
};