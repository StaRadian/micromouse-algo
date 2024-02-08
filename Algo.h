#pragma once

#include "Utilities.h"
#include "Map.h"
#include <queue>
#include <vector>

class Algo {
private:
    std::queue<spat::vec2<int16_t>> m_queue_position;
    spat::vec2<int16_t> m_map_size;

    bool** m_weight_check;
    bool** m_weight_fix;
    float m_weight_max;

    uint16_t** m_straight_count;

protected:
    float** m_weight;
    Map& m_map;
    uint8_t** m_mapdata;
    uint8_t** m_way;

public:
    Algo(Map& map);
    ~Algo();
    // void SetMap(Map& map);
    // void SetEnd(spat::vec2<int16_t> pos, spat::vec2<int16_t> size);
    void SetPush(spat::vec2<int16_t> pos) {
        QueuePositionPush(pos);
    }
    void SetEndPoint(spat::vec2<int16_t> pos) {
        spat::vec2comp<int16_t> vec(pos);
        m_queue_position.push(pos);
        m_weight[pos.y][pos.x] = 0;
        m_weight_fix[pos.y][pos.x] = true;
        uint8_t my_mapdata = m_mapdata[pos.y][pos.x];
        if(my_mapdata & spat::way::n) QueuePositionPush(vec.n);
        if(my_mapdata & spat::way::e) QueuePositionPush(vec.e);
        if(my_mapdata & spat::way::s) QueuePositionPush(vec.s);
        if(my_mapdata & spat::way::w) QueuePositionPush(vec.w);
    }
    float** GetWeightPointer() { return m_weight; }
    void Update();
    uint8_t** GetWay(spat::vec2<int16_t> vec) { return m_way; }
    void Reset();

private:
    float IncreaseWeight(spat::vec2<int16_t> pos, uint8_t way);
    void QueuePositionPush(spat::vec2<int16_t> vec);
    void Init();
    void Clean();
};