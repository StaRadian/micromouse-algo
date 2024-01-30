#include "Controller.h"

#include "API.h"

void Controller::Goto() {
    uint8_t mapdata = m_mapdata[m_current_position.y][m_current_position.x];
    // float small_weight = m_weight_max;
    m_stop_flag = false;
    API::log("x: " + std::to_string(m_current_position.x) + ", y: " + std::to_string(m_current_position.y) + ", " + std::to_string(m_way[m_current_position.y][m_current_position.x]) + ", " + std::to_string(mapdata));
    if(m_way[m_current_position.y][m_current_position.x] & (spat::way::n & mapdata)) {
        m_target_way = spat::way::n;
        m_current_position.y ++;
    } else if(m_way[m_current_position.y][m_current_position.x] & spat::way::e & mapdata) {
        m_target_way = spat::way::e;
        m_current_position.x ++;
    } else if(m_way[m_current_position.y][m_current_position.x] & spat::way::s & mapdata) {
        m_target_way = spat::way::s;
        m_current_position.y --;
    } else if(m_way[m_current_position.y][m_current_position.x] & spat::way::w & mapdata) {
        m_target_way = spat::way::w;
        m_current_position.x --;
    } else {
        for (int i = 0; i < m_map_size.y; ++i) {
            for (int j = 0; j < m_map_size.x; ++j) {
                m_way[i][j] = 0b00000000;
            }
        }
        SetWeight({7,7}, 0.0);
        SetWeight({7,8}, 0.0);
        SetWeight({8,8}, 0.0);
        SetWeight({8,7}, 0.0);
        API::log("Update");
        Update();
        if(m_way[m_current_position.y][m_current_position.x] & spat::way::n) {
            m_target_way = spat::way::n;
            m_current_position.y ++;
        } else if(m_way[m_current_position.y][m_current_position.x] & spat::way::e) {
            m_target_way = spat::way::e;
            m_current_position.x ++;
        } else if(m_way[m_current_position.y][m_current_position.x] & spat::way::s) {
            m_target_way = spat::way::s;
            m_current_position.y --;
        } else if(m_way[m_current_position.y][m_current_position.x] & spat::way::w) {
            m_target_way = spat::way::w;
            m_current_position.x --;
        } else m_stop_flag = true;
    }
}

int16_t Controller::Turn() {
    int16_t result = 720;
    uint8_t way = m_current_way + (m_current_way << 4);
    m_current_way = m_target_way;

    if(way & m_target_way) {
        result = 0;
    } else if(way & (m_target_way << 1)){
        result = 90;
    } else if(way & (m_target_way << 3)) {
        result = -90;
    } else if(way & (m_target_way << 2)) {
        result = 180;
    } 
    if (m_stop_flag) {
        API::log("Error");
        result = 720;
    }
    return result;
}