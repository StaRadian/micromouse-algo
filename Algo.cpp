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
    while(true) {
        if(m_queue_position.empty() == false) {
            spat::vec2<int16_t> pos = m_queue_position.front();
            m_queue_position.pop();

            float weight = m_weight[pos.y][pos.x];
            
            uint8_t count_ne = m_count_ne[pos.y][pos.x];
            uint8_t count_es = m_count_es[pos.y][pos.x];
            uint8_t count_sw = m_count_sw[pos.y][pos.x];
            uint8_t count_wn = m_count_wn[pos.y][pos.x];

            // API::log("x: " + std::to_string(pos.x) + ", y: " + std::to_string(pos.x) + ", " + std::to_string(m_mapdata[pos.y][pos.x]));
            if(m_mapdata[pos.y][pos.x] & spat::way::n) {
                uint8_t count_n = m_count_n[pos.y][pos.x];
                pos.y ++;
                // API::log("N x: " + std::to_string(pos.x) + ", y: " + std::to_string(pos.x));
                if(weight < m_weight[pos.y][pos.x]) {
                    m_queue_position.push(pos);

                    m_count_n[pos.y][pos.x] = count_n + 1;
                    
                    m_weight[pos.y][pos.x] = weight + 1;

                    API::setColor(pos, 'b');
                    API::setText(pos, Float2String(m_weight[pos.y][pos.x]));
                    m_way[pos.y][pos.x] |= spat::way::s;
                }
                pos.y --;
            }
            if(m_mapdata[pos.y][pos.x] & spat::way::e) {
                uint8_t count_e = m_count_e[pos.y][pos.x];
                pos.x ++;
                // API::log("E x: " + std::to_string(pos.x) + ", y: " + std::to_string(pos.x));
                if(weight < m_weight[pos.y][pos.x]) {
                    m_queue_position.push(pos);

                    m_count_e[pos.y][pos.x] = count_e + 1;

                    m_weight[pos.y][pos.x] = weight + 1;

                    API::setColor(pos, 'b');
                    API::setText(pos, Float2String(m_weight[pos.y][pos.x]));
                    m_way[pos.y][pos.x] |= spat::way::w;
                }
                pos.x --;
            }
            if(m_mapdata[pos.y][pos.x] & spat::way::s) {
                uint8_t count_s = m_count_s[pos.y][pos.x];
                pos.y --;
                // API::log("S x: " + std::to_string(pos.x) + ", y: " + std::to_string(pos.x));
                if(weight < m_weight[pos.y][pos.x]) {
                    m_queue_position.push(pos);

                    m_count_s[pos.y][pos.x] = count_s + 1;

                    m_weight[pos.y][pos.x] = weight + 1;

                    API::setColor(pos, 'b');
                    API::setText(pos, Float2String(m_weight[pos.y][pos.x]));
                    m_way[pos.y][pos.x] |= spat::way::n;
                }
                pos.y ++;
            }
            if(m_mapdata[pos.y][pos.x] & spat::way::w) {
                uint8_t count_w = m_count_w[pos.y][pos.x];
                pos.x --;
                // API::log("W x: " + std::to_string(pos.x) + ", y: " + std::to_string(pos.x));
                if(weight < m_weight[pos.y][pos.x]) {
                    m_queue_position.push(pos);

                    m_count_w[pos.y][pos.x] = count_w + 1;

                    m_weight[pos.y][pos.x] = weight + 1;

                    API::setColor(pos, 'b');
                    API::setText(pos, Float2String(m_weight[pos.y][pos.x]));
                    m_way[pos.y][pos.x] |= spat::way::e;
                }
                pos.x ++;
            }

            API::setColor(pos, 'r');
            API::setText(pos, std::to_string(m_way[pos.y][pos.x]));
            // API::setText(pos, std::to_string(m_count_n[pos.y][pos.x]));
            Sleep(1);
            API::clearColor(pos);
        } else break;
    }

    // CreateWay();
    // FindPath();
    // API::log("end");

    // API::clearAllColor();
    // Sleep(10);
}

void Algo::FindPath() {
    std::vector<std::vector<uint8_t>> path;

    // API::log("distance: " + std::to_string(Algo::CalculateDistance(path)));
}

float Algo::CalculateDistance(std::vector<uint8_t> path) {
    float distance = path.size();
    return distance;
}

void Algo::SetEnd(spat::vec2<int16_t> pos, spat::vec2<int16_t> size) {
    spat::vec2<int16_t> target_pos;
    for (int i = 0; i < size.y; ++i) {
        target_pos.y = pos.y + i;
        for (int j = 0; j < size.x; ++j) {
            target_pos.x = pos.x + j;
            m_queue_position.push(target_pos);
            m_way[target_pos.y][target_pos.x] |= 0x0F;
            m_weight[target_pos.y][target_pos.x] = 0.0;
        }
    }
    for (int i = 0; i < size.x; i++) {
        m_way[0][pos.x + i] &= ~spat::way::s;
        m_way[size.y - 1][pos.x + i] &= ~spat::way::n;
    }
    for (int i = 0; i < size.y; i++) {
        m_way[pos.y + i][0] &= ~spat::way::w;
        m_way[pos.y + i][size.x - 1] &= ~spat::way::e;
    }
    
}

void Algo::Init() {
    m_map_size = m_map.GetSize();
    m_mapdata = m_map.GetData();
    m_weight_max = m_map_size.x * m_map_size.y;
    m_weight = new float*[m_map_size.x];
    m_way = new uint8_t*[m_map_size.x];

    m_count_n = new uint8_t*[m_map_size.x];
    m_count_e = new uint8_t*[m_map_size.x];
    m_count_s = new uint8_t*[m_map_size.x];
    m_count_w = new uint8_t*[m_map_size.x];
    m_count_ne = new uint8_t*[m_map_size.x];
    m_count_es = new uint8_t*[m_map_size.x];
    m_count_sw = new uint8_t*[m_map_size.x];
    m_count_wn = new uint8_t*[m_map_size.x];
    
    for (int i = 0; i < m_map_size.x; ++i) {
        m_weight[i] = new float[m_map_size.y];
        m_way[i] = new uint8_t[m_map_size.y];

        m_count_n[i] = new uint8_t[m_map_size.x];
        m_count_e[i] = new uint8_t[m_map_size.x];
        m_count_s[i] = new uint8_t[m_map_size.x];
        m_count_w[i] = new uint8_t[m_map_size.x];
        m_count_ne[i] = new uint8_t[m_map_size.x];
        m_count_es[i] = new uint8_t[m_map_size.x];
        m_count_sw[i] = new uint8_t[m_map_size.x];
        m_count_wn[i] = new uint8_t[m_map_size.x];
    }
    for (int i = 0; i < m_map_size.y; ++i) {
        for (int j = 0; j < m_map_size.x; ++j) {
            m_weight[i][j] = m_weight_max;
            m_way[i][j] = 0b00000000;
            m_count_n[i][j] = 0;
            m_count_e[i][j] = 0;
            m_count_s[i][j] = 0;
            m_count_w[i][j] = 0;
            m_count_ne[i][j] = 0;
            m_count_es[i][j] = 0;
            m_count_sw[i][j] = 0;
            m_count_wn[i][j] = 0;
        }
    }
}

void Algo::Clean() {
    for (int i = 0; i < m_map_size.x; ++i) {
        delete[] m_weight[i];
        delete[] m_way[i];
        delete[] m_weight[i];
    }
    delete[] m_weight;
    delete[] m_way;
    delete[] m_weight;
}