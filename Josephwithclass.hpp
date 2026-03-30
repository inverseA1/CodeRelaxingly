#ifndef _JOSEPH_WITH_CLASS_
#define _JOSEPH_WITH_CLASS_

#include <iostream>
#include <vector>

class JOSEPH{
    public:
        JOSEPH(const std::vector<char>& circle, int papandom, int step)
        : circle(circle), papandom(papandom), step(step) {}

        JOSEPH() = default;

        void Get_circle(const std::vector<char>& circle){ this->circle = circle; }
        void Get_papandom(int papandom){ this->papandom = papandom; }
        void Get_step(int step){ this->step = step; }

        void Example_Init(){
            this->circle.assign(30,'@');
            this->papandom = 15;
            this->step = 9;
        }

        void Solve_Joseph(){
            int len = this->circle.size(), count = 0, call = 1, point = 0;
            do {
                if (this->OriginalJoseph(call)){
                    this->Eliminate(count, point);
                }

                do{
                point = (++point) % len;
                }while (this->circle[point] == '+');

                call++;
            }while(count < this->papandom);
        }

        void Print_Joseph(){
            int len = this->circle.size();
            for (int i = 0; i < len; i++) {
                std::cout<< this->circle[i] << ' ';
            }
            std::cout<<std::endl;
        }

    private:
        std::vector<char> circle;
        int papandom;
        int step;

        bool OriginalJoseph(int call) { return call % this->step == 0; }
        bool NewJoseph(int call) {
            if (call < 0) call = -call;
            do {
                if (call % 10 == this->step) return true;
                call /= 10;
            } while (call > 0);
            return false;
        }
        void Eliminate(int& count, int point) {
            count++;
            this->circle[point] = '+';
        }
};

#endif