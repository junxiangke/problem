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


// 26. 删除排序数组中的重复项
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int size = nums.size();
        if(!size) return 0;
        int slow=0, fast=1;
        while(fast<size) {
            // slow指向的是最近一次处理过的元素，当碰到了不相等的情况时，说明fast碰到了新元素，slow和fast之间都是经历过的多余的与slow前重复的元素
            while(fast<size && nums[slow] == nums[fast]) fast++;
            while(fast<size && nums[slow] != nums[fast])  nums[++slow] = nums[fast++];
        }
        return slow+1;
    }
};
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        int slow = 0, fast = 0;
        while(fast<nums.size()) {
            if(nums[slow] != nums[fast]) nums[++slow] = nums[fast];    // 因为需要判断快慢指针指向的元素是否相等，所以慢指针不能直接指向下一个需要置换的位置
            fast++;                            // 快慢指针指向的元素相同时，快指针继续向前走找新元素
        } 
        return slow+1;
    }
};


// 80. 删除排序数组中的重复项2
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(!nums.size()) return 0;              // 不加会导致slow+1越界
        int slow=0, fast=1, cnt = 1;            // 起始slow,fast不能指向同一个元素，此时cnt等于1，会把slow下一个位置复制成和slow相同[1,2]结果是[1,1]
        while(fast<nums.size()) {
            if(nums[slow]==nums[fast]) {
                if(cnt == 0) fast++;
                else {                            
                    // 值相同，且只出现过一次的，需要交换i后第一个元素，然后cnt置为0
                    // 必须交换是因为快慢指针之间的值可能是从前处理过的元素，slow现在指向的是fast之前置换回去的
                    nums[++slow] = nums[fast++];
                    cnt--;
                }
            }
            else { 
                nums[++slow] = nums[fast++];      // 不相等后的交换，说明新元素被放置到了前面，是第一次出现，cnt置为1
                cnt = 1;
            }
        }
        return slow+1;
    }
};

// 27 移除元素
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if(nums.size()==0) return 0;
        int i=0, j=nums.size()-1;
        while(i<=j){
            if(nums[i]==val) nums[i]=nums[j--];
            else i++;
        }
        return i;            // i前面的数据都是处理完成的
    } 
    // 下面两种方法是相同的
    int removeElement(vector<int>& nums, int val) {             
        // 同向双指针，慢指针指向下一个应该置换的，快指针在前面走，遇到满足条件的就置换，快慢指针之间都是不满足条件的，都是最终排序结果在前的一个个挪到前面
        int res = 0;
        for (int fast = 0; fast < nums.size(); ++fast) {
            if (nums[fast] != val) nums[res++] = nums[fast];     // res前都是处理过的，res指向下一个应该置换的元素
        }
        return res;
    }
    int removeElement(vector<int>& nums, int val) {
        int res = 0;
        int fast = 0;
        while(fast<nums.size()) {
            if (nums[fast] != val) nums[res++] = nums[fast];    
            fast++;
        }
        return res;
    }
};

// 283 移动零                   非零移动到前面，零在末尾
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int fast=0, slow=0;
        while(fast<nums.size()) {      //两指针先一起走，然后一起碰到了0，slow指向0，fast继续向前走，当fast领先slow时，两者之间的就是0
            if(nums[fast]!=0) swap(nums[slow++], nums[fast]);
            fast++;                    // 每一次循环 fast一定会前进一位，slow不一定前进
        }
    }
};
// 第二次刷题，写的乱七八糟，一个case没有通过

// 相向双指针
// 125 验证回文串
class Solution {
public:
    bool isPalindrome(string s) {
        if(s.size()==0) return true;
        int left=0, right=s.size()-1;
        while(left<right) {
            while(left<right && !isalnum(s[left])) left++;           //这里写成了if，会导致如果有连续的非字母数字，会在下面return false
            while(left<right && !isalnum(s[right])) right--;
            if(toupper(s[right--])!=toupper(s[left++])) return false;
        }
        return true;
    }
};
// 1. 判断是否为数字或字母的函数 isalnum(char c)；
// 2. 'a' - 32 = 'A'
// 3. 使用toupper函数比多个判断快多了

