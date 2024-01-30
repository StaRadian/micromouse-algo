#include "Map.h"
#include "API.h"

Map::Map(const spat::vec2<int16_t> map_size)
    : m_map_size(map_size){
    m_mapdata = new uint8_t*[m_map_size.x];
    
    for (int i = 0; i < m_map_size.x; ++i) {
        m_mapdata[i] = new uint8_t[m_map_size.y];
    }
    for (int i = 0; i < m_map_size.y; ++i) {
        for (int j = 0; j < m_map_size.x; ++j) {
            m_mapdata[i][j] = 0xFF;
        }
    }
    for (int i = 0; i < m_map_size.x; ++i) {
        m_mapdata[0][i] &= ~spat::way::s;
        m_mapdata[m_map_size.x - 1][i] &= ~spat::way::n;
    }
    for (int i = 0; i < m_map_size.y; ++i) {
        m_mapdata[i][0] &= ~spat::way::w;
        m_mapdata[i][m_map_size.y - 1] &= ~spat::way::e;
    }
}

Map::~Map() {
    for (int i = 0; i < m_map_size.x; ++i) {
        delete[] m_mapdata[i];
    }
    delete[] m_mapdata;
}

void Map::Update(spat::vec2<int16_t> pos, uint8_t data) {
    m_mapdata[pos.y][pos.x] = ~data;
    spat::vec2<int16_t> pos_p = {(int16_t)(pos.x + 1), (int16_t)(pos.y + 1)};
    spat::vec2<int16_t> pos_n = {(int16_t)(pos.x - 1), (int16_t)(pos.y - 1)};

    if(pos_p.y < m_map_size.y) {    //N
        if(m_mapdata[pos.y][pos.x] & spat::way::n)
            m_mapdata[pos_p.y][pos.x] |= spat::way::s;
        else
            m_mapdata[pos_p.y][pos.x] &= ~spat::way::s;
    } else {
        m_mapdata[pos.y][pos.x] &= ~spat::way::n;
    }
    if(pos_p.x < m_map_size.x) {    //E
        if(m_mapdata[pos.y][pos.x] & spat::way::e)
            m_mapdata[pos.y][pos_p.x] |= spat::way::w;
        else
            m_mapdata[pos.y][pos_p.x] &= ~spat::way::w;
    } else {
        m_mapdata[pos.y][pos.x] &= ~spat::way::e;
    }
    if(pos_n.y >= 0) {              //S
        if(m_mapdata[pos.y][pos.x] & spat::way::s)
            m_mapdata[pos_n.y][pos.x] |= spat::way::n;
        else
            m_mapdata[pos_n.y][pos.x] &= ~spat::way::n;
    } else {
        m_mapdata[pos.y][pos.x] &= ~spat::way::s;
    }
    if(pos_n.x >= 0) {              //W
        if(m_mapdata[pos.y][pos.x] & spat::way::w)
            m_mapdata[pos.y][pos_n.x] |= spat::way::e;
        else
            m_mapdata[pos.y][pos_n.x] &= ~spat::way::e;
    } else {
        m_mapdata[pos.y][pos.x] &= ~spat::way::w;
    }
}