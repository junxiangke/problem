#include<iostream>           //输入输出需要的库
#include<vector>             //STL库，容器
#include<algorithm>          //调sort函数，等
#include<queue>              //STL库，队列
#include<stack>              //STL库，栈
#include<unordered_map>      //哈希表，查找效率高，O(1)
#include<map>
#include<set>
#include<numeric>
#include <string>
using namespace std;         //命名空间

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

// 887 鸡蛋掉落
