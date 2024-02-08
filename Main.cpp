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
    spat::turn turn;
    Moving mov(turn);

    turn = spat::turn::r90;
    mov.Move();
    turn = spat::turn::l90;
    mov.Move();

    // while(true) {
    //     API::log("Running");
    //     ctl.Reset();
    //     ctl.SetEndPoint({7,7});
    //     ctl.SetEndPoint({7,8});
    //     ctl.SetEndPoint({8,8});
    //     ctl.SetEndPoint({8,7});
    //     ctl.Update();
    //     // ctl.Path();

    //     while(ctl.End() != true) {
    //         map.Update(ctl.GetCurrentPosition(), sensorData(ctl.GetCurrentWay()));
    //         draw.Update();

    //         turn = ctl.Goto();
    //         mov.Move();
    //     }

    //     API::log("End");

    //     ctl.Reset();

    //     ctl.SetEndPoint({0,0});

    //     ctl.Update();
    //     // ctl.Path();

    //     API::log("Returning");

    //     while(ctl.End() != true) {
    //         map.Update(ctl.GetCurrentPosition(), sensorData(ctl.GetCurrentWay()));
    //         draw.Update();

    //         turn = ctl.Goto();
    //         mov.Move();
    //     }
    //     API::log("End returning");
    // }

}