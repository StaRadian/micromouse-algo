#pragma once

#include <cstdint>

namespace spat {
    struct way {
        static const uint8_t n = 0b00001000; // 북쪽
        static const uint8_t e = 0b00000100; // 동쪽
        static const uint8_t s = 0b00000010; // 남쪽
        static const uint8_t w = 0b00000001; // 서쪽
    };

    template <typename T>
    struct vec2 {
        T x;
        T y;
    };

    template <typename T>
    struct vec2comp {
        T x;
        T y;
        vec2<T> n;
        vec2<T> e;
        vec2<T> s;
        vec2<T> w;

        vec2comp(vec2<T> vec) {
            Update(vec);
        }

        void Update(vec2<T> vec) {
            x = vec.x;
            y = vec.y;
            n.x = vec.x;
            n.y = vec.y + 1;
            e.x = vec.x + 1;
            e.y = vec.y;
            s.x = vec.x;
            s.y = vec.y - 1;
            w.x = vec.x - 1;
            w.y = vec.y;
        }

        vec2<T> Way(uint8_t _way) {
            switch (_way) {
            case 0b00001000:
                return n;

            case 0b00000100:
                return e;

            case 0b00000010:
                return s;

            case 0b00000001:
                return w;
            };

            return {x, y};
        }

        operator vec2<T>() const {
            return {x, y};
        }
    };
    enum turn {
        stop,
        forward,
        right,
        left,
        back,
        r90,
        l90,

    };
}