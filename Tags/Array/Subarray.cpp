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


// 53 最大子序和 
class Solution {               // 子数组问题
public: 
    int maxSubArray(vector<int>& nums) {
        int ans=nums[0], sum=0;
        int from=-1, to=-1, fromnew;
        for(int i=0; i<nums.size(); i++) {
            // sum = max(sum+nums[i], nums[i]);
            if(sum>0) sum = sum+nums[i];
            else {
                sum = nums[i];
                fromnew = i;  // 只有截断，重新开始时，fromnew才会变化，因此在后面更新ans时，即使出现，现在的sum与ans相等，fromnew记录的也是现在的from
            } 
            if(ans>=sum) continue;
            else {
                ans = sum;
                to = i;
                from = fromnew;  // from, to 记录的是目前ans的起始和终点，fromnew记录的是sum的起点，终点是i
            }
        }
        return ans;
    }
};
class Solution {               // 子数组问题        对于最小子序和，只需把他变为相反数，再求最大子序和
public: 
    int maxSubArray(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        int res = INT_MIN, sum = 0, minSum = 0;
        for(int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            res = max(res, sum-minSum);
            minSum = min(sum, minSum);
        }
        return res;
    }
    int maxSubArray(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        int res = INT_MIN, sum = 0, minSum = 0, from = 0, to = 0, fromnew = 0;
        for(int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if(res<sum-minSum) {
                to = i;
                from = fromnew;         // 记录当时的起始点，后面可能会更新起始点，但是res没有更新
                res = sum-minSum;
            }
            if(sum<minSum) {
                fromnew = i;
                minSum = sum;
            }
        }
        return res;
    }
};

// 152 乘积最大子序列         
class Solution {               // 子数组问题
public:
    int maxProduct(vector<int>& nums) {                  //负数乘以更小的值更大，因此需保留极小值
        int imax = 1, imin = 1, res = nums[0], tmp;      //imax， imin表示当前最大或最小子序列，必须包含此时的i
        for(int i = 0; i< nums.size(); i++){
            if(nums[i]<0){
                tmp = imin;
                imin = imax;
                imax = tmp;
            }
            imax = max(imax*nums[i], nums[i]);
            imin = min(imin*nums[i], nums[i]);
            res = max(imax, res);
        }
        return res;
        
    }
};
// 整数连乘，除了遇到0，绝对值会不断变大

// 560 和为k的子数组
class Solution {                                //  暴力法，时间复杂度为O(n**2), 结果不包含空子集，sum[i]表示前i-1个元素之和，例如sum[1] = nums[0]
public:
    int subarraySum(vector<int>& nums, int k) {
        vector<int> sum(nums.size()+1);
        int result = 0;
        sum[0] = 0;
        for(int i=1; i<nums.size()+1; i++)  sum[i] = sum[i-1] + nums[i-1];
        for(int i=0; i<nums.size()+1; i++) {
            for(int j=0; j<i; j++) if(sum[i]-sum[j]==k) result++;
        }
        return result;
    }
    int subarraySum(vector<int>& nums, int k) { 
        int sum = 0;
        unordered_map<int, int> m;
        m[0] = 1;                                 // 需要加入空集，否则当结果为第一个元素到第i-1个元素，哈希表中无空集0
        int result = 0;
        for(int i=0; i<nums.size(); i++)  {
            sum += nums[i];
            if(m.count(sum-k)) result += m[sum-k];
            if(m.count(sum)) m[sum]++;
            else m[sum] = 1;
        }
        return result;
    }
}; 

// 325. 和等于k的最长子数组长度
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int ans = 0;
        vector<int> sum(nums.size()+1, 0);
        for(int i = 0; i<nums.size(); i++) {
            sum[i+1] = sum[i] + nums[i];
        }
        for(int i = 1; i<=nums.size(); i++) {
            for(int j = 0; j<i; j++) {
                if(sum[i] - sum[j] == k) ans = max(i-j, ans);
            }
        }
        return ans;
    }
    int maxSubArrayLen(vector<int>& nums, int k) {
        int sum = 0;
        unordered_map<int, int> m;
        m[0] = -1;                                 // 需要加入空集，且初始化为-1，此时当子集从第一个元素开始时，长度为i+1
        int result = 0;
        for(int i=0; i<nums.size(); i++)  {
            sum += nums[i];
            if(m.count(sum-k)) result = max(result, i - m[sum-k]);
            if(!m.count(sum)) m[sum] = i;            // 只需记录第一次出现的位置，后面再出现则跳过，这样得到的结果是最长的
        }
        return result;
    }
};
// 第二次刷题对m[0]初始化错误，i - m[sum-k]，因为是从m[sum-k]的下一个位置开始的

