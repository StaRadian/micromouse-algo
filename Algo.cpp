#include "Algo.h"

#include "API.h"

Algo::Algo(spat::Vec2<int16_t> map_size): m_map_size(map_size) {
    m_weight = new float*[m_map_size.x];
    m_weight_check = new bool*[m_map_size.x];
    for (int i = 0; i < m_map_size.x; ++i) {
        m_weight[i] = new float[m_map_size.y];
        m_weight_check[i] = new bool[m_map_size.y];
    }
    for (int i = 0; i < m_map_size.y; ++i) {
        for (int j = 0; j < m_map_size.x; ++j) {
            m_weight[i][j] = 100000;
            m_weight_check[i][j] = false;
        }
    }
}

Algo::~Algo() {
    delete[] m_weight, m_weight_check;
}

void Algo::Update() {
    for(int i = 0; i<10000; i++) {
        spat::Vec2 vec = m_update_position.front();
        if(m_update_position.size() == 0)
            return;

        m_update_position.pop();
        m_weight_check[vec.x][vec.y] = false;
        vec_n.x = vec.x-1;
        if(vec_n.x >= 0) {
            if(m_weight[vec.y][vec.x] < m_weight[vec.y][vec_n.x]) {
                m_weight[vec.y][vec_n.x] = m_weight[vec.y][vec.x] + 1;
                if(m_weight_check[vec.y][vec_n.x] == false) {
                    m_update_position.push({vec_n.x, vec.y});
                    m_weight_check[vec.y][vec_n.x] = true;
                }
            }
        }
        vec_p.x = vec.x+1;
        if(vec_p.x < m_map_size.x) {
            if(m_weight[vec.y][vec.x] < m_weight[vec.y][vec_p.x]) {
                m_weight[vec.y][vec_p.x] = m_weight[vec.y][vec.x] + 1;
                if(m_weight_check[vec.y][vec_p.x] == false) {
                    m_update_position.push({vec_p.x, vec.y});
                    m_weight_check[vec.y][vec_p.x] = true;
                }
            }
        }
        vec_n.y = vec.y-1;
        if(vec_n.y >= 0) {
            if(m_weight[vec.y][vec.x] < m_weight[vec_n.y][vec.x]) {
                m_weight[vec_n.y][vec.x] = m_weight[vec.y][vec.x] + 1;
                if(m_weight_check[vec_n.y][vec.x] == false) {
                    m_update_position.push({vec.x, vec_n.y});
                    m_weight_check[vec_n.y][vec.x] = true;
                }
            }
        }
        vec_p.y = vec.y+1;
        if(vec_p.y < m_map_size.y) {
            if(m_weight[vec.y][vec.x] < m_weight[vec_p.y][vec.x]) {
                m_weight[vec_p.y][vec.x] = m_weight[vec.y][vec.x] + 1;
                if(m_weight_check[vec_p.y][vec.x] == false) {
                    m_update_position.push({vec.x, vec_p.y});
                    m_weight_check[vec_p.y][vec.x] = true;
                }
            }
        }
    }
    return;
}

