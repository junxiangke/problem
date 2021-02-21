#include<iostream>           //输入输出需要的库
#include<vector>             //STL库，容器
#include<algorithm>          //调sort函数，等
#include<queue>              //STL库，队列
#include<stack>              //STL库，栈
#include<unordered_map>      //哈希表，查找效率高，O(1)
#include<map>
#include<set>
#include<numeric>
using namespace std;         //命名空间


// 78 子集 
class Solution {         // 回溯法，相当于一种深度优先搜索         
public:                  // 可绘制树状图       时间复杂度O(n*2^n)  子集个数是2^n，每个集合的平均长度是O(n)
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> tmp;
        vector<vector<int>> results;
        sort(nums.begin(), nums.end());
        helper(nums, 0, tmp, results);
        return results;
    }
private:
    void helper(vector<int>& nums, int offset, vector<int>& tmp, vector<vector<int>>& results) {
        results.push_back(tmp);
        for(int i=offset; i<nums.size(); i++) {        // 对于同一层循环，相当于是节点的兄弟，offset相当于是每一层的标记，offset++意味着进入下一层
            tmp.push_back(nums[i]);
            helper(nums, i+1, tmp, results);           // 进入当前节点的子节点
            tmp.pop_back();
        }
    }
};

// 90  子集2 包含重复元素   
class Solution {
public:                     //  时间复杂度O(n*2^n)
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> tmp;
        vector<vector<int>> results;
        sort(nums.begin(), nums.end());
        helper(nums, 0, tmp, results);
        return results;
    }
private:
    void helper(vector<int>& nums, int offset, vector<int>& tmp, vector<vector<int>>& results) {
        results.push_back(tmp);
        for(int i=offset; i<nums.size(); i++) { 
            tmp.push_back(nums[i]);
            helper(nums, i+1, tmp, results);
            tmp.pop_back();
            while(i<nums.size()-1 && nums[i]==nums[i+1]) i++;
        }
    }
};


// 39 组合总和
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> tmp;
        vector<vector<int>> results;
        sort(candidates.begin(), candidates.end());
        helper(candidates, 0, tmp, results, target);
        return results;
    }
private:
    void helper(vector<int>& nums, int offset, vector<int>& tmp, vector<vector<int>>& results, int target) {
        if(accumulate(tmp.begin(), tmp.end(), 0)==target) {
            results.push_back(tmp);
            return;
        }
        else if(accumulate(tmp.begin(), tmp.end(), 0)>target)  return;
        for(int i=offset; i<nums.size(); i++) {
            tmp.push_back(nums[i]);
            helper(nums, i, tmp, results, target);        
            //任一元素可以无限使用，因此不断放入同一元素，直到触碰边界条件后，i++，遍历下一个元素 
            if(accumulate(tmp.begin(), tmp.end(), 0)>=target){
                tmp.pop_back();
                return;                                  
                // 对于同一层循环，相当于是节点的兄弟，超出target以后，后面比他更大的兄弟，没有必要遍历，剪枝
            }
            else tmp.pop_back();        
        }
    }
};


// 40 组合总和2
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> tmp;
        vector<vector<int>> results;
        sort(candidates.begin(), candidates.end());
        helper(candidates, 0, tmp, results, target);
        return results;
    }
private:
    void helper(vector<int>& nums, int offset, vector<int>& tmp, vector<vector<int>>& results, int target) {
        if(accumulate(tmp.begin(), tmp.end(), 0)==target) {
            results.push_back(tmp);
            return;
        }
        else if(accumulate(tmp.begin(), tmp.end(), 0)>target)  return;
        for(int i=offset; i<nums.size(); i++) {
            tmp.push_back(nums[i]);
            helper(nums, i+1, tmp, results, target);
            if(accumulate(tmp.begin(), tmp.end(), 0)==target){   // 剪枝
                tmp.pop_back();
                return;
            }
            tmp.pop_back();
            while(i<nums.size()-1 && nums[i]==nums[i+1]) i++;
        }
    }
};

// 216 组合总和
class Solution {          //既限制了数字个数，又限制了和的大小，需要两次剪枝 
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> results;
        if(k<=0 || n<=0) return results;
        vector<int> result;
        helper(k, n, 1, results, result);
        return results;
    }
private:
    void helper(int k, int n, int offset, vector<vector<int>>& results, vector<int>& result) {
        int sum = accumulate(result.begin(), result.end(), 0);
        if(result.size() == k && sum == n) {
            results.push_back(result);
            return;
        }
        else if(result.size()>=k || n-sum<offset) return;
        for(int i = offset; i<=9; i++) {
            result.push_back(i);
            helper(k, n, i+1, results, result);
            if(sum+i >= n){
                result.pop_back(); return;  // 和已经超过了n，不需要遍历比他还要大的兄弟节点
            }
            result.pop_back();
            if(9-i+result.size()+1<k) return;
        }
    }
};


// 77 组合
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> results;
        if(k>n) return results;
        // vector<int> result(k);        //  初始化会默认填充0，结果为[[0,0]]
        vector<int> result;             
        helper(n, k, 1, result, results);
        return results;
    }
private:
    void helper(int n, int k, int offset, vector<int>& result, vector<vector<int>>& results) {
        if(result.size()==k) {
            results.push_back(result);
            return;
        }
        for(int i=offset; i<=n; i++) {
            result.push_back(i);
            helper(n, k, i+1, result, results);
            result.pop_back();
            if(result.size()+n-i+1<k) return;             // 剪枝是必要的，否则超出时间限制
        }
    }
};
// 第二次刷题，写错剪枝条件


// 131 分割回文串
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        if(s.size()==0) return results;
        Palindrome(s, s.size(), dp);
        vector<string> solution;
        help(s, s.size(), 0, solution, results, dp);
        return results;
    }
private:
    void Palindrome(string str, int size, vector<vector<bool>>& dp) {
        for(int i=size-1; i>=0; i--) {
            for(int j=i; j<size; j++) {
                dp[i][j] = (str[i]==str[j]) && (j-i<=2 || dp[i+1][j-1]);
            }
        }      
    }
    void help(string str, int size, int start, vector<string>& solution, vector<vector<string>>& results, const vector<vector<bool>>& dp) {
        if(start==size) {
            results.push_back(solution);
            return;
        }
        for(int i=start; i<size; i++) {
            if(dp[start][i]) {
                solution.push_back(str.substr(start, i-start+1));
                help(str, size, i+1, solution, results, dp);
                solution.pop_back();
            }
        }
    }
};
// 第二次刷题 1.递归的结束条件写错，写成了solution.size()==s.size()；2.i-start+1写成了start-i+1;