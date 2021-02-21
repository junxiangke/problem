#include<iostream>           //输入输出需要的库
#include<vector>             //STL库，容器
#include<algorithm>          //调sort函数，等
#include<queue>              //STL库，队列
#include<stack>              //STL库，栈
#include<unordered_map>      //哈希表，查找效率高，O(1)
#include<map>
#include<set>
using namespace std;         //命名空间


// 496 下一个更大元素
// 构造单调栈，元素单调递减，从前向后遍历数组，遇到比栈顶元素更大的，处理掉栈顶元素，当前遍历元素是栈顶元素的下一个更大元素
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        vector<int> res(nums1.size());
        unordered_map<int, int> m;
        for(int i: nums2) {
            while(!st.empty() && st.top() < i) {
                m[st.top()] = i; st.pop();
            }
            st.push(i);
        }
        for(int i = 0; i < nums1.size(); i++) {
            res[i] = m.count(nums1[i])? m[nums1[i]]: -1; 
        }
        return res;
    }
};

// 503 下一个更大的元素 2
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        vector<int> res(n, -1); 
        if(n == 0) return res;
        for(int i = 0; i < 2 * n - 1; i++) {
            while(!st.empty() && nums[st.top()] < nums[i%n]) {
                res[st.top()] = nums[i%n]; st.pop();
            }
            st.push(i%n);
        }
        return res;
    }
};

// 84 柱状图中最大的矩形
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int ans = 0;
        stack<int> st;
        heights.push_back(0);
        for(int i = 0; i < heights.size(); i++) {
            if(st.empty() || heights[st.top()] < heights[i]) st.push(i);
            // 构造递增栈，对局部最大值，即前一个元素大于后一个元素时开始处理
            else {
                int cur = st.top(); st.pop();
                ans = max(st.empty()? i * heights[cur] : heights[cur] * (i - st.top() - 1), ans);
                // 情况一：1，3，2，5，6 栈中元素 1，2，5，6，处理元素2时，宽度是4，而不是3，应该使用st.top()位置，因为2以前可能会有比2大的
                // 情况二：1，3，2，5，6 栈中元素 1，2，5，6，处理元素5时，宽度是2，前方没有比5大的元素
                // 情况三：1，3，2，5，6 栈中元素 1，2，5，6，处理元素1时，栈空，宽度是i
                i--;
            }
        }
        return ans;
    }
};

// 85


// 221