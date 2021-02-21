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

struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };


// 912 排序数组
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        BuildHeap(nums);
        for(int i = nums.size(); i>=2; i--) {
            swap(nums[0], nums[i-1]);
            PercDown(nums, 0, i-1);
        }
        return nums;
    }
private:
    void BuildHeap(vector<int>& nums) {
        for(int i = nums.size()/2-1; i>=0; i--) {
            PercDown(nums, i, nums.size());
        }
    }
    void PercDown(vector<int>& nums, int root, int size) {
        int parent = root, tmp = nums[root], child;
        for(parent; 2*parent+1<size; parent = child) {
            child = 2*parent+1;
            if(child+1<size && nums[child+1]>nums[child]) child++;
            if(tmp<nums[child]) nums[parent] = nums[child];
            else break;
        }
        nums[parent] = tmp;
    }
};


// 215 数组中的第K个最大元素               
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        BuildHeap(nums, k);
        for(int i = k; i<nums.size(); i++) {
            Insert(nums, i, k);
            Delete(nums, k+1);
        }
        return nums[0];
    }
private:
    void BuildHeap(vector<int>& nums, int size) {
        for(int i = size/2 -1; i>=0; i--) {
            PercDown(nums, i, size);
        }
    }
    void PercDown(vector<int>& nums, int root, int size) {
        int tmp = nums[root], parent = root, child;            // 必须记录下来，否则root位置上的元素会发生变化
        for(parent; parent*2+1<size; parent = child) {
            child = parent*2+1;
            if(child+1<size && nums[child]>nums[child+1]) child++;
            if(tmp>nums[child]) nums[parent] = nums[child];
            else break;
        }
        nums[parent] = tmp;
    }
    void Insert(vector<int>& nums, int i, int size) {
        swap(nums[i], nums[size]);
        int tmp = nums[size], child = size, parent;
        for(child; (child+1)/2-1>=0; child = parent) {
            parent = (child-1)/2;
            if(tmp<nums[parent]) nums[child] = nums[parent];
            else break;
        }
        nums[child] = tmp;
    }
    void Delete(vector<int>& nums, int size) {     // 当前堆的大小为size，pop后，大小为size-1
        swap(nums[0], nums[size-1]);
        PercDown(nums, 0, size-1);
    }
};
// 建立N大小的堆，删除元素直到size大小为k
void PercDown(vector<int>& nums, int root, int size) {
    int child, parent;
    int tmp=nums[root];
    for(parent=root; (2*parent+1)<=size-1; parent=child) {
        child = 2*parent+1;
        if(child!=size-1 &&  nums[child]<nums[child+1]) child++;
        if(tmp>nums[child]) break;
        else nums[parent] = nums[child];
    }
    nums[parent] = tmp;
}

void BuildHeap(vector<int>& nums) {
    int size = nums.size();
    for(int i=size/2-1; i>=0; i--) {
        PercDown(nums, i, size);
    }
}

int findKthLargest(vector<int>& nums, int k) {
    BuildHeap(nums);
    int res;
    int size = nums.size();
    for(int i=1; i<=k; i++) {
        res = nums[0];
        nums[0] = nums[size-i];
        PercDown(nums, 0, size-i);
    }
    return res;
}

// 215 数组中的第K个最大元素               quickselect 时间复杂度是O(N)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        if(k>nums.size()) return -1;
        return quickselect(nums, 0, nums.size()-1, k);
    }
    int quickselect(vector<int>& nums, int start, int end, int k) {
        if(start==end) return nums[start];
        int left = start, right = end;
        int pivot = nums[(left + right) / 2];
        while(left <= right) {
            while(left<=right && nums[left] > pivot) left++;   // 是第k个最大元素，而不是第k大的元素，因此倒序排列
            while(left<=right && nums[right] < pivot) right--;
            if(left <= right) swap(nums[left++], nums[right--]);
        }
        if(start+k-1<=right) return quickselect(nums, start, right, k); // 理解为左侧数字的个数
        else if(start+k-1>=left) return quickselect(nums, left, end, k-(left-start));  // 这里一开始写错了left-start
        // start+k-1<=end，因此当left>end时，不满足条件语句，进入不了下一层递归
        else return nums[right+1];
    }
};

