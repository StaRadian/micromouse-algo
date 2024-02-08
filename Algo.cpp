#include "Algo.h"

#include "API.h"

#include <sstream>
#include <iomanip>

Algo::Algo(Map& map)
    : m_map(map){
    Init();
}

Algo::~Algo() {
    Clean();
}

std::string Float2String(float num) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << num;
    return ss.str();
}

void Algo::Update() {

    API::clearAllColor();
    uint16_t count = 0;

    while(m_queue_position.empty() == false) {
        spat::vec2comp<int16_t> vec(m_queue_position.front());
        m_queue_position.pop();
        m_weight_check[vec.y][vec.x] = false;
        float target_weight;
        float weight_temp = m_weight_max;
        uint8_t my_mapdata = m_mapdata[vec.y][vec.x];
        uint8_t my_way = 0;
        uint8_t target_way = 0;

        API::setColor((spat::vec2<int16_t>)vec, 'r');
        count++;

        if(my_mapdata & spat::way::n) {
            target_way = m_way[vec.n.y][vec.n.x];
            target_weight = m_weight[vec.n.y][vec.n.x] + IncreaseWeight(vec.n, spat::way::n);
            if(target_weight < weight_temp) {
                weight_temp = target_weight;
                my_way = spat::way::n;
            }
        }
        if(my_mapdata & spat::way::e) {
            target_way = m_way[vec.e.y][vec.e.x];
            target_weight = m_weight[vec.e.y][vec.e.x] + IncreaseWeight(vec.e, spat::way::e);       
            if(target_weight < weight_temp) { 
                weight_temp = target_weight;
                my_way = spat::way::e;
            }
        }
        if(my_mapdata & spat::way::s) {
            target_way = m_way[vec.s.y][vec.s.x];
            target_weight = m_weight[vec.s.y][vec.s.x] + IncreaseWeight(vec.s, spat::way::s);      
            if(target_weight < weight_temp) { 
                weight_temp = target_weight;
                my_way = spat::way::s;
            }
        }
        if(my_mapdata & spat::way::w) {
            target_way = m_way[vec.w.y][vec.w.x];
            target_weight = m_weight[vec.w.y][vec.w.x] + IncreaseWeight(vec.w, spat::way::w);
            if(target_weight < weight_temp) { 
                weight_temp = target_weight;
                my_way = spat::way::w;
            }
        }

        if(my_way != 0) {
            m_way[vec.y][vec.x] = my_way;
            if(my_way == target_way) {
                spat::vec2 target_vec = vec.Way(target_way);
                m_straight_count[vec.y][vec.x] = m_straight_count[target_vec.y][target_vec.x] + 1;
            } else {
                m_straight_count[vec.y][vec.x] = 0;
            }

            if(m_weight[vec.y][vec.x] != weight_temp) {
                if(m_weight_fix[vec.y][vec.x] == false) {
                    m_weight[vec.y][vec.x] = weight_temp;
                }
                if(my_mapdata & spat::way::n) QueuePositionPush(vec.n);
                if(my_mapdata & spat::way::e) QueuePositionPush(vec.e);
                if(my_mapdata & spat::way::s) QueuePositionPush(vec.s);
                if(my_mapdata & spat::way::w) QueuePositionPush(vec.w);
            }
        }

        API::setText((spat::vec2<int16_t>)vec, Float2String(m_weight[vec.y][vec.x]));
        // API::setText((spat::vec2<int16_t>)vec, std::to_string(m_straight_count[vec.y][vec.x]));
        // Sleep(0.1);
        API::setColor((spat::vec2<int16_t>)vec,'a');
    }

    API::log(std::to_string(count));
}

float Algo::IncreaseWeight(spat::vec2<int16_t> pos, uint8_t way) {
    float result = 1.0;
    if(m_way[pos.y][pos.x] == way) {
        switch (m_straight_count[pos.y][pos.x])
        {
        case 0:
            result = 0.9;
            break;
        
        case 1:
            result = 0.88;
            break;

        case 2:
            result = 0.74;
            break;

        case 3:
            result = 0.56;
            break;

        case 4:
            result = 0.34;
            break;
        default:
            result = 0.2;
        }
    }

    return result;
}

void Algo::QueuePositionPush(spat::vec2<int16_t> vec) {
    if(m_weight_check[vec.y][vec.x] == false && m_weight_fix[vec.y][vec.x] == false) {
        m_queue_position.push(vec);
        m_weight_check[vec.y][vec.x] = true;
    }
}

void Algo::Init() {
    m_mapdata = m_map.GetData();
    m_map_size = m_map.GetSize();
    m_weight_max = m_map_size.x * m_map_size.y;

    m_weight = new float*[m_map_size.x];
    m_way = new uint8_t*[m_map_size.x];
    m_weight_check = new bool*[m_map_size.x];
    m_weight_fix = new bool*[m_map_size.x];
    m_straight_count = new uint16_t*[m_map_size.x];
    
    for (int i = 0; i < m_map_size.x; ++i) {
        m_weight[i] = new float[m_map_size.y];
        m_way[i] = new uint8_t[m_map_size.y];
        m_weight_check[i] = new bool[m_map_size.y];
        m_weight_fix[i] = new bool[m_map_size.y];
        m_straight_count[i] = new uint16_t[m_map_size.y];
    }

    Reset();
}

void Algo::Reset() {
    for (int i = 0; i < m_map_size.y; ++i) {
        for (int j = 0; j < m_map_size.x; ++j) {
            m_weight[i][j] = m_weight_max;
            m_way[i][j] = 0;
            m_weight_check[i][j] = false;
            m_weight_fix[i][j] = false;
            m_straight_count[i][j] = 0;
        }
    }
}

void Algo::Clean() {
    for (int i = 0; i < m_map_size.x; ++i) {
        delete[] m_weight[i];
        delete[] m_way[i];
        delete[] m_weight_check[i];
        delete[] m_weight_fix[i];
        delete[] m_straight_count[i];
    }
    delete[] m_weight;
    delete[] m_way;
    delete[] m_weight_check;
    delete[] m_weight_fix;
    delete[] m_straight_count;
}