#ifndef Utilities_H_
#define Utilities_H_

#include <cstdint>

namespace spat {
    template <typename T>
    struct Vec2
    {
        T x;
        T y;
    };
    
    // typedef enum
    // {
    //     OK       = 0x00U,
    //     ERROR    = 0x01U,
    //     BUSY     = 0x02U,
    //     TIMEOUT  = 0x03U
    // } Status;
}

#endif