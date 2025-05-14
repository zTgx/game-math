/******************************
 *      游戏数学算法           *
 ******************************/
#pragma once
#include <cmath>
#include <type_traits>
#include <random>
#include <utility>

namespace GameMath {
// 线性插值
template<typename T, typename U>
T lerp(const T& a, const T& b, U t) {
    return a + (b - a) * t;
}

// 2D向量叉积
template<typename T>
T cross(const Vector<T, 2>& a, const Vector<T, 2>& b) {
    return a[0] * b[1] - a[1] * b[0];
}

// 3D向量叉积
template<typename T>
Vector<T, 3> cross(const Vector<T, 3>& a, const Vector<T, 3>& b) {
    return Vector<T, 3>(
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]
    );
}

// 点与矩形碰撞检测
template<typename T>
bool point_in_rect(const Vector<T, 2>& point, const Vector<T, 2>& rect_pos, 
                  const Vector<T, 2>& rect_size) {
    return point[0] >= rect_pos[0] && point[0] <= rect_pos[0] + rect_size[0] &&
           point[1] >= rect_pos[1] && point[1] <= rect_pos[1] + rect_size[1];
}

// 矩形与矩形碰撞检测
template<typename T>
bool rect_collision(const Vector<T, 2>& pos1, const Vector<T, 2>& size1,
                   const Vector<T, 2>& pos2, const Vector<T, 2>& size2) {
    return pos1[0] < pos2[0] + size2[0] && pos1[0] + size1[0] > pos2[0] &&
           pos1[1] < pos2[1] + size2[1] && pos1[1] + size1[1] > pos2[1];
}

// 随机数生成器
class Random {
    static std::mt19937 s_engine;
    
public:
    static void seed(unsigned int seed) { s_engine.seed(seed); }
    
    template<typename T>
    static T range(T min, T max) {
        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(min, max);
            return dist(s_engine);
        } else {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(s_engine);
        }
    }
    
    template<typename T>
    static Vector<T, 2> in_circle(T radius) {
        T angle = range<T>(0, 2 * M_PI);
        T r = radius * std::sqrt(range<T>(0, 1));
        return Vector<T, 2>{r * std::cos(angle), r * std::sin(angle)};
    }
    
    template<typename T>
    static Vector<T, 2> on_circle(T radius) {
        T angle = range<T>(0, 2 * M_PI);
        return Vector<T, 2>{radius * std::cos(angle), radius * std::sin(angle)};
    }
};

std::mt19937 Random::s_engine(std::random_device{}());

// 缓动函数
template<typename T>
T ease_in(T t) {
    return t * t;
}

template<typename T>
T ease_out(T t) {
    return 1 - (1 - t) * (1 - t);
}

template<typename T>
T ease_in_out(T t) {
    return t < 0.5 ? 2 * t * t : 1 - std::pow(-2 * t + 2, 2) / 2;
}
};