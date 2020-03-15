#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<algorithm>
using namespace std;

class Solution1 {
public:
    int climbStairs(int n) {
        int *p = new int[n];
        if(n==1) return 1;
        else if(n==2) return 2;
        else{
            p[0] = 1; 
            p[1] = 2;
            for(int i=2;i<n;i++){
                p[i] = p[i-1]+p[i-2];
            }
            return p[n-1];
            delete p;
        }
    }
};


class Solution2 {
public:
    int rob(vector<int>& nums) {
        if(nums.size()==0) return 0;

        if(nums.size()<=2) return *max_element(nums.begin(),nums.end());

        vector<int> dp = {nums[0],max(nums[1],nums[0])};

        for(int i=2;i<nums.size();i++){
            dp[i%2] = max(dp[(i-1)%2], dp[(i-2)%2]+nums[i]);
        }
        return dp[(nums.size() - 1)%2];

        //cout<<dp[(nums.size() - 1)%2]<<endl;
    }
};

//338. 比特位计数
class Solution3 {
public:
    vector<int> countBits(int num) {
        vector<int> res(num+1, 0);
        if (num == 0) {
            return res;
        }
        else if (num == 1){
            res[1] = 1;
            return res;
        }
        else {
            res[1] = 1;
            int tail = 1;
            int index;
            for (int i = 2; i <= num; ++i){
                if (i >> tail != 1) tail++;
                index = i & (~(1 << tail));
                res[i] = res[index] + 1;
                
            }
            return res;
        }
    }
};

//401.二进制手表
char ** readBinaryWatch(int num, int* returnSize){
    *returnSize = 0;
}

int main(){
}