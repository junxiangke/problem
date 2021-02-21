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

// 915 分割数组
class Solution {
public:
    int partitionDisjoint(vector<int>& A) {
        int size = A.size();
        vector<int> right(size);
        right[size-1] = A[size-1];
        for(int i=size-2; i>=0; i--) {
            right[i] = min(right[i+1], A[i]);
        }
        int left = A[0];
        if(left<=right[1]) return 1;
        int i = 1;
        for(i=1; i<size-1; i++) {
            left = max(left, A[i]);
            if(left<=right[i+1]) return i+1;     // 不能用left[i],right[i]比较，第i个数会改变两数组的结果
        }
        return i+1;
    }
};

//1013 将数组分成和相等的三个部分
class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int sum = 0;
        for(int i = 0; i<A.size(); i++) {
            sum += A[i];
        }
        if(sum%3) return false;
        int average = sum / 3;
        int count = 0;
        sum = 0;
        for(int i = 0; i<A.size(); i++) {
            sum += A[i];
            if(sum == average) {
                count++; sum=0;
            }
            if(count == 3) return true;
        }
        return false;
    }
};

// 225 队列实现栈
class MyStack {
public:
    queue<int> q;
    int top_element = 0;

    /** Initialize your data structure here. */
    MyStack() {
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        q.push(x);
        top_element = x;
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int size = q.size();
        while(size>2) {
            q.push(q.front());
            q.pop();
            size--;
        }
        top_element = q.front();
        q.push(top_element);
        q.pop();
        int res = q.front();
        q.pop();
        return res;
    }
    
    /** Get the top element. */
    int top() {
        return top_element;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return q.size()==0;
    }
};

// 232 用栈实现队列
class MyQueue {
public:

    stack<int> s1;
    stack<int> s2;

    /** Initialize your data structure here. */
    MyQueue() {
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        s1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int res = peek();
        s2.pop();
        return res;
    }
    
    /** Get the front element. */
    int peek() {
        if(s2.empty()) {
            while(!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return s1.empty && s2.empty();
    }
};


