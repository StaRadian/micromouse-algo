#pragma once

#include "Algo.h"

class Controller : public Algo {
private:
    spat::vec2<int16_t> m_current_position;
    uint8_t m_current_way;
    uint8_t m_target_way;
    std::queue<spat::vec2<int16_t>> m_queue_way;
    // bool m_find_shortest_way = false;
    // spat::vec2<int16_t> m_unkown_target;
public:
    Controller(Map& map, spat::vec2<int16_t> startpoint, uint8_t current_way)
        : Algo(map), m_current_position(startpoint), m_current_way(current_way) {}
    spat::turn Goto();
    spat::vec2<int16_t> GetCurrentPosition() { return m_current_position; }
    uint8_t GetCurrentWay() { return m_current_way; }
    bool End() { 
        // if(m_find_shortest_way == true) {
        if(m_weight[m_current_position.y][m_current_position.x] == 0) return true;
        else return false;
        // } else {
        //     if(m_weight[m_current_position.y][m_current_position.x] <= 1) return true;
        //     else return false;
        // }
    }
    void Path();
    // bool ShortestWay() { return m_find_shortest_way; }
    // spat::vec2<int16_t> UnknownTarget() { return m_unkown_target; }
private:
    spat::turn Turn();
};