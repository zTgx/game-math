#pragma once

// 核心配置
#include "GameMath/Config.hpp"

// 基础数学类型
#include "GameMath/Vector.hpp"
#include "GameMath/Matrix.hpp"
// #include "GameMath/Quaternion.hpp"

// 高级功能
// #include "GameMath/Transform.hpp"
// #include "GameMath/Geometry.hpp"
// #include "GameMath/Random.hpp"
// #include "GameMath/Interpolation.hpp"
#include "GameMath/Utility.hpp"

// 常用类型别名
namespace GameMath {
    // 向量
    using Vec2 = Vector<float, 2>;
    using Vec3 = Vector<float, 3>;
    using Vec4 = Vector<float, 4>;
    
    // 矩阵
    using Mat3 = Matrix<float, 3, 3>;
    using Mat4 = Matrix<float, 4, 4>;
    
    // // 四元数
    // using Quat = Quaternion;
}