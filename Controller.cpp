#include "Controller.h"

#include "API.h"

spat::turn Controller::Goto() {
    m_target_way = m_way[m_current_position.y][m_current_position.x];
    uint8_t my_mapdata = m_mapdata[m_current_position.y][m_current_position.x];
    if(!(my_mapdata & m_target_way)) {
        SetPush(m_current_position);
        Update();
        m_target_way = m_way[m_current_position.y][m_current_position.x];
    }
    Path();
    return Turn();
}

void Controller::Path() {
    spat::vec2<int16_t> vec = m_current_position;
    while (!m_queue_way.empty()) {
        m_queue_way.pop();
    }
    while(m_map.Know(vec)) {
        m_queue_way.push(vec);

        API::setColor((spat::vec2<int16_t>)vec,'c');
        // Sleep(1);

        switch (m_way[vec.y][vec.x])
        {
        case spat::way::n:
            vec.y ++;
            break;
        case spat::way::e:
            vec.x ++;
            break;
        case spat::way::s:
            vec.y --;
            break;
        case spat::way::w:
            vec.x --;
            break;
        }
        if(m_weight[vec.y][vec.x] == 0) {
            // m_find_shortest_way = true;
            break;
        }
        // else m_find_shortest_way = false;
    }
    // m_unkown_target = vec;
}

spat::turn Controller::Turn() {
    spat::turn result = spat::turn::stop;
    uint8_t way = m_current_way + (m_current_way << 4);
    m_current_way = m_target_way;
    

    switch (m_target_way)
    {
    case spat::way::n:
        m_current_position.y += 1;
        break;

    case spat::way::e:
        m_current_position.x += 1;
        break;
    case spat::way::s:
    
        m_current_position.y -= 1;
        break;

    case spat::way::w:
        m_current_position.x -= 1;
        break;
    
    default:
        break;
    }

    if(way & m_target_way) {
        result = spat::turn::forward;
    } else if(way & (m_target_way << 1)){
        result = spat::turn::right;
    } else if(way & (m_target_way << 3)) {
        result = spat::turn::left;
    } else if(way & (m_target_way << 2)) {
        result = spat::turn::back;
    }
    return result;
}