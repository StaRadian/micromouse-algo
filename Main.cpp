#include "API.h"
#include "Draw.h"

#include "Moving.h"
#include "Algo.h"

#define N_WAY (0b00001000)
#define E_WAY (0b00000100)
#define S_WAY (0b00000010)
#define W_WAY (0b00000001)

#define N_DIR (0)
#define E_DIR (1)
#define S_DIR (2)
#define W_DIR (3)

int main(int argc, char* argv[]) {
    API::log("Start");

    
    /////////////////////////////////
    const int16_t map_size_x = 16;
    const int16_t map_size_y = 16;

    Draw draw; 
    Algo algo({map_size_x, map_size_y});

    algo.SetWeight({7,7},0);
    algo.SetWeight({7,8},0);
    algo.SetWeight({8,8},0);
    algo.SetWeight({8,7},0);
    /////////////////////////////////

    uint8_t map_data[map_size_y][map_size_x] = {0};

    spat::Vec2<int16_t> current_position = {0, 0};
    uint8_t mouse_direction = 0;

    if(API::wallFront() == true) {
        map_data[current_position.y][current_position.x] |= 0b10001000 >> mouse_direction;
    } else {
        map_data[current_position.y][current_position.x] &= ~(0b10001000 >> mouse_direction);
    }
    if(API::wallRight() == true) {
        map_data[current_position.y][current_position.x] |= 0b01000100 >> mouse_direction;
    } else {
        map_data[current_position.y][current_position.x] &= ~(0b01000100 >> mouse_direction);
    }
    if(API::wallLeft() == true) {
        map_data[current_position.y][current_position.x] |= 0b00010001 >> mouse_direction;
    } else {
        map_data[current_position.y][current_position.x] &= ~(0b00010001 >> mouse_direction);
    }

    //////////////////////////////////

    algo.Update();

    for(int16_t y = 0; y < map_size_y; y++) {
        for(int16_t x = 0; x < map_size_x; x++) {      
            draw.SetBlock(algo.GetWeight({x, y}), map_data[x][y], {x,y});
        }
    }

    current_position.x = 0;
    current_position.y = 1;

    API::moveForward();

    if(API::wallFront() == true) {
        map_data[current_position.y][current_position.x] |= 0b10001000 >> mouse_direction;
    } else {
        map_data[current_position.y][current_position.x] &= ~(0b10001000 >> mouse_direction);
    }
    if(API::wallRight() == true) {
        map_data[current_position.y][current_position.x] |= 0b01000100 >> mouse_direction;
    } else {
        map_data[current_position.y][current_position.x] &= ~(0b01000100 >> mouse_direction);
    }
    if(API::wallLeft() == true) {
        map_data[current_position.y][current_position.x] |= 0b00010001 >> mouse_direction;
    } else {
        map_data[current_position.y][current_position.x] &= ~(0b00010001 >> mouse_direction);
    }

    for(int16_t y = 0; y < map_size_y; y++) {
        for(int16_t x = 0; x < map_size_x; x++) {      
            draw.SetBlock(algo.GetWeight({x, y}), map_data[y][x], {x,y});
        }
    }
    
    API::moveForward();
    API::turnRight();

    mouse_direction = 1;

    current_position.x = 0;
    current_position.y = 2;

    if(API::wallFront() == true) {
        map_data[current_position.y][current_position.x] |= 0b10001000 >> mouse_direction;
    } else {
        map_data[current_position.y][current_position.x] &= ~(0b10001000 >> mouse_direction);
    }
    if(API::wallRight() == true) {
        map_data[current_position.y][current_position.x] |= 0b01000100 >> mouse_direction;
    } else {
        map_data[current_position.y][current_position.x] &= ~(0b01000100 >> mouse_direction);
    }
    if(API::wallLeft() == true) {
        map_data[current_position.y][current_position.x] |= 0b00010001 >> mouse_direction;
    } else {
        map_data[current_position.y][current_position.x] &= ~(0b00010001 >> mouse_direction);
    }

    for(int16_t y = 0; y < map_size_y; y++) {
        for(int16_t x = 0; x < map_size_x; x++) {      
            draw.SetBlock(algo.GetWeight({x, y}), map_data[y][x], {x,y});
        }
    }

    API::moveForward();

    current_position.x = 1;
    current_position.y = 2;

    if(API::wallFront() == true) {
        map_data[current_position.y][current_position.x] |= 0b10001000 >> mouse_direction;
    } else {
        map_data[current_position.y][current_position.x] &= ~(0b10001000 >> mouse_direction);
    }
    if(API::wallRight() == true) {
        map_data[current_position.y][current_position.x] |= 0b01000100 >> mouse_direction;
    } else {
        map_data[current_position.y][current_position.x] &= ~(0b01000100 >> mouse_direction);
    }
    if(API::wallLeft() == true) {
        map_data[current_position.y][current_position.x] |= 0b00010001 >> mouse_direction;
    } else {
        map_data[current_position.y][current_position.x] &= ~(0b00010001 >> mouse_direction);
    }

    for(int16_t y = 0; y < map_size_y; y++) {
        for(int16_t x = 0; x < map_size_x; x++) {      
            draw.SetBlock(algo.GetWeight({x, y}), map_data[y][x], {x,y});
        }
    }
}