// 680 验证回文字符串 Ⅱ
class Solution {
public:
    bool validPalindrome(string s) {
        if(s.size()==0) return true;
        int left=0, right=s.size()-1;
        while(left<right) {
            if(s[left]!=s[right]) return (ispalindrom(s, left+1, right) || ispalindrom(s, left, right-1));
            left++; right--;
        }
        return true;
    }
private:
    bool ispalindrom(string s, int left, int right) {
        while(left<right) {
            if(s[left++]!=s[right--]) return false;
        }
        return true;
    }
};

// 796. 旋转字符串
class Solution {
public:
    bool rotateString(string A, string B) {
        return A.size()==B.size() && (A+A).find(B) != string::npos;
    }
};

// 1 两数之和   哈希表时间复杂度o(n），空间o(n)，双指针的时间复杂度是o(nlogn)，双指针不能解决返回index
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int ,int> m;
        for(int i=0; i<nums.size(); i++) {
            if(!m.count(nums[i])) m[target-nums[i]] = i;
            else return vector<int> {m[nums[i]], i};
        }
        return vector<int> {};
    }
    vector<int> twoSum(vector<int>& nums, int target) {           
        // 这种做法改变了元素的顺序，如果是return index，则错误；如果是return 元素值，可以使用two pointers
        sort(nums.begin(), nums.end());
        int i=0, j=nums.size()-1;
        while(i<j) {
            if(nums[i]+nums[j] == target) return vector<int> {j, i};
            else if(nums[i]+nums[j] > target) j--;
            else i++;
        }
        return vector<int> {};
    }
};
// 两数之和 设计 add是o(1)复杂度，不可以使用排序的方法，否则插入一个元素，需要向后移动数组元素，o(n)
// 第二次刷题，返回index使用了two pointers


// 15 三数之和
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) { 
       vector<vector<int>> res;
       sort(nums.begin(), nums.end());
       if(nums.size()<3 || nums.back()<0 || nums.front()>0) return res;     // sort写成sorted, front写成了begin
       for(int k = 0; k<nums.size()-2; k++) {
           if(nums[k]>0) break;
           if(k>0 && nums[k]==nums[k-1]) continue;
           int target=0-nums[k], i=k+1, j=nums.size()-1;
           while(i<j) {
               if(target==nums[i]+nums[j]) { 
                   res.push_back({nums[k], nums[i], nums[j]});
                   while(i<j && nums[i]==nums[i+1]) i++;                // while写成if
                   while(i<j && nums[j]==nums[j-1]) j--;
                   i++;j--;                                             // 上一步结束以后指向的仍旧是放入结果的那个元素
               }
               else if(target>nums[i]+nums[j]) i++;
               else j--;
           }
        //    while(k<nums.size()-2 && nums[k] == nums[k+1]) i++;          //处理完k以后，判断前面有没有相同的，也可以
       }
       return res;
    }
};
// 第二次刷题落下找到结果并去重以后的i++,j--

// 611 有效三角形的个数
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int ans = 0;
        if(nums.size()<3) return ans;
        sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size()-2; i++) {
            int left=i+1, right=nums.size()-1;
            while(left<right) {
                if(nums[i]+nums[left]>nums[right]) {
                    ans += right-left; right--;
                }
                else left++;   // 不满足条件时，既可以动right，也可以动left，所以会缺失解
            }
        }
        return ans;
    }
    // 应该固定最大值，当不满足条件时，把最小值前移即可
    int triangleNumber(vector<int>& nums) {
        int ans = 0;
        if(nums.size()<3) return ans;
        sort(nums.begin(), nums.end());
        for(int i=2; i<nums.size(); i++) {
            int left=0, right=i-1;
            while(left<right) {
                if(nums[right]+nums[left]>nums[i]) {
                    ans += right-left; right--;
                }
                else left++;   
            }
        }
        return ans;
    }
};
// 第二次刷题，找到了答案以后，没有right--，丢解


// 16 最接近的三数之和
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        if(nums.size()<3) return 0;
        int diff = INT_MAX, res, sum, left, right;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size()-2; i++) {
            left = i+1; right = nums.size()-1;
            while(left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if(abs(sum-target)<diff) {
                    res = sum;
                    diff = abs(sum-target);
                }
                if(sum < target) left++;
                else if(sum > target) right--;
                else return res; 
            }
        }
        return res;
    }
};
// 第二次刷题，没有记录diff，记录了当前最好结果res，初始化时会出问题，abs(res-target)在target是负数的时候越界。

