#pragma once

#include <string>
#include "windows.h"
#include "Utilities.h"

class API {

public:

    static int mazeWidth();
    static int mazeHeight();

    static bool wallFront();
    static bool wallRight();
    static bool wallLeft();

    static void moveForward(int distance = 1);
    static void moveForwardHalf(int numHalfSteps = 1);
    static void turnRight();
    static void turnLeft();
    static void turnRight45();
    static void turnLeft45();

    static void setWall(int x, int y, char direction);
    static void clearWall(int x, int y, char direction);

    static void setColor(int x, int y, char color);
    static void clearColor(int x, int y);
    static void clearAllColor();

    static void setText(int x, int y, const std::string& text);
    static void clearText(int x, int y);
    static void clearAllText();

    static bool wasReset();
    static void ackReset();

    static void log(const std::string& text);

    template <typename T>
    static void setWall(spat::vec2<T> pos, char direction) { setWall((int)pos.x, (int)pos.y, direction); }
    
    template <typename T>
    static void clearWall(spat::vec2<T> pos, char direction) { clearWall((int)pos.x, (int)pos.y, direction); }
    
    template <typename T>
    static void setColor(spat::vec2<T> pos, char color) { setColor((int)pos.x, (int)pos.y, color); }
    
    template <typename T>
    static void clearColor(spat::vec2<T> pos) { clearColor((int)pos.x, (int)pos.y); }
    
    template <typename T>
    static void setText(spat::vec2<T> pos, const std::string& text) { setText((int)pos.x, (int)pos.y, text); }
    
    template <typename T>
    static void clearText(spat::vec2<T> pos) { clearText((int)pos.x, (int)pos.y); }
};
