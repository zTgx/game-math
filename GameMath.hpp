// #pragma once

// #include <Eigen/Dense>
// #include <cmath>
// #include <type_traits>
// #include <random>
// #include <utility>

// namespace GameMath {

// // 前置声明
// template<typename T> class Matrix;
// template<typename T, int N> class Vector;

// // 类型特性
// namespace internal {
//     template<typename T> using IsArithmetic = std::enable_if_t<std::is_arithmetic_v<T>>;
// }

// /******************************
//  *        矩阵类定义           *
//  ******************************/
// template<typename T>
// class Matrix {
//     static_assert(std::is_arithmetic_v<T>, "Matrix type must be arithmetic");
    
//     Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> m_data;

// public:
//     // 构造方法
//     Matrix() = default;
//     Matrix(int rows, int cols) : m_data(rows, cols) {}
    
//     template<int Rows, int Cols>
//     Matrix(const T (&array)[Rows][Cols]) : m_data(Rows, Cols) {
//         for (int i = 0; i < Rows; ++i)
//             for (int j = 0; j < Cols; ++j)
//                 m_data(i, j) = array[i][j];
//     }
    
//     Matrix(std::initializer_list<std::initializer_list<T>> init) {
//         int rows = init.size();
//         int cols = rows > 0 ? init.begin()->size() : 0;
//         m_data.resize(rows, cols);
        
//         int i = 0;
//         for (const auto& row : init) {
//             int j = 0;
//             for (const auto& val : row) {
//                 m_data(i, j++) = val;
//             }
//             ++i;
//         }
//     }
    
//     // 访问方法
//     int rows() const { return m_data.rows(); }
//     int cols() const { return m_data.cols(); }
//     T& operator()(int row, int col) { return m_data(row, col); }
//     const T& operator()(int row, int col) const { return m_data(row, col); }
    
//     // Eigen数据访问
//     auto& eigen() { return m_data; }
//     const auto& eigen() const { return m_data; }
    
//     // 矩阵操作
//     Matrix<T> transposed() const { return Matrix<T>(m_data.transpose()); }
//     Matrix<T> inverse() const { return Matrix<T>(m_data.inverse()); }
//     T determinant() const { return m_data.determinant(); }
    
//     // 运算符重载
//     Matrix<T> operator+(const Matrix<T>& other) const { return Matrix<T>(m_data + other.m_data); }
//     Matrix<T> operator-(const Matrix<T>& other) const { return Matrix<T>(m_data - other.m_data); }
//     Matrix<T> operator*(const Matrix<T>& other) const { return Matrix<T>(m_data * other.m_data); }
//     Matrix<T> operator*(T scalar) const { return Matrix<T>(m_data * scalar); }
    
//     // 静态工厂方法
//     static Matrix<T> identity(int size) { return Matrix<T>(Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Identity(size, size)); }
//     static Matrix<T> zero(int rows, int cols) { return Matrix<T>(Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Zero(rows, cols)); }
// };


// /******************************
//  *      游戏数学算法           *
//  ******************************/
// // 线性插值
// template<typename T, typename U>
// T lerp(const T& a, const T& b, U t) {
//     return a + (b - a) * t;
// }

// // 2D向量叉积
// template<typename T>
// T cross(const Vector<T, 2>& a, const Vector<T, 2>& b) {
//     return a[0] * b[1] - a[1] * b[0];
// }

// // 3D向量叉积
// template<typename T>
// Vector<T, 3> cross(const Vector<T, 3>& a, const Vector<T, 3>& b) {
//     return Vector<T, 3>(
//         a[1] * b[2] - a[2] * b[1],
//         a[2] * b[0] - a[0] * b[2],
//         a[0] * b[1] - a[1] * b[0]
//     );
// }

// // 点与矩形碰撞检测
// template<typename T>
// bool point_in_rect(const Vector<T, 2>& point, const Vector<T, 2>& rect_pos, 
//                   const Vector<T, 2>& rect_size) {
//     return point[0] >= rect_pos[0] && point[0] <= rect_pos[0] + rect_size[0] &&
//            point[1] >= rect_pos[1] && point[1] <= rect_pos[1] + rect_size[1];
// }

// // 矩形与矩形碰撞检测
// template<typename T>
// bool rect_collision(const Vector<T, 2>& pos1, const Vector<T, 2>& size1,
//                    const Vector<T, 2>& pos2, const Vector<T, 2>& size2) {
//     return pos1[0] < pos2[0] + size2[0] && pos1[0] + size1[0] > pos2[0] &&
//            pos1[1] < pos2[1] + size2[1] && pos1[1] + size1[1] > pos2[1];
// }

// // 随机数生成器
// class Random {
//     static std::mt19937 s_engine;
    
// public:
//     static void seed(unsigned int seed) { s_engine.seed(seed); }
    
//     template<typename T>
//     static T range(T min, T max) {
//         if constexpr (std::is_integral_v<T>) {
//             std::uniform_int_distribution<T> dist(min, max);
//             return dist(s_engine);
//         } else {
//             std::uniform_real_distribution<T> dist(min, max);
//             return dist(s_engine);
//         }
//     }
    
//     template<typename T>
//     static Vector<T, 2> in_circle(T radius) {
//         T angle = range<T>(0, 2 * M_PI);
//         T r = radius * std::sqrt(range<T>(0, 1));
//         return Vector<T, 2>(r * std::cos(angle), r * std::sin(angle));
//     }
    
//     template<typename T>
//     static Vector<T, 2> on_circle(T radius) {
//         T angle = range<T>(0, 2 * M_PI);
//         return Vector<T, 2>(radius * std::cos(angle), radius * std::sin(angle));
//     }
// };

// std::mt19937 Random::s_engine(std::random_device{}());

// // 缓动函数
// template<typename T>
// T ease_in(T t) {
//     return t * t;
// }

// template<typename T>
// T ease_out(T t) {
//     return 1 - (1 - t) * (1 - t);
// }

// template<typename T>
// T ease_in_out(T t) {
//     return t < 0.5 ? 2 * t * t : 1 - std::pow(-2 * t + 2, 2) / 2;
// }

// } // namespace GameMath