#include <string>
#include <iostream>
using namespace std;
#define PRINT(x) cout << x << endl;

int main(){
    //字符串定义
    string s1;
    string s2 = "Hello";
    string s3("World");
    string s4(s2);
    string s5 = s3;
    string s6(5,'a');
    PRINT(s1)
    PRINT(s2)
    PRINT(s3)
    PRINT(s4)
    PRINT(s5)
    PRINT(s6)

    //字符串拼接
    string s7 = s2 + s3;
    s1 += "String";
    s2.append(" world!");
    PRINT(s7)
    PRINT(s1)
    PRINT(s2)
    PRINT(s4)

    //字符串访问
    int len = s1.length();
    for(int i = 0 ; i < len ; i++){
        cout << s1[i] << " ";
    }
    cout << endl;

    cout << s1.at(0) << ' ' << endl;
    try{
        cout << s1.at(len) <<endl;
    }catch(const out_of_range& e){
        cout << "越界访问！" << endl;
    }
    cout << s1.front() << ' ' << s1.back() << endl;

    //字符串长度与容量
    cout << s7.empty() << " ";
    s7.clear();
    cout << s7.empty() << endl;
    cout << s1.length() << ' ' << s1.size() << ' ' << s1.capacity() << endl;

    //字符串比较
    cout << s1.compare(s1) << ' ' << s1.compare(s2) << ' ' << s1.compare(s3) << endl;

    //子字符串提取
    for(int i = 0 ; i < 2*len ; i++){
        for(int j = 0 ; j < len ; j++){
            cout << s1.substr(j,i) << endl;
        }
    }

    //查找操作
    //s2 = "Hello world!"
    cout << s2.find("H") << ' ' << (s2.find("5") == string::npos) << ' ' << s2.rfind("o") << ' ' << s2.find("O") << endl;
    

    return 0;
}