#include <iostream>

// 测试编译器包含路径
int main() {
    // 打印一些预定义宏，查看编译器信息
    std::cout << "Compiler version: " << _MSC_VER << std::endl;
    std::cout << "Include paths:" << std::endl;
    
    // 尝试包含 graphics.h
    #ifdef __has_include
        #if __has_include(<graphics.h>)
            std::cout << "graphics.h found!找到了！" << std::endl;
        #else
            std::cout << "graphics.h NOT found!" << std::endl;
        #endif
        #if __has_include(<iostream>)
            std::cout << "iostream found!找到了！" << std::endl;
        #else
            std::cout << "iostream NOT found!" << std::endl;
        #endif
    #endif
    
    return 0;
}
