#pragma once
#include "Utilities.h"

class Map{
private:
    uint8_t** m_map_data;
    const spat::vec2<int16_t> m_map_size;
    bool** m_know_data;
public:
    Map(const spat::vec2<int16_t> map_size);
    ~Map();
    void Update(spat::vec2<int16_t> pos, uint8_t Data);
    uint8_t** GetData() {return m_map_data;}
    const spat::vec2<int16_t> GetSize() { return m_map_size; }
    bool Know(spat::vec2<int16_t> pos) { return m_know_data[pos.y][pos.x]; }
};