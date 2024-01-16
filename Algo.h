#ifndef ALGO_H_
#define ALGO_H_

#include "Utilities.h"
#include <queue>
#include <string>

class Algo {
private:
    const spat::Vec2<int16_t> m_map_size;
    float** m_weight;
    bool** m_weight_check;
    spat::Vec2<int16_t> vec_p;
    spat::Vec2<int16_t> vec_n;
    std::queue<spat::Vec2<int16_t>> m_update_position;
public:
    Algo(spat::Vec2<int16_t> map_size);
    ~Algo();
    void Update();
    void SetWeight(spat::Vec2<int16_t> pos, float weight) {
        m_update_position.push(pos);
        m_weight[pos.y][pos.x] = weight;
    }
    float GetWeight(spat::Vec2<int16_t> pos) {
        return m_weight[pos.y][pos.x];
    }
private:
};

#endif