//学习关于文件读写输入输出流

#include<fstream>
#include<iostream>

int main(){
    std::ifstream in("README.md");
    if (!in) {                // operator bool
        std::cerr << "打开失败\n";
        return 1;
    }

    char buf[100];
    in.getline(buf, 100);    // 读取一行
    std::streamsize n = in.gcount();
    std::cout.write(buf, n); // 输出

    in.seekg(0, std::ios::beg); // 回到文件开头
    int x;
    in >> x;                 // 格式化读取整数

    in.close();
    return 0;
}