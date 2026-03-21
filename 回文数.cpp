#include <iostream>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if( x < 0){
            return false;
        }else{
            int td = this->GetTDig(x);
            for(int i = 0 ; i < td/2 ; i++){
                if(this->GetDigN(x,i) != this->GetDigN(x,td-1 - i)){
                    return false;
                }
            }
            return true;
        }
    }

    //获得某个整数的第n位，注意0为个位
    int GetDigN(int x, int n){
        int dig = 0;
        for(int i = 0 ; i < n ; i++){
            x /= 10;
        }
        dig += x % 10;
        return dig;
    }
    //获得某个整数有几位，没考虑x <= 0
    int GetTDig(int x){
        int td = 0;
        do{
            x /= 10;
            td++;
        }while(x != 0);
        return td;
    }
};

int main(){
    Solution solution;
    cout << solution.GetDigN(4321, 1) << ' '
         << solution.GetTDig(0) << ' '
         << solution.isPalindrome(0) << endl;
    return 0;
}