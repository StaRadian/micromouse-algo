#include "Moving.h"
#include "API.h"

void Moving::Move() {
    switch (m_turn)
    {
    case spat::turn::forward:
        Forward();
        break;
    case spat::turn::right:
        Right();
        break;
    case spat::turn::left:
        Left();
        break;
    case spat::turn::back:
        Back();
        break;
    case spat::turn::r90:
        R90();
        break;
    case spat::turn::l90:
        L90();
        break;
    case spat::turn::stop:
        break;
    default:
        API::log("turn error!");
        break;
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

void Moving::R90() {
    API::moveForwardHalf();
    API::turnRight45();
    API::moveForwardHalf();
    API::turnRight45();
    API::moveForwardHalf();

}

void Moving::L90() {
    API::moveForwardHalf();
    API::turnLeft45();
    API::moveForwardHalf();
    API::turnLeft45();
    API::moveForwardHalf();

}