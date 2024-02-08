#pragma once

#include "Utilities.h"

class Moving {
private:
    spat::turn& m_turn;
public:
    Moving(spat::turn& turn) :m_turn(turn) {}
    void Move();
private:
    void Forward();
    void Right();
    void Left();
    void Back();
    void R90();
    void L90();
};