#include "API.h"
#include "Draw.h"
#include "Moving.h"

#include "Map.h"
#include "Controller.h"

uint8_t sensorData(uint8_t way) {
    uint8_t data = 0x00;
    way += (way << 4);
    if(API::wallFront() == true) {
        data |= way;
    } else {
        data &= ~way;
    }
    if(API::wallRight() == true) {
        data |= (way >> 1);
    } else {
        data &= ~(way >> 1);
    }
    if(API::wallLeft() == true) {
        data |= (way >> 3);
    } else {
        data &= ~(way >> 3);
    }
    data &= 0x0F;
    return data;
}

int main(int argc, char* argv[]) {
    API::log("Start");
    
    /////////////////////////////////
    Map map({16, 16});

    Controller ctl(map, {0, 0}, spat::way::n);
    
    Draw draw(ctl.GetWeightPointer(), map);
    int16_t turn;
    Moving mov(turn);

/////////////////////
    // {
    //     map_data[0][0] = 0b0111;
    //     map_data[7][7] = 0b0010;
    //     map_data[7][8] = 0b0110;
    //     map_data[8][7] = 0b1001;
    //     map_data[8][8] = 0b1100;
    // }
/////////////////////

    ctl.SetEnd({7, 7}, {2, 2});
    draw.Update();
    ctl.Update();
    
    draw.Update();
    while(1);

    // draw.Update();
    
    // uint8_t way = ctl.GetCurrentWay();
    // API::setColor(pos.x, pos.y, 'y');
    // ctl.Goto();
    // turn = ctl.Turn();
    // mov.Move();

    while(true) {
        map.Update(ctl.GetCurrentPosition(), sensorData(ctl.GetCurrentWay()));
        // API::log(std::to_string(map.GetCurrentWay()));
        draw.Update();
        ctl.Goto();
        turn = ctl.Turn();
        mov.Move();
    }
    
    API::log("End");
    Sleep(100);
}