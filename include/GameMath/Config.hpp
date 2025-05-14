#pragma once

#if defined(_MSC_VER)
    #define GM_COMPILER_MSVC 1
#elif defined(__GNUC__)
    #define GM_COMPILER_GCC 1
#elif defined(__clang__)
    #define GM_COMPILER_CLANG 1
#endif

// SIMD支持检测
#if (defined(__SSE__) || defined(_M_X64) || _M_IX86_FP >= 1)
    #define GM_SIMD_SSE 1
#endif

// 数学常量
namespace GameMath {
    constexpr float PI = 3.14159265358979323846f;
    constexpr float DEG2RAD = PI / 180.0f;
    constexpr float RAD2DEG = 180.0f / PI;
    constexpr float EPSILON = 1e-6f;
}