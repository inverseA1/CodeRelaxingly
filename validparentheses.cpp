#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        int len = s.length();
        vector<char> sv(len,' ');
        int pos = 0;

        for(int i = 0 ; i < len ; i++){
            char s_ = s[i];
            if( (s_ == '(') || (s_ == '[') || (s_ == '{') ){
                sv[pos] = s_;
                pos++;
            }else{
                if( (pos != 0) &&
                    ((s_ == ')') && (sv[pos == 0 ? 0 : pos-1] == '(') ) ||
                    ((s_ == ']') && (sv[pos == 0 ? 0 : pos-1] == '[') ) ||
                    ((s_ == '}') && (sv[pos == 0 ? 0 : pos-1] == '{') ) ){
                        sv[pos-1] = ' ';
                        pos--;
                    }else{
                        return false;
                    }
            }
        }

        if(pos == 0){
            return true;
        }
        return false;
    }

};

int main(){
    Solution solution;
    cout << solution.isValid("]");
    return 0;
}