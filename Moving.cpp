#include "Moving.h"
#include "API.h"

void Moving::Move() {
    if(m_turn == 0) {
        Forward();
    } else if(m_turn == 90) {
        Right();
    } else if(m_turn == -90) {
        Left();
    } else if(m_turn == 180 || m_turn == -180) {
        Back();
    }
}

void Moving::Forward() {
    API::moveForward();
}

void Moving::Right() {
    API::turnRight();
    API::moveForward();
}

void Moving::Left() {
    API::turnLeft();
    API::moveForward();
}

void Moving::Back() {
    API::turnRight();
    API::turnRight();
    API::moveForward();
}