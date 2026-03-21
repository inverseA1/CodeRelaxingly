#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int size = strs.size();
        string cp = strs[0];
            for(int i = 0 ; i < size ; i++){
                this->IsPre(cp,strs[i]);
            }
        return cp;
    }

    bool IsPre(string& p , string s){
        if(p == s.substr(0,p.size())){
            //---
            //cout << p << " is prefix of " << s <<endl;
            //---
            return true;
        }else
        //---
        //cout << p << " is not prefix of " << s << endl;
        //---
        p.pop_back();
            return IsPre(p,s);
    }
};

int main(){
    Solution solution;
    vector<string> strs = {"flower","flow","flight"};
    cout << solution.longestCommonPrefix(strs);
    return 0;
}