#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int len = nums.size();
        for(int i = 0 ; i < len ; i++){
            for(int j = 0 ; j < i ; j++)
                if(nums[i] + nums[j] == target){
                    return {i , j};
                }
        }
        return {};
    }
};

int main(){
    Solution solution;
    vector<int> nums = { 2 , 7 , 11 , 15};
    vector<int> vec = solution.twoSum( nums ,9);
    cout << vec[0] 
         << " "
         << vec[1]
         << endl;
    return 0;
}