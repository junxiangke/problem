#include<iostream>           //输入输出需要的库
#include<vector>             //STL库，容器
#include<algorithm>          //调sort函数，等
#include<queue>              //STL库，队列
#include<stack>              //STL库，栈
#include<unordered_map>      //哈希表，查找效率高，O(1)
#include<unordered_set>
#include<map>
#include<set>
#include<numeric>
using namespace std;         //命名空间

// 46 全排列
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int size = nums.size();
        if(size) help(nums, 0, size);
        return res;
    }
private:
    vector<vector<int>> res;
    void help(vector<int>& nums, int f, int size) {
        if(f == size-1) res.push_back(nums);
        for(int i=f; i<size; i++){     // 所有数字都放在f一次，从f+1递归全排列
            swap(nums[i], nums[f]);
            help(nums, f+1, size);
            swap(nums[i], nums[f]);
        }
    }
};
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> results;
        if(nums.size() == 0) return results;
        vector<int> result;
        unordered_set<int> visited;
        helper(nums, results, result, visited);
        return results;
    }
private:
    vector<vector<int>> res;
    void helper(vector<int>& nums, vector<vector<int>>& results, vector<int>& result, unordered_set<int>& visited) {
        if(result.size() == nums.size()) {
            results.push_back(result);
            return;
        }
        for(int i = 0; i<nums.size(); i++) {
            if(visited.count(nums[i])) continue;
            result.push_back(nums[i]);
            visited.insert(nums[i]);
            helper(nums, results, result, visited);     // 每个位置都遍历所有数字，递归调用进入下一个位置
            result.pop_back();
            visited.erase(nums[i]);
        }
        return;
    }
};


// 47 全排列 2
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int size = nums.size();
        if(size) help(nums, 0, size);
        return res;
    }
private:
    vector<vector<int>> res;
    void help(vector<int>& nums, int f, int size) {
        if(f == size-1) res.push_back(nums);
        for(int i=f; i<size; i++){
            int flag = 1;
            for(int tmp=f; tmp<i; tmp++) {            // 意味着i处的元素已经在offset处放置过了，即同一层已经处理过具有相同值的兄弟节点
                if(nums[tmp] == nums[i]) {
                    flag = 0;
                    break;
                }
            }
            if(flag) {
                swap(nums[i], nums[f]);
                help(nums, f+1, size);
                swap(nums[i], nums[f]);
            }
        }
    }
};

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> results;
        if(nums.size() == 0) return results;
        sort(nums.begin(), nums.end());
        help(nums, 0, nums.size());
        return res;
    }
private:
    vector<vector<int>> res;
    void help(vector<int>& nums, int f, int size) {
        if(f == size-1) res.push_back(nums);
        for(int i=f; i<size; i++){
            swap(nums[i], nums[f]);
            help(nums, f+1, size);
            swap(nums[i], nums[f]);
            while(i<size-1 && nums[i]==nums[i+1]) i++;
        }
    }
};
// 出问题的原因是[0,0,1,9]在offset=0，i=3时，置换为[9,0,1,0]，此时两个相同的值被分开了，在下一层的全排列中，[0,1,0]会出问题


// 51 N皇后         问题函数化    时间复杂度不是n！因为很多排列在一开始或者中间就结束了
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> results;
        if(n<=0) return results; 
        vector<int> cols;
        dfs(n, cols, results);
        return results;
    }
private:
    void dfs(int n, vector<int>& cols, vector<vector<string>>& results) {     //全排列
        if(cols.size() == n) {
            results.push_back(drawChessboard(cols));
            return ;
        }
        for(int col = 0; col < n; col++) {
            if(!isValid(cols, col)) continue;
            cols.push_back(col);
            dfs(n, cols, results);
            cols.pop_back();
        }
    }
    bool isValid(vector<int> cols, int column) {
        int raw = cols.size();
        for(int raw_index = 0; raw_index < raw; raw_index++) {
            if(cols[raw_index] == column) return false;
            if(raw_index + cols[raw_index] == raw + column) return false;
            if(raw_index - cols[raw_index] == raw - column) return false;
        }
        return true;
    }
    vector<string> drawChessboard(vector<int> cols) {          // 绘制结果
        vector<string> result;
        for(int raw_index = 0; raw_index < cols.size(); raw_index++) {
            string tmp(cols.size(), '.');         // 构造string的方法
            tmp[cols[raw_index]] = 'Q';
            result.push_back(tmp);
        }
        return result;
    }
};

// 22 括号生成  有条件的全排列
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> results;
        helper(results, n, n, "");
        return results;
    }
private:
    void helper(vector<string>& results, int left, int right, string result) {
        // left是指剩余未使用的左括号
        if(left > right) return;
        if(left == 0 && right == 0) {
            results.push_back(result);
            return;
        }
        if(left>0) helper(results, left-1, right, result+"(");
        if(right>0) helper(results, left, right-1, result+")");
    }
};
