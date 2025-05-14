# GameMath - 轻量级高性能游戏数学库

## 📌 概述  
GameMath 是一款专为游戏开发、计算机图形学和物理模拟打造的轻量级 C++ 数学库。它提供了向量（Vector）、矩阵（Matrix）、四元数（Quaternion）等核心数学运算，针对游戏开发中的常见需求进行了高效优化。

## ✨ 主要特性  
- **高性能**：利用模板元编程实现极致性能，未来计划支持 SIMD（SSE/AVX）加速。  
- **类型安全**：强类型设计，避免隐式类型转换带来的错误。  
- **易用 API**：支持直观的运算符重载（`+`, `-`, `*`, `/`）及常用函数（`dot`、`cross`）。  
- **跨平台兼容**：基于标准 C++17，支持 Windows、Linux、macOS 等主流平台。  
- **模块化设计**：按需引入功能，无冗余依赖，适合嵌入式和性能敏感场景。

## 核心功能  
- **向量运算**（支持 2D/3D/4D，`float` 与 `int` 类型）  
  - 基础算术（加减乘除）、点积、叉积、归一化、长度计算  
  - 针对 `Vector3` 特化，支持 `x,y,z` 与 `r,g,b` 双重访问语义  

- **矩阵运算**（任意维度，常用如 `Matrix4x4`）  
  - 矩阵乘法、转置、行列式、逆矩阵计算  
  - 单位矩阵、零矩阵便捷构造  

- **四元数支持**（规划中）  
  - 旋转插值（SLERP）、欧拉角转换等高级功能  

## 🚀 未来规划  
- **SIMD 加速**：利用硬件指令集提升计算性能。  
- **丰富数学工具**：增加几何算法（射线检测、AABB 碰撞检测）、随机数生成等。  
- **链式调用支持**：提供更友好的 API，如 `vec.normalize().scale(2.0f)`。  
- **跨语言绑定**：计划支持 Python、Lua 等脚本语言接口，方便扩展。  

## 使用优势  
- 减少重复数学代码编写，提高开发效率。  
- 优化物理和渲染计算性能，提升游戏运行流畅度。  
- 降低低级数学错误风险，如未归一化向量、矩阵乘法顺序错误。  

## 📦 安装方式  
1. **单头文件使用（推荐）**  
   直接包含头文件即可：  
   ```cpp
   #include "GameMath/GameMath.hpp"
   ```
2. **CMake 集成**  
   ```cmake
   add_subdirectory(GameMath)
   target_link_libraries(YourProject PRIVATE GameMath)
   ```

## 📖 示例代码  

**向量运算示例**  
```cpp
GameMath::Vector3 a{1.0f, 2.0f, 3.0f};
GameMath::Vector3 b{4.0f, 5.0f, 6.0f};

auto c = a + b;                // 向量加法
auto dot = a.dot(b);           // 点积
auto cross = a.cross(b);       // 叉积
auto normalized = a.normalized(); // 归一化
```

**矩阵运算示例**  
```cpp
GameMath::Matrix matA = GameMath::Matrix::identity();
GameMath::Matrix matB = GameMath::Matrix::zero();

matA(0, 0) = 2.0f;            // 访问元素
auto matC = matA * matB;      // 矩阵乘法
auto transposed = matC.transposed(); // 转置
```

## 📜 许可证  
采用 MIT 许可证，允许自由使用、修改和商业分发。

## 🤝 欢迎贡献  
项目欢迎提交 PR 和 Issue，未来计划加入：  
- 四元数完整支持  
- SIMD 硬件加速  
- 几何算法（AABB、射线检测）  
- 性能测试套件  

---

🎮 让复杂的数学计算变得简单高效，助力游戏开发者打造更流畅的游戏体验！🚀