// 703 数据流中的第k个最大元素                 与上一道题目的区别是，数字是一个一个来的，不能直接建立大小为k的堆，或者建立大小为n的堆
class KthLargest {                       // priority queue 定义 priority_queue<Type, Container, Functional>
public:
    priority_queue<int, vector<int>, greater<int>> pq;     // 小顶堆是greater<int>，大顶堆是less<int>
    int size;

    KthLargest(int k, vector<int> nums) {    
        size=k;//将小顶堆的大小控制在k
        for(int i=0;i<nums.size();i++) {     // 最后维护的是大小为k的堆，接近O(NlogK)
            pq.push(nums[i]);
            if(pq.size()>k) pq.pop();
        }
    }
    int add(int val) {                       // O(logK)
        pq.push(val); 
        if(pq.size()>size) pq.pop();    //小顶堆pop是删除最小值，top是返回最小值
        // pq.size()的时间复杂度一定是O(1)，有专门的变量记录，不可能每次都数一遍
        return pq.top();       // 取堆顶元素是top
    }
};


// 23 合并k个排序链表
class Solution {        // Heap
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, cmp> pq;
        for(int i = 0; i<lists.size(); i++) {
            if(lists[i] != NULL) pq.push(lists[i]); 
            }
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;
        while(!pq.empty()) {
            ListNode* node = pq.top(); pq.pop();
            tail->next = node;
            tail = node;
            if(node->next != NULL) pq.push(node->next); 
        }
        return dummy->next;
    }
private:
    struct cmp {bool operator() (ListNode* l1, ListNode* l2) {return l1->val > l2->val; }};   // 运算符重载
};

class Solution {        // 自底向上的两两归并
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0) return NULL;
        while(lists.size() > 1) {
            vector<ListNode*> new_lists;
            for(int i = 0; i<lists.size()-1; i = i+2) {    // 要写i = i+2
                ListNode* node = mergetwolists(lists[i], lists[i+1]);
                if(node != NULL) new_lists.push_back(node);
            }
            if(lists.size()%2 == 1 && lists[lists.size()-1] != NULL) new_lists.push_back(lists[lists.size()-1]);
            lists = new_lists;
            cout<<lists.size()<<endl;
        }
        return lists[0];
    }
private:
    ListNode* mergetwolists(ListNode* list1, ListNode* list2) {
        if(list1 == NULL) return list2;
        if(list2 == NULL) return list1;
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;
        while(list1 != NULL && list2 != NULL) {
            if(list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            }
            else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        if(list1 != NULL) tail->next = list1;
        if(list2 != NULL) tail->next = list2;
        return dummy->next;
    }
};

class Solution {        // 类似归并的分治
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0) return NULL;
        return mergehelper(lists, 0, lists.size()-1);
    }
private:
    ListNode* mergehelper(vector<ListNode*>& lists, int start, int end) {
        if(start == end) return lists[start];
        int mid = (start + end) / 2;
        ListNode* left = mergehelper(lists, start, mid);
        ListNode* right = mergehelper(lists, mid+1, end);
        return mergetwolists(left, right);
    }
    ListNode* mergetwolists(ListNode* list1, ListNode* list2) {
        if(list1 == NULL) return list2;
        if(list2 == NULL) return list1;
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;
        while(list1 != NULL && list2 != NULL) {
            if(list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            }
            else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        if(list1 != NULL) tail->next = list1;
        if(list2 != NULL) tail->next = list2;
        return dummy->next;
    }
};


vector<vector<int>> func(int m, int n) {
    vector<vector<int>> res(m, vector<int>(n, 0));
    int index = 1;
    for(int i = 0; i<m+n-1; i++) {
        for(int j = 0; j<=i; j++) {
            if(j>=n || i-j>=m) continue;
            res[i-j][j] = index++;
        }
    }
    return res;
}
