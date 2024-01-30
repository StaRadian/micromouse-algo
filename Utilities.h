#pragma once

#include <cstdint>

namespace spat {
    template <typename T>
    struct vec2
    {
        T x;
        T y;
    };

    struct way {
        static const uint8_t n = 0b00001000; // 북쪽
        static const uint8_t e = 0b00000100; // 동쪽
        static const uint8_t s = 0b00000010; // 남쪽
        static const uint8_t w = 0b00000001; // 서쪽
    };
}