#pragma once

#include "Utilities.h"
#include "Map.h"
#include <queue>
#include <vector>

class Algo {
private:
    Map& m_map;
    spat::vec2<int16_t> m_start_point = {0, 0};
    
    std::queue<spat::vec2<int16_t>> m_queue_position;
    

    uint8_t** m_count_n;
    uint8_t** m_count_ne;
    uint8_t** m_count_e;
    uint8_t** m_count_es;
    uint8_t** m_count_s;
    uint8_t** m_count_sw;
    uint8_t** m_count_w;
    uint8_t** m_count_wn;


    std::vector<uint8_t> m_path;

protected:
    uint8_t** m_mapdata;
    spat::vec2<int16_t> m_map_size;
    uint8_t** m_way;
    float** m_weight;
    float m_weight_max;

public:
    Algo(Map& map);
    ~Algo();
    void SetMap(Map& map);
    void SetEnd(spat::vec2<int16_t> pos, spat::vec2<int16_t> size);
    void SetWeight(spat::vec2<int16_t> pos, float weight) {
        m_queue_position.push(pos);
        m_weight[pos.y][pos.x] = weight;
    }
    float** GetWeightPointer() { return m_weight; }
    void Update();

private:
    float CalculateDistance(std::vector<uint8_t> path);
    void FindPath();
    void Init();
    void Clean();
};