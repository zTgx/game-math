#pragma once
#include "Vector.hpp"

namespace GameMath {

template<typename T, size_t Rows, size_t Cols>
struct Matrix {
    Vector<T, Cols> rows[Rows];

    // 构造函数
    Matrix() = default;
    
    explicit Matrix(T scalar) {
        for (auto& row : rows) {
            row = Vector<T, Cols>(scalar);
        }
    }
    
    Matrix(std::initializer_list<Vector<T, Cols>> list) {
        std::copy(list.begin(), list.end(), rows);
    }
    
    // 访问操作符
    Vector<T, Cols>& operator[](size_t row) { return rows[row]; }
    const Vector<T, Cols>& operator[](size_t row) const { return rows[row]; }
   
    // 行列访问操作符 (非常量版本)
    T& operator()(size_t row, size_t col) {
        if (row >= Rows || col >= Cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return rows[row][col];
    }
    
    // 行列访问操作符 (常量版本)
    const T& operator()(size_t row, size_t col) const {
        if (row >= Rows || col >= Cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return rows[row][col];
    }

    // 获取行列数
    constexpr size_t numRows() const { return Rows; }
    constexpr size_t numCols() const { return Cols; }
    
    // 获取列向量
    Vector<T, Rows> col(size_t colIndex) const {
        Vector<T, Rows> result;
        for (size_t i = 0; i < Rows; ++i) {
            result[i] = rows[i][colIndex];
        }
        return result;
    }
    
    // 矩阵运算
    Matrix operator+(const Matrix& rhs) const {
        Matrix result;
        for (size_t i = 0; i < Rows; ++i) {
            result[i] = rows[i] + rhs[i];
        }
        return result;
    }
    
    Matrix operator-(const Matrix& rhs) const {
        Matrix result;
        for (size_t i = 0; i < Rows; ++i) {
            result[i] = rows[i] - rhs[i];
        }
        return result;
    }
    
    template<size_t OtherCols>
    Matrix<T, Rows, OtherCols> operator*(const Matrix<T, Cols, OtherCols>& rhs) const {
        Matrix<T, Rows, OtherCols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < OtherCols; ++j) {
                result[i][j] = rows[i].dot(rhs.col(j));
            }
        }
        return result;
    }
    
    // 标量乘法
    Matrix operator*(T scalar) const {
        Matrix result;
        for (size_t i = 0; i < Rows; ++i) {
            result[i] = rows[i] * scalar;
        }
        return result;
    }
    
    // 标量除法
    Matrix operator/(T scalar) const {
        Matrix result;
        for (size_t i = 0; i < Rows; ++i) {
            result[i] = rows[i] / scalar;
        }
        return result;
    }
    
    // 转置矩阵
    Matrix<T, Cols, Rows> transposed() const {
        Matrix<T, Cols, Rows> result;
        for (size_t i = 0; i < Cols; ++i) {
            for (size_t j = 0; j < Rows; ++j) {
                result[i][j] = rows[j][i];
            }
        }
        return result;
    }
    
    // 行列式 (仅适用于方阵)
    T determinant() const {
        static_assert(Rows == Cols, "Determinant is only defined for square matrices");
        // 实现行列式计算 (递归或LU分解等方法)
        // 这里只是一个占位符实现
        if constexpr (Rows == 1) {
            return rows[0][0];
        } else if constexpr (Rows == 2) {
            return rows[0][0] * rows[1][1] - rows[0][1] * rows[1][0];
        } else {
            // 更高维度的实现
            T det = 0;
            for (size_t i = 0; i < Cols; ++i) {
                // 递归计算余子式
                // ...
            }
            return det;
        }
    }
    
    // 逆矩阵 (仅适用于方阵)
    Matrix inverse() const {
        static_assert(Rows == Cols, "Inverse is only defined for square matrices");
        // 实现逆矩阵计算 (伴随矩阵法或高斯消元法等)
        // 这里只是一个占位符实现
        Matrix result;
        T det = determinant();
        if (det == 0) {
            throw std::runtime_error("Matrix is not invertible");
        }
        
        if constexpr (Rows == 2) {
            result[0][0] = rows[1][1] / det;
            result[0][1] = -rows[0][1] / det;
            result[1][0] = -rows[1][0] / det;
            result[1][1] = rows[0][0] / det;
        } else {
            // 更高维度的实现
            // ...
        }
        return result;
    }
    
