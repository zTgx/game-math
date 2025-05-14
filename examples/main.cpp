#include "GameMath.hpp"
#include <iostream>

int main() {
    using namespace GameMath;
    
    // 矩阵操作示例
    Matrix<int> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    std::cout << "Original matrix:\n";
    for (int i = 0; i < mat.rows(); ++i) {
        for (int j = 0; j < mat.cols(); ++j) {
            std::cout << mat(i, j) << " ";
        }
        std::cout << "\n";
    }
    
    auto rotated = rotate_90_clockwise(mat);
    std::cout << "\nRotated 90° clockwise:\n";
    for (int i = 0; i < rotated.rows(); ++i) {
        for (int j = 0; j < rotated.cols(); ++j) {
            std::cout << rotated(i, j) << " ";
        }
        std::cout << "\n";
    }
    
    // 向量操作示例
    Vector3f v1(1.0f, 2.0f, 3.0f);
    Vector3f v2(4.0f, 5.0f, 6.0f);
    
    auto cross_product = cross(v1, v2);
    std::cout << "\nCross product: (" 
              << cross_product[0] << ", " 
              << cross_product[1] << ", " 
              << cross_product[2] << ")\n";
    
    // 游戏数学示例
    Vector2f point(5.0f, 5.0f);
    Vector2f rect_pos(0.0f, 0.0f);
    Vector2f rect_size(10.0f, 10.0f);
    
    std::cout << "\nPoint in rect: " 
              << (point_in_rect(point, rect_pos, rect_size) ? "true" : "false") 
              << "\n";
    
    // 随机数示例
    std::cout << "\nRandom float: " << Random::range(0.0f, 1.0f) << "\n";
    std::cout << "Random point in circle: (" 
              << Random::in_circle(5.0f)[0] << ", " 
              << Random::in_circle(5.0f)[1] << ")\n";
    
    // 缓动函数示例
    std::cout << "\nEase in at 0.5: " << ease_in(0.5f) << "\n";
    std::cout << "Ease out at 0.5: " << ease_out(0.5f) << "\n";
    std::cout << "Ease in-out at 0.5: " << ease_in_out(0.5f) << "\n";
    
    return 0;
}