#include<math.h>
#include<vector>
#include<string>
#include<iostream>
#include<numeric>
#include<algorithm>
using namespace std;

/****
// 比特位计数
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> outlist(num+1,0);
        if(num==0)
            outlist[0] = 0;
        else if(num==1){
            outlist[0] = 0;
            outlist[1] = 1;
        }
        else{
            outlist[0] = 0;
            outlist[1] = 1;
            int curr_base = 2;
            int next_base = 4;
            for(int i=2; i<=num; i++){
                if(i==next_base){
                    curr_base = next_base;
                    next_base = next_base<<1;
                }
                outlist[i] = outlist[i-curr_base]+1;
            }
        }
        return outlist;
    }
};
****/

/****
//最小路径和
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        //vector<int> a(n,0);
        vector<vector<int>> res_arr(m, vector<int>(n,0));
        res_arr[0][0] = grid[0][0];
        for(int j=1;j<n;j++)
            res_arr[0][j] = res_arr[0][j-1] + grid[0][j];
        for(int i=1;i<m;i++)
            res_arr[i][0] = res_arr[i-1][0] + grid[i][0];
        
        //int sum=0;
        if(m==1){
            return res_arr[0][n-1];
        }
        else if(n==1){
            return res_arr[m-1][0];
        }
        else{
            for(int i=1; i<m;i++)
                for(int j=1;j<n;j++){
                    res_arr[i][j] = min(res_arr[i-1][j],res_arr[i][j-1])+grid[i][j];
                }
            return res_arr[m-1][n-1];
        }
    }
};
****/

/****
//等差数列划分
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int len = A.size();
        vector<int> sub_num(len,0);
        int diff = A[1]-A[0];
        int cnt_d = 0;
        int d;
        for(int i=2;i<len;i++){
            d = A[i]-A[i-1];
            if(d==diff) {
                cnt_d += 1;
                sub_num[i] = cnt_d;
            }
            else{
                diff = d;
                cnt_d = 0;
            }
        }
        int sum = 0;
        for(int i=0;i<len;i++)
            sum += sub_num[i];
        return sum;
    }
};
****/


/****
//三角形最小路径和
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int row = triangle.size();
        //vector<int> res_num = vector<int>(row,0);
        vector<int> res_num(row,0);
        vector<int> res_back(row,0);
        res_back[0] = triangle[0][0];
        int res;
        int col;
        if(row==1) 
            res = res_back[0];
        else{
            for(int i=1; i<row; i++){
                col = triangle[i].size();
                for(int j=0;j<col;j++){
                    if(j==0)
                        res_num[j] = res_back[j] + triangle[i][0];
                    else if(j==col-1)
                        res_num[j] = res_back[j-1] + triangle[i][j];
                    else
                        res_num[j] = triangle[i][j] + min(res_back[j-1],res_back[j]);
                }
                res_back = res_num;
            }
            for(int k=0;k<col;k++){
                if(res_back[k]<res)
                    res = res_back[k];
            }
        }
        return res;
    }
};
****/

//1.两数之和
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> nums_back(nums);
        sort(nums.begin(), nums.end());
        int size = nums.size();
        int begin = 0;
        int end = size-1;
        vector<int> res,res_id;
        while(begin != end){
            if(target< (nums[begin]+nums[end])){
                end--;
                //cout<<end<<endl;
            }
            else if(target> (nums[begin]+nums[end])){
                begin++;
                //cout<<begin<<endl;
            }

            else{
                res.push_back(nums[begin]);
                res.push_back(nums[end]);
                break;
            }
        }
        //cout<<res[0]<<','<<res[1]<<endl;
        if(begin == end)
            return res_id;
        else{
            for(int i=0;i<size;i++){
                if(nums_back[i]==res[0])
                    res_id.push_back(i);
                else if(nums_back[i]==res[1])
                    res_id.push_back(i);

                if(res_id.size()==2) break;
            }
        }
        return res_id;
    }
};

int main(int argc, char const *argv[])
{
    Solution s = Solution();
    int arr[3] = {3,3};
    vector<int> nums(arr,arr+2);
    vector<int> res_id = s.twoSum(nums, 6);
    cout<<res_id[0]<<','<<res_id[1]<<endl;
    return 0;
}
