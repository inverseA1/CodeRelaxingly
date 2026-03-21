/*
*约瑟夫问题。这是十七世纪的法国数学家加斯帕在《数目的游戏问题》中讲的一个故事：15个基督教徒和15个异教徒在海上遇险，必须将一半的人投入海中，其余的人才能幸免于难，于是想了个办法：30个人围成一个圆圈，从第一个人开始依次报数，每数到第9个人就将他扔入大海，如此循环进行直到仅余15个人为止。问怎样排法，才能使每次投入大海的都是异教徒。
本题示例为 @ @ @ @ + + + + + @ @ + @ @ @ + @ + + @ @ + + + @ + + @ @ + （第一个人前无空格，每人中间1个空格）
**输出格式要求："The original circle is (+:papandom,  @:christian);\n" "%c "
*/
#include <iostream>
#include <string>
using namespace std;
//原始约瑟夫问题：第step个人要扔下去
bool OriginalJoseph(int call, int step) { return call % step == 0; }
//新约瑟夫问题：报数中包含有step的人要扔下去
//注：要求step为1~9
bool NewJoseph(int call, int step) {
    if (call < 0) call = -call;
    do {
        if (call % 10 == step) return true;
        call /= 10;
    } while (call > 0);
    return false;
}

void Eliminate(int* count, char* circle, int point) {
    (*count)++;//有人要倒霉了
    circle[point] = '+';//是异端！
}

void SolveJoseph(char* circle, const int n, const int papandom, const int step, bool (*shouldEliminate)(int, int)) {
    int count = 0, call = 1, point = 0;//初始化扔下去的人数、当前报数、报数者
    do {

        if (shouldEliminate(call, step)) /*报数为step的倍数的人*/ {
            Eliminate(&count, circle, point);
        }

        do{
        point = (++point) % n;//下一个，被扔的人不会报数
        }while (circle[point] == '+');

        call++;//报数
    } while (count < papandom);//扔足够多的人
}

int main() {
    char circle[30];
    for (int i = 0; i < 30; i++) {
        circle[i] = '@';
    }//完成数组初始化

    SolveJoseph(circle, 30, 15, 9, OriginalJoseph);

    for (int i = 0; i < 30; i++) {
        cout << circle[i] << " ";
    }
    return 0;
}