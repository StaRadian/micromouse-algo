#pragma once

#include "Utilities.h"

class Moving {
private:
    int16_t& m_turn;
public:
    Moving(int16_t& turn) :m_turn(turn) {}
    void Move();
private:
    void Forward();
    void Right();
    void Left();
    void Back();
};