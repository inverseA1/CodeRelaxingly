#include <iostream>
#include <vector>
using namespace std;

class JOSEPH{
    public:
        void Get_circle(vector<char> circle){ this->circle = circle; }
        void Get_papandom(int papandom){ this->papandom = papandom; }
        void Get_step(int step){ this->step = step; }

        void Example_Init(){
            this->circle.assign(30,'@');
            this->papandom = 15;
            this->step = 9;
        }

        void Solve_Joseph(){
            int n = this->circle.size(), count = 0, call = 1, point = 0;//初始化总人数，已经扔下去的人数、当前报数、报数者
            do {
                if (this->OriginalJoseph(call)) /*报数为step的倍数的人*/ {
                    this->Eliminate(count, point);
                }
                do{
                point = (++point) % n;//下一个，被扔的人不会报数
                }while (this->circle[point] == '+');

                call++;//报数
            } while (count < this->papandom);//扔足够多的人
        }

        void Print_Joseph(){
            for (int i = 0; i < 30; i++) {
                cout<< this->circle[i] << " ";
            }
            cout<<endl;
        }

    private:
        vector<char> circle;
        int papandom;
        int step;

        //原始约瑟夫问题：第step个人要扔下去
        bool OriginalJoseph(int call) { return call % this->step == 0; }
        //新约瑟夫问题：报数中包含有step的人要扔下去
        //注：要求step为1~9
        bool NewJoseph(int call) {
            if (call < 0) call = -call;
            do {
                if (call % 10 == this->step) return true;
                call /= 10;
            } while (call > 0);
            return false;
        }
        void Eliminate(int& count, int point) {
            count++;//有人要倒霉了
            this->circle[point] = '+';//是异端！
        }
};

int main() {
    JOSEPH Joseph;

    Joseph.Example_Init();

    Joseph.Solve_Joseph();
    Joseph.Print_Joseph();

    return 0;
}