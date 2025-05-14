#pragma once

#include <Eigen/Dense>
#include <cmath>
#include <type_traits>
#include <random>
#include <utility>

namespace GameMath {

// 前置声明
template<typename T> class Matrix;
template<typename T, int N> class Vector;

// 类型特性
namespace internal {
    template<typename T> using IsArithmetic = std::enable_if_t<std::is_arithmetic_v<T>>;
}

/******************************
 *        矩阵类定义           *
 ******************************/
template<typename T>
class Matrix {
    static_assert(std::is_arithmetic_v<T>, "Matrix type must be arithmetic");
    
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> m_data;

public:
    // 构造方法
    Matrix() = default;
    Matrix(int rows, int cols) : m_data(rows, cols) {}
    
    template<int Rows, int Cols>
    Matrix(const T (&array)[Rows][Cols]) : m_data(Rows, Cols) {
        for (int i = 0; i < Rows; ++i)
            for (int j = 0; j < Cols; ++j)
                m_data(i, j) = array[i][j];
    }
    
    Matrix(std::initializer_list<std::initializer_list<T>> init) {
        int rows = init.size();
        int cols = rows > 0 ? init.begin()->size() : 0;
        m_data.resize(rows, cols);
        
        int i = 0;
        for (const auto& row : init) {
            int j = 0;
            for (const auto& val : row) {
                m_data(i, j++) = val;
            }
            ++i;
        }
    }
    
    // 访问方法
    int rows() const { return m_data.rows(); }
    int cols() const { return m_data.cols(); }
    T& operator()(int row, int col) { return m_data(row, col); }
    const T& operator()(int row, int col) const { return m_data(row, col); }
    
    // Eigen数据访问
    auto& eigen() { return m_data; }
    const auto& eigen() const { return m_data; }
    
    // 矩阵操作
    Matrix<T> transposed() const { return Matrix<T>(m_data.transpose()); }
    Matrix<T> inverse() const { return Matrix<T>(m_data.inverse()); }
    T determinant() const { return m_data.determinant(); }
    
    // 运算符重载
    Matrix<T> operator+(const Matrix<T>& other) const { return Matrix<T>(m_data + other.m_data); }
    Matrix<T> operator-(const Matrix<T>& other) const { return Matrix<T>(m_data - other.m_data); }
    Matrix<T> operator*(const Matrix<T>& other) const { return Matrix<T>(m_data * other.m_data); }
    Matrix<T> operator*(T scalar) const { return Matrix<T>(m_data * scalar); }
    
    // 静态工厂方法
    static Matrix<T> identity(int size) { return Matrix<T>(Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Identity(size, size)); }
    static Matrix<T> zero(int rows, int cols) { return Matrix<T>(Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Zero(rows, cols)); }
};

/******************************
 *        向量类定义           *
 ******************************/
template<typename T, int N>
class Vector {
    static_assert(std::is_arithmetic_v<T>, "Vector type must be arithmetic");
    static_assert(N > 0, "Vector dimension must be positive");
    
    Eigen::Matrix<T, N, 1> m_data;

public:
    Vector() = default;
    
    template<typename... Args, typename = internal::IsArithmetic<T>>
    Vector(Args... args) : m_data{static_cast<T>(args)...} {}
    
    // 访问方法
    static constexpr int dimension() { return N; }
    T& operator[](int index) { return m_data[index]; }
    const T& operator[](int index) const { return m_data[index]; }
    
    // 向量运算
    T length() const { return m_data.norm(); }
    T length_squared() const { return m_data.squaredNorm(); }
    Vector<T, N> normalized() const { return Vector<T, N>(m_data.normalized()); }
    T dot(const Vector<T, N>& other) const { return m_data.dot(other.m_data); }
    
    // 运算符重载
    Vector<T, N> operator+(const Vector<T, N>& other) const { return Vector<T, N>(m_data + other.m_data); }
    Vector<T, N> operator-(const Vector<T, N>& other) const { return Vector<T, N>(m_data - other.m_data); }
    Vector<T, N> operator*(T scalar) const { return Vector<T, N>(m_data * scalar); }
    Vector<T, N> operator/(T scalar) const { return Vector<T, N>(m_data / scalar); }
    
    // 静态方法
    static Vector<T, N> zero() { return Vector<T, N>(Eigen::Matrix<T, N, 1>::Zero()); }
    static Vector<T, N> unit() { return Vector<T, N>(Eigen::Matrix<T, N, 1>::Unit()); }
    static Vector<T, N> random() { return Vector<T, N>(Eigen::Matrix<T, N, 1>::Random()); }
};

// 常用向量类型别名
using Vector2f = Vector<float, 2>;
using Vector3f = Vector<float, 3>;
using Vector4f = Vector<float, 4>;
using Vector2d = Vector<double, 2>;
using Vector3d = Vector<double, 3>;
using Vector4d = Vector<double, 4>;
using Vector2i = Vector<int, 2>;
using Vector3i = Vector<int, 3>;
using Vector4i = Vector<int, 4>;

/******************************
 *      矩阵操作函数           *
 ******************************/
template<typename T>
Matrix<T> rotate_90_clockwise(const Matrix<T>& mat) {
    Matrix<T> result(mat.cols(), mat.rows()); // Create a new matrix with transposed dimensions
    result.eigen() = mat.eigen().transpose().rowwise().reverse();
    return result;
}

template<typename T>
Matrix<T> rotate_90_counterclockwise(const Matrix<T>& mat) {
    Matrix<T> result(mat.cols(), mat.rows());
    result.eigen() = mat.eigen().transpose().colwise().reverse();
    return result;
}

template<typename T>
Matrix<T> rotate_180(const Matrix<T>& mat) {
    Matrix<T> result(mat.rows(), mat.cols());
    result.eigen() = mat.eigen().reverse();
    return result;
}

template<typename T>
Matrix<T> flip_horizontal(const Matrix<T>& mat) {
    Matrix<T> result(mat.rows(), mat.cols());
    result.eigen() = mat.eigen().rowwise().reverse();
    return result;
}

template<typename T>
Matrix<T> flip_vertical(const Matrix<T>& mat) {
    Matrix<T> result(mat.rows(), mat.cols());
    result.eigen() = mat.eigen().colwise().reverse();
    return result;
}

/******************************
 *      游戏数学算法           *
 ******************************/
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
        return Vector<T, 2>(r * std::cos(angle), r * std::sin(angle));
    }
    
    template<typename T>
    static Vector<T, 2> on_circle(T radius) {
        T angle = range<T>(0, 2 * M_PI);
        return Vector<T, 2>(radius * std::cos(angle), radius * std::sin(angle));
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

} // namespace GameMath