// 18 四数之和
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        if(nums.size()<4) return res;           //不加入for循环会越界，不明白原因，不应该进入for循环
        for(int i=0; i<nums.size()-3; i++) {
            // while(i<nums.size()-4 && nums[i]==nums[i+1]) i++;      在还没处理的时候就跳过相同值，会缺失解，如0000123，会缺失0000，0001....等多个解
            if(i>0 && nums[i]==nums[i-1]) continue;     
            for(int j=i+1; j<nums.size()-2; j++) {
                // while(j<nums.size()-3 && nums[j]==nums[j+1]) j++;   // 与left或right不同，这里确定了i，j的范围，不会直接跑到最后
                if(j>i+1 && nums[j]==nums[j-1]) continue;
                int left = j+1, right = nums.size()-1;
                while(left<right) {
                    int sum = nums[i] + nums[j] + nums[left] + nums[right];
                    if(target == sum) {
                        res.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
                        while(left<right && nums[left]==nums[left+1]) left++;         // while循环中要时刻监测left<right
                        // 判断以后再进行去重是为了避免，left 到right之间的值全部相同，会直接跳过这个解
                        // while以后会停留在最后一个相同的元素，因为这个元素已经处理过，最后仍旧需要++或--
                        while(left<right && nums[right]==nums[right-1]) right--;
                        left++; right--;
                    }
                    else if(target < sum) right--;
                    else left++;
                }
            }
        }
        return res;
    }
};
// 第二次刷题，if(i>0 && nums[i]==nums[i-1]) 写的while会导致越界问题，缺少对右边界的限制，导致越界


// 905 按奇偶排序数组                 quick select类似题目，没有办法保持原有的顺序
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        int size = A.size();
        if(size == 0 || size == 1) return A;
        int left = 0, right = size-1;
        while(left < right) {
            while(left < right && A[left]%2 == 0) left++;
            while(left < right && A[right]%2 == 1) right--;
            if(left < right) swap(A[left++], A[right--]);
        }
        return A;
    }
};

// 922 按奇偶排序数组 II
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        int size = A.size(), even = 0, odd = 1;
        while(even < size && odd < size) {
            while(even < size && A[even]%2 == 0) even += 2;
            while(odd < size && A[odd]%2 == 1) odd += 2;
            if(even < size && odd < size) {
                swap(A[even], A[odd]);
                even += 2; odd += 2;
            }
        }
        return A;
    }
};

// 75 颜色排序    最简单使用counting sort 需要额外空间，O(N)时间复杂度  其次可以使用两次partition array
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0, right = nums.size()-1, cur = 0;
        while(cur<=right) {     //right指向的数据没有处理过
            if(nums[cur] == 0) swap(nums[left++], nums[cur++]);
            else if(nums[cur] == 2) swap(nums[right--], nums[cur]); 
            // right 指向的数据没有处理过，因此cur应该在下一轮判断一下
            else cur++;
        }
    }
};

// 彩虹排序，有k种颜色排序，第一种方法使用counting sort，空间O(k),时间复杂度O(N)，时间复杂度和颜色个数无关
// k=1,O(1),k=2,O(n),k=3,O(n)   k=n,O(nlogn)    所以推测时间复杂度是O(nlogk) logk联想到把k一分为二
// 归并排序的思路利用k一分为二，k限制了树高，每一层运用快速排序的思路实现partition
class Solution {
public:
    void sortColors2(vector<int>& nums, int k) {
        helper(nums, 0, nums.size()-1, 1, k);
    }
private:
    void helper(vector<int>& nums, int start, int end, int k_start, int k_end) {
        if(k_start == k_end || start == end) return;
        int left = start, right = end, middle = (k_start + k_end)/2;
        while(left<=right) {   // 后续涉及到分成两个部分的,判断写left<=right
            while(left<=right && nums[left]<=middle) left++;  
            //此处与快排条件不同，不会出现left-right=2
            while(left<=right && nums[right]>middle) right--;
            if(left<=right) swap(nums[left++], nums[right--]);
        } 
        if(right>=start) helper(nums, start, right, k_start, middle);  
        if(end>=left) helper(nums, left, end, middle+1, k_end);
    }
};