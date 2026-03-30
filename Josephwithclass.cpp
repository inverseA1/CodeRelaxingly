#include <iostream>
#include <vector>
using namespace std;

class JOSEPH{
    public:
        void SolveJoseph(char* circle, const int n, const int papandom, const int step) {
            int count = 0, call = 1, point = 0;//初始化扔下去的人数、当前报数、报数者
            do {

                if (this->OriginalJoseph(call, step)) /*报数为step的倍数的人*/ {
                    this->Eliminate(&count, circle, point);
                }

                do{
                point = (++point) % n;//下一个，被扔的人不会报数
                }while (circle[point] == '+');

                call++;//报数
            } while (count < papandom);//扔足够多的人
        }

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
    private:
        void Eliminate(int* count, char* circle, int point) {
            (*count)++;//有人要倒霉了
            circle[point] = '+';//是异端！
        }
};

int main() {
    JOSEPH Joseph;
    char circle[30];
    for (int i = 0; i < 30; i++) {
        circle[i] = '@';
    }//完成数组初始化

    Joseph.SolveJoseph(circle, 30, 15, 9);

    for (int i = 0; i < 30; i++) {
        cout << circle[i] << " ";
    }
    return 0;
}