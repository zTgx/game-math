#include <iostream>
#if defined(__x86_64__) || defined(_M_X64)
#include <cpuid.h>
void checkSIMD() {
    unsigned int eax, ebx, ecx, edx;
    __cpuid(1, eax, ebx, ecx, edx);

    std::cout << "SSE:  " << (edx & (1 << 25) ? "YES" : "NO") << "\n";
    std::cout << "AVX:  " << (ecx & (1 << 28) ? "YES" : "NO") << "\n";
    std::cout << "AVX2: " << (ebx & (1 << 5)  ? "YES" : "NO") << "\n";
}
#else
void checkSIMD() {
    std::cout << "ARM CPU - 检查NEON需读取/proc/cpuinfo" << "\n";
}
#endif

int main() {
    checkSIMD();
    return 0;
}