// lintcode 最接近0的子数组和
class Solution {
public:
    struct node {
        node(int _value, int _pos):value(_value), pos(_pos) {}
        int value, pos;
        bool operator<(const node &o) const{
            return (value < o.value || value == o.value && pos < o.pos);
        }
    };
    vector<int> subarraySumClosest(vector<int> nums){
        vector<node> s;
        vector<int> results(2);
        s.push_back(node(0,-1));
        int sum = 0, len = nums.size();
        for (int i = 0; i < len ; ++i) {
            sum += nums[i];     
            s.push_back(node(sum, i));
        }
        sort(s.begin(), s.end());
        len = s.size();
        int ans = 0x7fffffff;
        for (int i = 0; i < len-1; ++i)
            if (abs(s[i+1].value - s[i].value) < ans) { 
                ans = abs(s[i+1].value - s[i].value);
                results[0] = min(s[i].pos, s[i+1].pos)+1;
                results[1] = max(s[i].pos, s[i+1].pos);
            }
        return results;
    }
};
// 第二次刷题没有思路，且运算符重载不会写


// 713 乘积小于k的子数组    nums正整数数组，返回子数组的个数
// 相当于是一种滑动窗口的解法，维护一个数字乘积刚好小于k的滑动窗口，用变量left来记录其左边界的位置，右边界i就是当前遍历到的位置。
// 遍历原数组，用 prod 乘上当前遍历到的数字，然后进行 while 循环，如果 prod 大于等于k，则滑动窗口的左边界需要向右移动一位，删除最左边的数字，
// 那么少了一个数字，乘积就会改变，所以用 prod 除以最左边的数字，然后左边右移一位，即 left 自增1。
// 当我们确定了窗口的大小后，就可以统计子数组的个数了，就是窗口的大小。为啥呢，比如 [5 2 6] 这个窗口，k还是 100，右边界刚滑到6这个位置，
// 这个窗口的大小就是包含6的子数组乘积小于k的个数，即 [6], [2 6], [5 2 6]，正好是3个。所以窗口每次向右增加一个数字，然后左边去掉需要去掉的数字后，
// 窗口的大小就是新的子数组的个数，每次加到结果 res 中即可
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {    // 暴力法，数字太大
        int ans=0;
        vector<long> mul(nums.size()+1);
        mul[0] = 1;
        for(int i=0; i<nums.size(); i++) mul[i+1] = mul[i]*nums[i];
        for(int i=1; i<nums.size()+1; i++) {
            for(int j=0; j<i; j++)  if(mul[i] / mul[j] < k) ans++; 
        }
        return ans;
    }
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;                     // 如果k<1，则对于数组[1,1,1]，会越界
        int res = 0, prod = 1, left = 0;
        for (int i = 0; i < nums.size(); ++i) {
            prod *= nums[i];
            while (prod >= k) prod /= nums[left++];        // 每一次循环，得到的是以i为结尾的子数组数量
            // 当left=i时，此时prod=nums[i]
            // 若元素值不是1，且大于k时，经过while后，prod为1，此时left=i+1，若到了末尾会结束循环，不会出现越界的情况
            res += i - left + 1;
        }
        return res;
    }
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {   // 第二次刷题
        int prod = 1, res = 0, left = 0;
        for(int i = 0; i < nums.size(); i++) {
            prod = prod*nums[i];
            while(prod>=k && left<=i) prod = prod/nums[left++];
            // left = i时，prod=1，若此时也不满足情况，则left+1，res+0，继续向前走
            res += i-left+1;
        }
        return res;
    }
};

// 209 长度最小的子数组               找出该数组中满足其和 ≥ s 的长度最小的连续子数组
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {      //sum是left到i之间的子数组和，包含边界
        if(s<=0) return 0;
        int sum=0, left=0, res=INT_MAX;
        for (int i = 0; i < nums.size(); ++i) {           // 每一次循环得到的是以i为结尾的最小子数组的长度
            sum = sum + nums[i];
            while(sum >= s && left<=i) {        // 可以使用双指针或者二分法的前提是正整数数组，否则sum不会递增
                res = min(res, i-left+1);
                sum -= nums[left++];
            }
        }
        return res == INT_MAX? 0: res;
    }
};
// 连续子数组问题
// 1.大于小于某target使用滑动窗口；2.等于target可以使用哈希；3.求最大值最小值使用dp

// 3 无重复字符的最长子串
class Solution {
public:
    int lengthOfLongestSubstring(string s) {     
        if(s.size() == 0) return 0;
        int res = 1, left = 0, right = 0;
        while(right<s.size()) {
            for(int i = left; i < right; i++) {
                if(s[right] == s[i]) {
                    left = i+1;            //right-1 到left是以left开头的最长无重复子串，只会有一个值与s[right]相等
                    break;
                }
            }
            res = max(res, right-left+1);
            right++;
        }
        return res;
    }
};
class Solution {                                  // 虽然是常数时间，但需要多步操作，速度慢
public:
    int lengthOfLongestSubstring(string s) {      //right-1 到left是以left开头的最长无重复子串 
        if(s.size() == 0) return 0;
        unordered_set<char> visited;
        int res = 1, left = 0;
        for(int i = 0; i<s.size(); i++) {         
            //判断右边指针元素是否存在，不存在则更新res，并加入set
            if(!visited.count(s[i])) {
                visited.insert(s[i]);
                res = max(res, i-left+1);
                cout<<i<<left<<endl;
                continue;
            }
            // 若存在则移动左边指针，不断在set中去除指向的元素，最后指向与right相同的下一个元素
            while(s[left]!=s[right]) visited.erase(s[left++]);
            left++;
        }
        return res;
    }
};






