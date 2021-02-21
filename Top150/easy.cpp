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
#include<string>
#include<cstring>
#include<sstream>
using namespace std;         //命名空间


//  118 杨辉三角形
class Solution {
public:
    vector<vector<int>> generate(int numRows) {   // 一开始忘记考虑0，1的情况
        vector<vector<int>> results;
        if(numRows == 0) return results;
        results.push_back({1});
        if(numRows == 1) return results;
        for(int i = 1; i<numRows; i++) {
            vector<int> res;
            res.push_back(1);
            for(int j = 1; j < i; j++) {
                res.push_back(results[i-1][j-1]+results[i-1][j]);
            }
            res.push_back(1);
            results.push_back(res);
        }
        return results;
    }
};

// 202 快乐数
class Solution {
public:
    bool isHappy(int n) {
        int slow = n, fast = helper(n);
        while(slow != fast) {
            slow = helper(slow);
            fast = helper(fast);
            fast = helper(fast);
        }
        return slow == 1;
        
    }
private:
    int helper(int n) {
        int res = 0;
        while(n!=0) {
            res += (n%10)*(n%10);
            n = n/10;
        }
        return res;
    }
};

// 136 只出现一次的数据                  只有一个数字出现一次，其余都出现两次，要求o(n)，不使用额外空间
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        if(nums.size()==1) return nums[0];
        int res = 0;
        for(int i = 0; i < nums.size(); i++) {
            res = res ^ nums[i];
        }
        return res;                          // 即使数组中有0，不影响结果
    }
};


// 169 多数元素         1.排序然后去nums[n/2]；2.数字不同就消耗，最后剩下的就是超过了1/2的数字
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int key = nums[0], cnt = 0;
        for(int i = 0; i<nums.size(); i++) {
            if(nums[i] == key) cnt++;
            else cnt--;
            if(cnt==0) key = nums[i+1];
        }
        return key;
    }
};

// 9 回文数      反转后半部分，看是否等于前半部分，对于10，1100，等以0为结尾的，reverse没有办法直接表达出反转后的结果
class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0 || x%10 == 0 && x != 0) return false;
        int reverse = 0;
        while(x>reverse) {
            reverse = reverse*10 + x%10;
            x = x/10;
        }
        return x == reverse || x == reverse/10;
    }
};

// 217 存在重复元素
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        set<int> *s = new set<int>(nums.begin(), nums.end()) ;   // set 使用new的方法
        return (*s).size() != nums.size();
    }
};


// 50 Pow(x, y)    暴力法会超时，特别注意int->long long
class Solution {
public:
    double myPow(double x, int n) {
        if(x == 0) return 1;
        long long N = n;
        // long long N = -n; 这样写是不对的
        if(n < 0) {
            x = 1 / x; N = -N;
        }
        return helper(x, N);
    }
private:
    double helper(double x, long long n) {
        if(n == 0) return 1;
        double y = helper(x, n / 2);
        if(n % 2) return y * y * x;
        else return y * y;
    }
};