    // 静态方法
    static Matrix identity() {
        static_assert(Rows == Cols, "Identity matrix must be square");
        Matrix result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result[i][j] = (i == j) ? T(1) : T(0);
            }
        }
        return result;
    }
    
    static Matrix zero() {
        Matrix result;
        for (auto& row : result.rows) {
            row = Vector<T, Cols>(T(0));
        }
        return result;
    }
    
    // 比较操作符
    bool operator==(const Matrix& rhs) const {
        for (size_t i = 0; i < Rows; ++i) {
            if (rows[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }
    
    bool operator!=(const Matrix& rhs) const {
        return !(*this == rhs);
    }
};

// 标量乘法的友元函数 (允许 scalar * matrix)
template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols> operator*(T scalar, const Matrix<T, Rows, Cols>& matrix) {
    return matrix * scalar;
}

// 常用特化
using Matrix3x3 = Matrix<float, 3, 3>;
using Matrix4x4 = Matrix<float, 4, 4>;

// 特殊矩阵操作
Matrix4x4 perspective(float fov, float aspect, float near, float far);
Matrix4x4 orthographic(float left, float right, float bottom, float top, float near, float far);
Matrix4x4 lookAt(const Vector3f& eye, const Vector3f& target, const Vector3f& up);

/******************************
 *      矩阵操作函数           *
 ******************************/

/**
 * @brief 顺时针旋转矩阵90度
 * @param mat 输入矩阵
 * @return 旋转后的新矩阵
 */
 template<typename T, size_t Rows, size_t Cols>
 Matrix<T, Cols, Rows> rotate_90_clockwise(const Matrix<T, Rows, Cols>& mat) {
     Matrix<T, Cols, Rows> result;
     for (size_t i = 0; i < Rows; ++i) {
         for (size_t j = 0; j < Cols; ++j) {
             result[j][Rows - 1 - i] = mat[i][j];
         }
     }
     return result;
 }
 
 /**
  * @brief 逆时针旋转矩阵90度
  * @param mat 输入矩阵
  * @return 旋转后的新矩阵
  */
 template<typename T, size_t Rows, size_t Cols>
 Matrix<T, Cols, Rows> rotate_90_counterclockwise(const Matrix<T, Rows, Cols>& mat) {
     Matrix<T, Cols, Rows> result;
     for (size_t i = 0; i < Rows; ++i) {
         for (size_t j = 0; j < Cols; ++j) {
             result[Cols - 1 - j][i] = mat[i][j];
         }
     }
     return result;
 }
 
 /**
  * @brief 旋转矩阵180度
  * @param mat 输入矩阵
  * @return 旋转后的新矩阵
  */
 template<typename T, size_t Rows, size_t Cols>
 Matrix<T, Rows, Cols> rotate_180(const Matrix<T, Rows, Cols>& mat) {
     Matrix<T, Rows, Cols> result;
     for (size_t i = 0; i < Rows; ++i) {
         for (size_t j = 0; j < Cols; ++j) {
             result[Rows - 1 - i][Cols - 1 - j] = mat[i][j];
         }
     }
     return result;
 }
 
 /**
  * @brief 水平翻转矩阵
  * @param mat 输入矩阵
  * @return 翻转后的新矩阵
  */
 template<typename T, size_t Rows, size_t Cols>
 Matrix<T, Rows, Cols> flip_horizontal(const Matrix<T, Rows, Cols>& mat) {
     Matrix<T, Rows, Cols> result;
     for (size_t i = 0; i < Rows; ++i) {
         for (size_t j = 0; j < Cols; ++j) {
             result[i][Cols - 1 - j] = mat[i][j];
         }
     }
     return result;
 }
 
 /**
  * @brief 垂直翻转矩阵
  * @param mat 输入矩阵
  * @return 翻转后的新矩阵
  */
 template<typename T, size_t Rows, size_t Cols>
 Matrix<T, Rows, Cols> flip_vertical(const Matrix<T, Rows, Cols>& mat) {
     Matrix<T, Rows, Cols> result;
     for (size_t i = 0; i < Rows; ++i) {
         for (size_t j = 0; j < Cols; ++j) {
             result[Rows - 1 - i][j] = mat[i][j];
         }
     }
     return result;
 }
 
} // namespace GameMath