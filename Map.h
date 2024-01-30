#pragma once
#include "Utilities.h"

class Map{
private:
    uint8_t** m_mapdata;
    const spat::vec2<int16_t> m_map_size;
public:
    Map(const spat::vec2<int16_t> map_size);
    ~Map();
    void Update(spat::vec2<int16_t> pos, uint8_t Data);
    uint8_t** GetData() {return m_mapdata;}
    const spat::vec2<int16_t> GetSize() {return m_map_size;}
};