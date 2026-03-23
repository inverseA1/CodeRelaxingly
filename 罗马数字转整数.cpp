#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {

        int num = 0;
        if(this->FinSubS(s,"IV")){
            num += 4;
        }
        if(this->FinSubS(s,"IX")){
            num += 9;
        }
        if(this->FinSubS(s,"XL")){
            num += 40;
        }
        if(this->FinSubS(s,"XC")){
            num += 90;
        }
        if(this->FinSubS(s,"CD")){
            num += 400;
        }
        if(this->FinSubS(s,"CM")){
            num += 900;
        }
        int len = s.size();
        for(int i = 0 ; i < len ; i++){
            if(s[i] == 'I')
            num += 1;
            if(s[i] == 'V')
            num += 5;
            if(s[i] == 'X')
            num += 10;
            if(s[i] == 'L')
            num += 50;
            if(s[i] == 'C')
            num += 100;
            if(s[i] == 'D')
            num += 500;
            if(s[i] == 'M')
            num += 1000;
        }
        return num;
    }

    //查找字符串是否有某个字串，如果有，则删掉，返回是否有该字串
    bool FinSubS(string& s,string ss){
        if( s.find(ss) != string::npos ){
            int pos = s.find(ss);
            int len = ss.size();
            s.replace(pos , len , "");
            return true;
        }else
        return false;
    }
};

int main(){
    Solution solution;
    cout << solution.romanToInt("MCMXCIV");
}