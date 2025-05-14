#pragma once
#include "Config.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace GameMath {

// 通用向量模板
template<typename T, size_t N>
struct Vector {
    T data[N];
    
    // 构造函数
    Vector() = default;
    
    explicit Vector(T scalar) { fill(scalar); }
    
    Vector(std::initializer_list<T> list) {
        if (list.size() != N) {
            throw std::invalid_argument("Initializer list size does not match vector dimension");
        }
        std::copy(list.begin(), list.end(), data);
    }
    
    // 访问操作符
    T& operator[](size_t index) { 
        if (index >= N) throw std::out_of_range("Vector index out of range");
        return data[index]; 
    }
    
    const T& operator[](size_t index) const { 
        if (index >= N) throw std::out_of_range("Vector index out of range");
        return data[index]; 
    }
    
    // 数学运算
    Vector operator+(const Vector& rhs) const {
        Vector result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] + rhs[i];
        }
        return result;
    }
    
    Vector operator-(const Vector& rhs) const {
        Vector result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] - rhs[i];
        }
        return result;
    }
    
    Vector operator*(T scalar) const {
        Vector result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] * scalar;
        }
        return result;
    }
    
    Vector operator/(T scalar) const {
        if (scalar == 0) throw std::runtime_error("Division by zero");
        Vector result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] / scalar;
        }
        return result;
    }
    
    // 点积
    T dot(const Vector& rhs) const {
        T result = 0;
        for (size_t i = 0; i < N; ++i) {
            result += data[i] * rhs[i];
        }
        return result;
    }
    
    // 向量长度
    T length() const {
        return std::sqrt(length_squared());
    }
    
    // 向量长度平方
    T length_squared() const {
        return dot(*this);
    }
    
    // 归一化向量
    Vector normalized() const {
        T len = length();
        if (len == 0) throw std::runtime_error("Cannot normalize zero vector");
        return *this / len;
    }
    
    // 填充值
    void fill(T value) {
        std::fill(data, data + N, value);
    }
    
    // 静态方法
    static Vector zero() {
        return Vector(T(0));
    }
    
    static Vector one() {
        return Vector(T(1));
    }
    
    // 比较操作符
    bool operator==(const Vector& rhs) const {
        for (size_t i = 0; i < N; ++i) {
            if (data[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }
    
    bool operator!=(const Vector& rhs) const {
        return !(*this == rhs);
    }
};

// 特化优化实现 - Vector3
template<>
struct Vector<float, 3> {
    union {
        struct { float x, y, z; };
        struct { float r, g, b; };
        float data[3];
    };
    
    // 构造函数
    Vector() : x(0), y(0), z(0) {}
    
    explicit Vector(float scalar) : x(scalar), y(scalar), z(scalar) {}
    
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}
    
    Vector(std::initializer_list<float> list) {
        if (list.size() != 3) {
            throw std::invalid_argument("Initializer list size must be 3");
        }
        auto it = list.begin();
        x = *it++;
        y = *it++;
        z = *it;
    }
    
    // 访问操作符
    float& operator[](size_t index) { 
        if (index >= 3) throw std::out_of_range("Vector3 index out of range");
        return data[index]; 
    }
    
    const float& operator[](size_t index) const { 
        if (index >= 3) throw std::out_of_range("Vector3 index out of range");
        return data[index]; 
    }
    
    // 数学运算
    Vector operator+(const Vector& rhs) const {
        return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    
    Vector operator-(const Vector& rhs) const {
        return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    
    Vector operator*(float scalar) const {
        return Vector(x * scalar, y * scalar, z * scalar);
    }
    
    Vector operator/(float scalar) const {
        if (scalar == 0) throw std::runtime_error("Division by zero");
        return Vector(x / scalar, y / scalar, z / scalar);
    }
    
    // 点积
    float dot(const Vector& rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }
    
    // 叉积
    Vector cross(const Vector& rhs) const {
        return Vector(
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        );
    }
    
    // 向量长度
    float length() const {
        return std::sqrt(length_squared());
    }
    
    // 向量长度平方
    float length_squared() const {
        return dot(*this);
    }
    
    // 归一化向量
    Vector normalized() const {
        float len = length();
        if (len == 0) throw std::runtime_error("Cannot normalize zero vector");
        return *this / len;
    }
    
    // 填充值
    void fill(float value) {
        x = y = z = value;
    }
    
    // 静态方法
    static Vector zero() {
        return Vector(0.0f);
    }
    
    static Vector one() {
        return Vector(1.0f);
    }
    
    // 比较操作符
    bool operator==(const Vector& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    
    bool operator!=(const Vector& rhs) const {
        return !(*this == rhs);
    }
};

// 常用特化别名
using Vector2f = Vector<float, 2>;
using Vector3f = Vector<float, 3>;
using Vector4f = Vector<float, 4>;
using Vector2i = Vector<int, 2>;
using Vector3i = Vector<int, 3>;
using Vector4i = Vector<int, 4>;

// 运算符重载
template<typename T, size_t N>
Vector<T, N> operator*(T scalar, const Vector<T, N>& vec) {
    return vec * scalar;
}

} // namespace GameMath